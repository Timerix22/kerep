#include "allocators_internal.h"
#include <stdio.h>


#define default_chunks_per_allocation 16
// growing chunk array size
#define new_max_chunks_count ( default_chunks_per_allocation*(self->chunks_count/16 == 0) + \
    default_chunks_per_allocation*add_padding(self->chunks_count/2)/4 )

#define default_chunk_size 1024
// growing chunk size
#define new_chunk_size ( default_chunk_size*(self->chunks_count/16 == 0) + \
    default_chunk_size*add_padding(self->chunks_count/8) )

#define chunk_alloc(SZ, OCCUPIED) (MemoryChunk){ .data=malloc(SZ), .size=SZ, .occupied_size=OCCUPIED }
#define curr_chunk (self->chunks+self->curr_chunk_i)

__attribute__ ((noinline)) void* ___alloc_realloc_chunk(LinearAllocator* self, alloc_size_t alloc_size){
    free(curr_chunk->data);
    *curr_chunk=chunk_alloc(alloc_size, alloc_size);
    return curr_chunk->data;
}

__attribute__ ((noinline)) void* __alloc_new_chunk(LinearAllocator* self, alloc_size_t alloc_size){
    self->curr_chunk_i++;
    // next chunk has been already allocated
    if(self->curr_chunk_i < self->chunks_count)
        return curr_chunk->data;

    // self->chunks array is full
    if(self->chunks_count == self->max_chunks_count){
        self->max_chunks_count = new_max_chunks_count;
        self->chunks = realloc(self->chunks, sizeof(MemoryChunk) * self->max_chunks_count);
    }

    // new chunk allocation
    self->chunks_count++;
    alloc_size_t _new_chunk_size= alloc_size > new_chunk_size ? alloc_size : new_chunk_size;
    *curr_chunk=chunk_alloc(_new_chunk_size, alloc_size);
    return curr_chunk->data;
}

void* LinearAllocator_alloc(allocator_ptr _self, alloc_size_t alloc_size){
    // assert(_self!=NULL);
    // assert(alloc_size>0);
    LinearAllocator* self = (LinearAllocator*)_self;
    alloc_size=add_padding(alloc_size);

    // aligned alloc_size can fit into the current chunk
    if(curr_chunk->occupied_size + alloc_size <= curr_chunk->size){
        void* data_ptr=curr_chunk->data + curr_chunk->occupied_size;
        curr_chunk->occupied_size += alloc_size;
        return data_ptr;
    }
    // reallocation of current chunk because it is clean
    if(curr_chunk->occupied_size == 0){
        // It is very unefficient operation.
        // If it happens not only in the first chunk, code have to be refactored
        assert(self->curr_chunk_i==0);
        return ___alloc_realloc_chunk(self, alloc_size);
    }
    // creation of a new chunk
    else {
        return __alloc_new_chunk(self, alloc_size);
    }
}

void LinearAllocator_free(allocator_ptr _self, void* ptr){
    // LinearAllocator can't free pointers
}

void LinearAllocator_destruct(LinearAllocator* self){
    // assert(_self!=NULL);
    u32 size=0;
    u32 oc_size=0;
    for(u32 chunk_i=0; chunk_i < self->chunks_count; chunk_i++){
        free(self->chunks[chunk_i].data);
        size+=self->chunks[chunk_i].size;
        oc_size+=self->chunks[chunk_i].occupied_size;
    }
    printf("\e[35m%u/%u\n",oc_size,size);
    free(self->chunks);
    self->chunks=NULL;
    self->chunks_count=0;
    self->curr_chunk_i=0;
    self->max_chunks_count=0;
}

void LinearAllocator_construct(LinearAllocator* self, alloc_size_t starting_size){
    assert(self!=NULL);
    assert(starting_size>0);
    self->base.alloc_f=LinearAllocator_alloc;
    self->base.free_f=LinearAllocator_free;

    self->curr_chunk_i=0;
    self->chunks_count=1;
    self->max_chunks_count=new_max_chunks_count;
    self->chunks=malloc(sizeof(MemoryChunk) * new_max_chunks_count);
    self->chunks[0]=chunk_alloc(starting_size, 0);
}

kt_define(LinearAllocator, (destruct_t)LinearAllocator_destruct, NULL)
