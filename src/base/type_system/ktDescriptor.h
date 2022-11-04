#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "ktid.h"

typedef void (*freeMembers_t)(void*);
typedef char* (*toString_t)(void* obj, uint32 fmt);
typedef struct ktDescriptor{
    char* name;
    ktid id;
    uint16 size;
    freeMembers_t freeMembers; // NULL or function which frees all struct members
    toString_t toString; // NULL or function which generates string representaion of object
} ktDescriptor;

#if __cplusplus
}
#endif