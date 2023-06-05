#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "../type_system/ktDescriptor.h"

///////////////////////////////////////////
//       MemoryAllocator interface       //
///////////////////////////////////////////

typedef struct MemoryAllocator allocator_t;

typedef void* (*alloc_t)(allocator_t*, size_t size);
typedef void (*free_t)(allocator_t*, void* ptr);

typedef struct MemoryAllocator {
    alloc_t alloc_f;
    free_t free_f;
} allocator_t;

#define allocator_alloc(ALLOCATOR, SIZE) \
    ((allocator_t*)ALLOCATOR)->alloc_f(ALLOCATOR, SIZE)
#define allocator_free(ALLOCATOR, PTR) \
    ((allocator_t*)ALLOCATOR)->free_f(ALLOCATOR, PTR)
#define allocator_destruct(ALLOCATOR) \
    ((allocator_t*)ALLOCATOR)->destruct_f(ALLOCATOR)

void* allocator_transfer(allocator_t* src, allocator_t* dest, void* data, size_t data_size);


///////////////////////////////////////////
//             CstdAllocator             //
///////////////////////////////////////////
// Just wrapper for malloc() and free()  // 
///////////////////////////////////////////

STRUCT(CstdAllocator,
    allocator_t base;
);

void CstdAllocator_construct(CstdAllocator* self);


///////////////////////////////////////////
//            LinearAllocator            //
///////////////////////////////////////////
// Can't free allocated memory.          //
// Allocates new memory chunk when the   //
// current is full.                      // 
///////////////////////////////////////////

typedef struct MemoryChunk {
    void* data;
    size_t size;
    size_t occupied_size;  /* free memory position in the current chunk. */
} MemoryChunk;

STRUCT(LinearAllocator,
    allocator_t base;
    MemoryChunk* chunks;    /* MemoryChunk[max_chunks_count] */
    u16 chunks_count;       /* allocated chunks */
    u16 max_chunks_count;   /* chunks that can be allocated without reallocating .chunks */
    u16 curr_chunk_i;       /* index of current chunk in .chunks, can be < .chunks_count */
);

void LinearAllocator_construct(LinearAllocator* self, size_t starting_size);
void LinearAllocator_destruct(LinearAllocator* self);


///////////////////////////////////////////
//           StackingAllocator           //
///////////////////////////////////////////
// The same as Linear, but can free      //
// allocations in reverse order          // 
///////////////////////////////////////////

STRUCT(StackingAllocator,
    LinearAllocator base;
    u32 allocations_count;
);

void StackingAllocator_construct(StackingAllocator* self, size_t starting_size);
void StackingAllocator_destruct(StackingAllocator* self);


#if __cplusplus
}
#endif
