#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../std.h"

///////////////////////////////////////////
//       MemoryAllocator interface       //
///////////////////////////////////////////

typedef u32 alloc_size_t;
typedef struct MemoryAllocator MemoryAllocator;
typedef MemoryAllocator* allocator_ptr;

typedef void* (*alloc_t)(allocator_ptr, alloc_size_t size);
typedef void (*free_t)(allocator_ptr, void* ptr);

typedef struct MemoryAllocator {
    alloc_t alloc_f;
    free_t free_f;
} MemoryAllocator;

#define allocator_alloc(ALLOCATOR, SIZE) \
    ((allocator_ptr)ALLOCATOR)->alloc_f(ALLOCATOR, SIZE)
#define allocator_free(ALLOCATOR, PTR) \
    ((allocator_ptr)ALLOCATOR)->free_f(ALLOCATOR, PTR)
#define allocator_destruct(ALLOCATOR) \
    ((allocator_ptr)ALLOCATOR)->destruct_f(ALLOCATOR)

void* allocator_transfer(allocator_ptr src, allocator_ptr dest, void* data, alloc_size_t data_size);

#ifdef __cplusplus
}
#endif
