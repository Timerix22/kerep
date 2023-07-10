#include "allocators_internal.h"

void* CstdAllocator_alloc(allocator_ptr self, alloc_size_t size){
    // assert(size>0);
    return malloc(size);
}

void CstdAllocator_free(allocator_ptr self, void* ptr){
    // assert(ptr!=NULL);
    free(ptr);
}

kt_define(CstdAllocator, NULL, NULL);

CstdAllocator CstdAllocator_instance=(CstdAllocator){.base.alloc_f=CstdAllocator_alloc, .base.free_f=CstdAllocator_free};
