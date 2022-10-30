#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Array_declare(type)\
typedef struct Array_##type{\
    type* values;\
    uint32 length;\
    bool allocatedOnHeap;\
} Array_##type;\
\
\
static inline Array_##type Array_##type##_allocValues(uint32 length){\
    return (Array_##type) {\
        .values=(type##*)malloc(sizeof(type)*length),\
        .length=length,\
        .allocatedOnHeap=true\
    };\
}\
\
static inline Array_##type Array_##type##_fromBuffer(type##* buffer, uint32 bufferLength, bool allocatedOnHeap){\
    return (Array_##type) {\
        .values=buffer,\
        .length=bufferLength,\
        .allocatedOnHeap=allocatedOnHeap\
    };\
}\
\
static inline void Array_##type##_freeValues(Array_##type* array){\
    if(array->allocatedOnHeap)\
        free(array->values);\
}

#if __cplusplus
}
#endif