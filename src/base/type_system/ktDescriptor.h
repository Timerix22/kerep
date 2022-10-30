#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "ktId.h"

typedef struct ktDescriptor{
    char* name;
    ktId id;
    uint16 size;
    void (*freeMembers)(void*); // NULL or function which frees all struct members
    char* (*toString)(void* obj, uint32 fmt); // NULL or function which generates string representaion of object
} ktDescriptor;

#if __cplusplus
}
#endif