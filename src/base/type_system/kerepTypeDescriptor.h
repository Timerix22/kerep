#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "../errors.h"
#include "kerepTypeId.h"

typedef struct kerepTypeDescriptor{
    char* name;
    kerepTypeId id;
    uint16 size;
    void (*freeMembers)(void*); // NULL or function which frees all struct members
    ///@return Maybe<char*>
    Maybe (*toString)(void*, int32); // NULL or function which generates string representaion of object
} kerepTypeDescriptor;

#if __cplusplus
}
#endif