#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Autoarr_declare(TYPE) \
\
typedef struct Autoarr_##TYPE Autoarr_##TYPE; \
\
typedef struct __Autoarr_##TYPE##_functions_list_t { \
    void (*add)(Autoarr_##TYPE* ar, TYPE element); \
    TYPE (*get)(Autoarr_##TYPE* ar, u32 index); \
    TYPE* (*getPtr)(Autoarr_##TYPE* ar, u32 index); \
    void (*set)(Autoarr_##TYPE* ar, u32 index, TYPE element); \
    TYPE* (*toArray)(Autoarr_##TYPE* ar, allocator_ptr array_holder); \
} __Autoarr_##TYPE##_functions_list_t; \
\
STRUCT(Autoarr_##TYPE, \
    InternalAllocator_declare(LinearAllocator); \
    __Autoarr_##TYPE##_functions_list_t* functions; \
    ktDescriptor* type; \
    u32 length; \
    TYPE* _typeof_target; \
) \
\
void __Autoarr_##TYPE##_construct(Autoarr_##TYPE* ar, alloc_size_t starting_size, allocator_ptr external_al); \
void __Autoarr_##TYPE##_destruct(Autoarr_##TYPE* ar); \

#define Autoarr(TYPE) Autoarr_##TYPE

#define Autoarr_construct(ptr, TYPE, starting_size, data_allocator) \
    __Autoarr_##TYPE##_construct(ptr, starting_size, data_allocator)
#define Autoarr_destruct(autoarr)               (autoarr)->type->destruct(autoarr)
#define Autoarr_add(autoarr, element)           (autoarr)->functions->add(autoarr, element)
#define Autoarr_get(autoarr, index)             (autoarr)->functions->get(autoarr,index)
#define Autoarr_getPtr(autoarr, index)          (autoarr)->functions->getPtr(autoarr,index)
#define Autoarr_set(autoarr, index, element)    (autoarr)->functions->set(autoarr, index, element)
#define Autoarr_toArray(autoarr, array_alloctr) (autoarr)->functions->toArray(autoarr, array_alloctr)
#define Autoarr_length(autoarr)                 (autoarr)->length
#define Autoarr_pop(autoarr) { \
    u32 new_len=(autoarr)->length-1; \
    allocator_free(InternalAllocator_getPtr((autoarr)), Autoarr_getPtr((autoarr), new_len)); \
    (autoarr)->length=new_len; \
}

#define Autoarr_foreach(ar, elem, codeblock...) { \
    if((ar)->length > 0) { \
        typeof(*((ar)->_typeof_target)) elem; \
        LinearAllocator* al=(LinearAllocator*)InternalAllocator_getPtr(ar); \
        for(u16 chunk_i=0; chunk_i <= al->curr_chunk_i; chunk_i++) { \
            MemoryChunk chunk = al->chunks[chunk_i]; \
            alloc_size_t chunk_elem_count = chunk.occupied_size/sizeof(elem); \
            typeof((ar)->_typeof_target) chunk_data = (void*)chunk.data; \
            for(u32 elem##_i=0; elem##_i < chunk_elem_count; elem##_i++) { \
                elem = chunk_data[elem##_i]; \
                { codeblock; } \
            } \
        } \
    } \
}

#if __cplusplus
}
#endif
