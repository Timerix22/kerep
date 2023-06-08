#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "../type_system/ktDescriptor.h"
#include "allocator_base.h"

///////////////////////////////////////////
//             CstdAllocator             //
///////////////////////////////////////////
// Just wrapper for malloc() and free()  // 
///////////////////////////////////////////

STRUCT(CstdAllocator,
    MemoryAllocator base;
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
    alloc_size_t size;
    alloc_size_t occupied_size;  /* free memory position in the current chunk. */
} MemoryChunk;

STRUCT(LinearAllocator,
    MemoryAllocator base;
    MemoryChunk* chunks;    /* MemoryChunk[max_chunks_count] */
    u32 chunks_count;       /* allocated chunks */
    u32 max_chunks_count;   /* chunks that can be allocated without reallocating .chunks */
    u32 curr_chunk_i;       /* index of current chunk in .chunks, can be < .chunks_count */
);

void LinearAllocator_construct(LinearAllocator* self, alloc_size_t starting_size);
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

void StackingAllocator_construct(StackingAllocator* self, alloc_size_t starting_size);
void StackingAllocator_destruct(StackingAllocator* self);


#if __cplusplus
}
#endif
