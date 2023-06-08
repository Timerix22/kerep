#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Autoarr_define(type, TYPE_IS_PTR) \
\
kt_define(Autoarr_##type, ____Autoarr_##type##_destructWithMembers, NULL); \
\
void __Autoarr_##type##_add(Autoarr_##type* ar, type element){ \
    if(!ar->chunks){ \
        ar->chunks=malloc(ar->max_chunks_count*sizeof(type*)); \
        goto create_chunk; \
    } \
    if(ar->chunk_length==ar->max_chunk_length){ \
        if (ar->chunks_count>=ar->max_chunks_count) throw(ERR_MAXLENGTH); \
        ar->chunk_length=0; \
create_chunk: \
        ar->chunks[ar->chunks_count]=malloc(ar->max_chunk_length*sizeof(type)); \
        ar->chunks_count++; \
    } \
    ar->chunks[ar->chunks_count-1][ar->chunk_length]=element; \
    ar->chunk_length++; \
} \
\
type __Autoarr_##type##_get(Autoarr_##type* ar, u32 index){ \
    if(index>=Autoarr_length(ar)) throw(ERR_WRONGINDEX); \
    return ar->chunks[index/ar->max_chunk_length][index%ar->max_chunk_length]; \
} \
\
type* __Autoarr_##type##_getPtr(Autoarr_##type* ar, u32 index){ \
    if(index>=Autoarr_length(ar)) throw(ERR_WRONGINDEX); \
    return ar->chunks[index/ar->max_chunk_length]+(index%ar->max_chunk_length); \
} \
\
void __Autoarr_##type##_set(Autoarr_##type* ar, u32 index, type element){ \
    if(index>=Autoarr_length(ar)) throw(ERR_WRONGINDEX); \
    ar->chunks[index/ar->max_chunk_length][index%ar->max_chunk_length]=element; \
} \
\
void __Autoarr_##type##_destructWithoutMembers(Autoarr_##type* ar, bool freePtr){ \
    for(u16 i=0; i<ar->chunks_count;i++) \
        free(ar->chunks[i]); \
    free(ar->chunks); \
    if(freePtr) free(ar); \
} \
\
void __Autoarr_##type##_destructWithMembers(Autoarr_##type* ar, bool freePtr){ \
    if(ktDescriptor_##type.freeMembers!=NULL) { \
        Autoarr_foreach(ar, el,  \
            void* members_ptr=&el; \
            if(TYPE_IS_PTR) members_ptr=*(type**)members_ptr; \
            ktDescriptor_##type.freeMembers(members_ptr); \
        ); \
    } \
    __Autoarr_##type##_destructWithoutMembers(ar, freePtr); \
} \
void ____Autoarr_##type##_destructWithMembers(void* ar){ \
    __Autoarr_##type##_destructWithMembers((Autoarr_##type*)ar, false); \
} \
\
type* __Autoarr_##type##_toArray(Autoarr_##type* ar){ \
    u32 length=Autoarr_length(ar); \
    if(length==0) \
        return NULL; \
    type* array=malloc(length * sizeof(type)); \
    for(u32 i=0; i<length; i++) \
        array[i]=__Autoarr_##type##_get(ar, i); \
    return array; \
} \
\
__Autoarr_##type##_functions_list_t __Autoarr_##type##_functions_list={ \
    &__Autoarr_##type##_add, \
    &__Autoarr_##type##_get, \
    &__Autoarr_##type##_getPtr, \
    &__Autoarr_##type##_set, \
    &__Autoarr_##type##_destructWithMembers, \
    &__Autoarr_##type##_destructWithoutMembers, \
    &__Autoarr_##type##_toArray \
}; \
\
Autoarr_##type* __Autoarr_##type##_create(u16 max_chunks_count, u16 max_chunk_length){ \
    Autoarr_##type* ar=malloc(sizeof(Autoarr_##type)); \
    *ar=(Autoarr_##type){ \
        .max_chunks_count=max_chunks_count, \
        .chunks_count=0, \
        .max_chunk_length=max_chunk_length, \
        .chunk_length=0, \
        .chunks=NULL, \
        .functions=&__Autoarr_##type##_functions_list \
    }; \
    return ar; \
}

#if __cplusplus
}
#endif
