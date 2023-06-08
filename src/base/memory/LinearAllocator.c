#include "allocators_internal.h"

#define chunks_per_allocation 16
#define default_chunk_size add_padding(1024)
#define chunk_alloc(SZ, OCCUPIED) (MemoryChunk){ .data=malloc(SZ), .size=SZ, .occupied_size=OCCUPIED }
#define curr_chunk (self->chunks+self->curr_chunk_i)

__attribute__ ((noinline)) void* ___alloc_realloc_chunk(LinearAllocator* self, size_t size){
    free(curr_chunk->data);
    *curr_chunk=chunk_alloc(size, size);
    return curr_chunk->data;
}

__attribute__ ((noinline)) void* __alloc_new_chunk(LinearAllocator* self, size_t size){
    self->curr_chunk_i++;
    // next chunk has been already allocated
    if(self->curr_chunk_i < self->chunks_count)
        return curr_chunk->data;

    // self->chunks array is full
    if(self->chunks_count == self->max_chunks_count){
        self->max_chunks_count += chunks_per_allocation;
        self->chunks = realloc(self->chunks, sizeof(MemoryChunk) * self->max_chunks_count);
    }

    // new chunk allocation
    self->chunks_count++;
    size_t new_chunk_size=default_chunk_size > size ? size : default_chunk_size;
    *curr_chunk=chunk_alloc(new_chunk_size, new_chunk_size);
    return curr_chunk->data;
}

void* LinearAllocator_alloc(allocator_ptr _self, size_t size){
    // assert(_self!=NULL);
    // assert(size>0);
    LinearAllocator* self = (LinearAllocator*)_self;
    size=add_padding(size);

    // aligned size can fit into the current chunk
    if(curr_chunk->occupied_size + size <= curr_chunk->size){
        void* data_ptr=curr_chunk->data + curr_chunk->occupied_size;
        curr_chunk->occupied_size += size;
        return data_ptr;
    }
    // reallocation of current chunk because it is clean
    if(curr_chunk->occupied_size == 0){
        // It is very unefficient operation.
        // If it happens not only in the first chunk, code have to be refactored
        assert(self->curr_chunk_i==0);
        return ___alloc_realloc_chunk(self, size);
    }
    // creation of a new chunk
    else {
        return __alloc_new_chunk(self, size);
    }
}

void LinearAllocator_free(allocator_ptr _self, void* ptr){
    // LinearAllocator can't free pointers
}

void LinearAllocator_destruct(LinearAllocator* self){
    // assert(_self!=NULL);
    for(u16 chunk_i=0; chunk_i < self->chunks_count; chunk_i++){
        free(self->chunks[chunk_i].data);
    }
    free(self->chunks);
    self->chunks=NULL;
}

void LinearAllocator_construct(LinearAllocator* self, size_t starting_size){
    assert(self!=NULL);
    assert(starting_size>0);
    self->base.alloc_f=LinearAllocator_alloc;
    self->base.free_f=LinearAllocator_free;

    self->curr_chunk_i=0;
    self->chunks_count=1;
    self->max_chunks_count=chunks_per_allocation;
    self->chunks=malloc(sizeof(*self->chunks) * chunks_per_allocation);
    self->chunks[0]=chunk_alloc(starting_size, 0);
}

kt_define(LinearAllocator, (freeMembers_t)LinearAllocator_destruct, NULL)
