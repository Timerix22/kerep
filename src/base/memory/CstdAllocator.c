#include "allocators_internal.h"

void* CstdAllocator_alloc(allocator_ptr self, alloc_size_t size){
    // assert(size>0);
    return malloc(size);
}

void CstdAllocator_free(allocator_ptr self, void* ptr){
    // assert(ptr!=NULL);
    free(ptr);
}

void CstdAllocator_construct(CstdAllocator* self){
    self->base.alloc_f=CstdAllocator_alloc;
    self->base.free_f=CstdAllocator_free;
}

kt_define(CstdAllocator, NULL, NULL);
