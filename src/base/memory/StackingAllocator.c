#include "allocators_internal.h"

#define chunk_alloc(SZ) (MemoryChunk){ .data=malloc(SZ), .size=SZ, .occupied_size=0 }
#define linear self->base
#define curr_chunk (linear.chunks+linear.curr_chunk_i)

typedef struct {
    size_t data_size;
} AllocationHeader;

void* StackingAllocator_alloc(allocator_ptr _self, size_t size){
    assert(_self!=NULL);
    assert(size>0);
    StackingAllocator* self = (StackingAllocator*)_self;
    size=add_padding(size);

    // allocates memory with header struct before data
    AllocationHeader* header_ptr=LinearAllocator_alloc(_self, sizeof(AllocationHeader) + size);
    void* data_ptr = (void*)header_ptr + sizeof(AllocationHeader);
    header_ptr->data_size = size;

    self->allocations_count++;
    return data_ptr;
}

void StackingAllocator_free(allocator_ptr _self, void* data_ptr){
    assert(_self!=NULL);
    assert(data_ptr!=NULL);
    StackingAllocator* self = (StackingAllocator*)_self;
    AllocationHeader* header_ptr = data_ptr - sizeof(AllocationHeader);
    
    // chunk is empty
    if(curr_chunk->occupied_size==0){
        // isn't the first chunk
        assert(linear.curr_chunk_i>0);
        linear.curr_chunk_i--;
    }

    size_t allocation_size=header_ptr->data_size+sizeof(*header_ptr);
    // data must fit in chunk
    assert(allocation_size <= curr_chunk->occupied_size);
    curr_chunk->occupied_size -= allocation_size;
}

void StackingAllocator_destruct(StackingAllocator* self){
    LinearAllocator_destruct(&self->base);
}

void StackingAllocator_construct(StackingAllocator* self, size_t starting_size){
    assert(self!=NULL);
    assert(starting_size>0);
    LinearAllocator_construct(&linear, starting_size);
    linear.base.alloc_f=StackingAllocator_alloc;
    linear.base.free_f=StackingAllocator_free;
    self->allocations_count=0;
}

kt_define(StackingAllocator, (freeMembers_t)StackingAllocator_destruct, NULL)
