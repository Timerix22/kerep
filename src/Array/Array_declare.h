#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Array_declare(type)\
typedef struct Array_##type{\
    type* values;\
    u32 length;\
    bool allocatedOnHeap;\
} Array_##type;\
\
ktid_declare(Array_##type);\
\
static inline Array_##type Array_##type##_allocValues(u32 length){\
    return (Array_##type) {\
        .values=(type*)malloc(sizeof(type)*length),\
        .length=length,\
        .allocatedOnHeap=true\
    };\
}\
\
static inline Array_##type Array_##type##_fromBuffer(type* buffer, u32 bufferLength, bool allocatedOnHeap){\
    return (Array_##type) {\
        .values=buffer,\
        .length=bufferLength,\
        .allocatedOnHeap=allocatedOnHeap\
    };\
}\
\
static inline void Array_##type##_free(Array_##type* array){\
    if(array->allocatedOnHeap)\
        free(array->values);\
}

#if __cplusplus
}
#endif