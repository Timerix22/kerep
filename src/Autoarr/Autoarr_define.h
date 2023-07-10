#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Autoarr_define(TYPE, TYPE_IS_PTR) \
\
void __Autoarr_##TYPE##_add(Autoarr_##TYPE* ar, TYPE element){ \
    TYPE* ptr = allocator_alloc(InternalAllocator_getPtr(ar), sizeof(element)); \
    *ptr=element; \
    ar->length++; \
} \
\
TYPE* __Autoarr_##TYPE##_getPtr(Autoarr_##TYPE* ar, u32 index){ \
    if(index >= Autoarr_length(ar)) \
        throw(ERR_WRONGINDEX); \
    u32 elem_count_sum=0; \
    LinearAllocator* al=(LinearAllocator*)InternalAllocator_getPtr(ar); \
    for(u16 chunk_i=0; chunk_i <= al->curr_chunk_i; chunk_i++) { \
        MemoryChunk chunk = al->chunks[chunk_i]; \
        alloc_size_t chunk_elem_count = chunk.occupied_size/sizeof(TYPE); \
        alloc_size_t chunk_elem_i = index - elem_count_sum; \
        if(chunk_elem_i < chunk_elem_count){ \
            return chunk.data + chunk_elem_i*sizeof(TYPE); \
        } \
        elem_count_sum += chunk_elem_count; \
    } \
    return NULL; \
} \
\
TYPE __Autoarr_##TYPE##_get(Autoarr_##TYPE* ar, u32 index){ \
    TYPE* ptr=__Autoarr_##TYPE##_getPtr(ar, index); \
    return *ptr; \
} \
\
void __Autoarr_##TYPE##_set(Autoarr_##TYPE* ar, u32 index, TYPE value){ \
    TYPE* ptr=__Autoarr_##TYPE##_getPtr(ar, index); \
    *ptr=value; \
} \
\
void __Autoarr_##TYPE##_destruct(Autoarr_##TYPE* ar){ \
    destruct_t value_destructor=ar->type->destruct; \
    if(value_destructor!=NULL) { \
        Autoarr_foreach(ar, el, \
            TYPE* value_ptr = TYPE_IS_PTR ? *(TYPE**)(&el) : &el; \
            value_destructor(value_ptr); \
        ); \
    } \
    InternalAllocator_destructIfInternal(LinearAllocator, ar); \
} \
\
TYPE* __Autoarr_##TYPE##_toArray(Autoarr_##TYPE* ar, allocator_ptr array_alloctr){ \
    u32 length=Autoarr_length(ar); \
    if(length==0) \
        return NULL; \
    TYPE* array=allocator_alloc(array_alloctr, length); \
    Autoarr_foreach(ar, el, { \
        array[el_i]=el; \
    }); \
    return array; \
} \
\
__Autoarr_##TYPE##_functions_list_t __Autoarr_##TYPE##_functions_list={ \
    &__Autoarr_##TYPE##_add, \
    &__Autoarr_##TYPE##_get, \
    &__Autoarr_##TYPE##_getPtr, \
    &__Autoarr_##TYPE##_set, \
    &__Autoarr_##TYPE##_toArray \
}; \
\
void __Autoarr_##TYPE##_construct(Autoarr_##TYPE* ar, alloc_size_t starting_size, allocator_ptr data_allocator){ \
    InternalAllocator_setExternalOrConstruct(ar, data_allocator, LinearAllocator, starting_size); \
    ar->functions=&__Autoarr_##TYPE##_functions_list; \
    ar->type = TYPE_IS_PTR ? &ktDescriptor_namePtr(TYPE) : &ktDescriptor_name(TYPE); \
    ar->length=0; \
} \
\
kt_define(Autoarr_##TYPE, (destruct_t)__Autoarr_##TYPE##_destruct, NULL);

#if __cplusplus
}
#endif
