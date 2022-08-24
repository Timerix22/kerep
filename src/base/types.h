#pragma once

#if __cplusplus
extern "C" {
#endif

#include "std.h"

typedef uint16 kerepTypeId;

typedef struct kerepTypeDescriptor{
    void (*free_members)(void*); // NULL or function which frees all struct members
    char* name;
    kerepTypeId id;
    uint16 size;
} kerepTypeDescriptor;

#define kerepType_declare(NAME)\
    extern kerepTypeId kerepTypeId_##NAME

extern kerepTypeId kerepTypeId_last;
void __kerepType_register(char* name, int16 size, void (*free_members)(void*));

#define kerepType_register(TYPE, NAME, FREE_MEMBERS_FUNC)\
    __kerepType_register(#NAME, sizeof(TYPE), FREE_MEMBERS_FUNC);\
    kerepTypeId_##NAME=kerepTypeId_last;

void kerepTypeDescriptors_beginInit();
void kerepTypeDescriptors_endInit();
kerepTypeDescriptor kerepTypeDescriptor_get(kerepTypeId id);

kerepType_declare(Null);

kerepType_declare(Char);
kerepType_declare(Bool);
kerepType_declare(Float32);
kerepType_declare(Float64);
kerepType_declare(Int8);
kerepType_declare(UInt8);
kerepType_declare(Int16);
kerepType_declare(UInt16);
kerepType_declare(Int32);
kerepType_declare(UInt32);
kerepType_declare(Int64);
kerepType_declare(UInt64);

kerepType_declare(CharPtr);
kerepType_declare(BoolPtr);
kerepType_declare(Float32Ptr);
kerepType_declare(Float64Ptr);
kerepType_declare(Int8Ptr);
kerepType_declare(UInt8Ptr);
kerepType_declare(Int16Ptr);
kerepType_declare(UInt16Ptr);
kerepType_declare(Int32Ptr);
kerepType_declare(UInt32Ptr);
kerepType_declare(Int64Ptr);
kerepType_declare(UInt64Ptr);

#if __cplusplus
}
#endif