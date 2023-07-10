#include "tests.h"

void _test_allocator(allocator_ptr al){
    void* ptr=allocator_alloc(al, 1);
    allocator_free(al, ptr);
    ptr=allocator_alloc(al, 5);
    allocator_free(al, ptr);
    ptr=allocator_alloc(al, 41);
    allocator_free(al, ptr);
    ptr=allocator_alloc(al, 19);
    void* ptr1=allocator_alloc(al, 1);
    void* ptr2=allocator_alloc(al, 5);
    // allocator_free(al, ptr); // temp case
    allocator_free(al, ptr2);
    allocator_free(al, ptr1);
    allocator_free(al, ptr);
    ptr=allocator_alloc(al, 500);
    ptr1=allocator_alloc(al, 1025);
    allocator_free(al, ptr1);
    allocator_free(al, ptr);/*
    ptr=allocator_alloc(al, 5000);
    ptr1=allocator_alloc(al, 5000000);
    allocator_free(al, ptr1);
    allocator_free(al, ptr);*/
}


void test_allocators(){
    kprintf("\e[96m----------[test_allocators]-----------\n");
    optime("test CstdAllocator", 10000,
        _test_allocator(CstdAllocator_instPtr);
    );
    optime("test LinearAllocator", 10000,
        LinearAllocator al;
        LinearAllocator_construct(&al, 4096);
        _test_allocator((allocator_ptr)&al);
        LinearAllocator_destruct(&al);
    );
    optime("test StackingAllocator", 10000,
        StackingAllocator al;
        StackingAllocator_construct(&al, 4096);
        _test_allocator((allocator_ptr)&al);
        StackingAllocator_destruct(&al);
    );
}
