#pragma once

#if __cplusplus
extern "C" {
#endif

#include "std.h"

typedef uint16 kerepTypeId;

typedef struct kerepTypeDescriptor{
    char* name;
    kerepTypeId id;
    uint16 size;
    void (*freeMembers)(void*); // NULL or function which frees all struct members
    ///@return Maybe<char*>
    Maybe (*toString)(void*, int32); // NULL or function which generates string representaion of object
} kerepTypeDescriptor;

#define kerepTypeId_declare(ID_VAR_NAME)\
    extern kerepTypeId ID_VAR_NAME
#define kerepTypeId_define(ID_VAR_NAME)\
    kerepTypeId ID_VAR_NAME=-1

extern kerepTypeId kerepTypeId_last;
void __kerepType_register(char* name, int16 size, void (*freeMembers)(void*), char* (*toString)(void*, int32));

#define kerepType_register(TYPE, ID_VAR_NAME, FREE_MEMBERS_FUNC, TO_STRING_FUNC)\
    __kerepType_register(#ID_VAR_NAME, sizeof(TYPE), FREE_MEMBERS_FUNC, TO_STRING_FUNC);\
    ID_VAR_NAME=kerepTypeId_last;

void kerepTypeDescriptors_beginInit();
void kerepTypeDescriptors_endInit();
/// @param id id of registered type 
/// @return Maybe<kerepTypeDescriptor*>
Maybe kerepTypeDescriptor_get(kerepTypeId id);

kerepTypeId_declare(kerepTypeId_Null);

kerepTypeId_declare(kerepTypeId_Char);
kerepTypeId_declare(kerepTypeId_Bool);
kerepTypeId_declare(kerepTypeId_Float32);
kerepTypeId_declare(kerepTypeId_Float64);
kerepTypeId_declare(kerepTypeId_Int8);
kerepTypeId_declare(kerepTypeId_UInt8);
kerepTypeId_declare(kerepTypeId_Int16);
kerepTypeId_declare(kerepTypeId_UInt16);
kerepTypeId_declare(kerepTypeId_Int32);
kerepTypeId_declare(kerepTypeId_UInt32);
kerepTypeId_declare(kerepTypeId_Int64);
kerepTypeId_declare(kerepTypeId_UInt64);

kerepTypeId_declare(kerepTypeId_CharPtr);
kerepTypeId_declare(kerepTypeId_BoolPtr);
kerepTypeId_declare(kerepTypeId_Float32Ptr);
kerepTypeId_declare(kerepTypeId_Float64Ptr);
kerepTypeId_declare(kerepTypeId_Int8Ptr);
kerepTypeId_declare(kerepTypeId_UInt8Ptr);
kerepTypeId_declare(kerepTypeId_Int16Ptr);
kerepTypeId_declare(kerepTypeId_UInt16Ptr);
kerepTypeId_declare(kerepTypeId_Int32Ptr);
kerepTypeId_declare(kerepTypeId_UInt32Ptr);
kerepTypeId_declare(kerepTypeId_Int64Ptr);
kerepTypeId_declare(kerepTypeId_UInt64Ptr);

kerepTypeId_declare(kerepTypeId_kerepTypeDescriptor);
kerepTypeId_declare(kerepTypeId_kerepTypeDescriptorPtr);

#if __cplusplus
}
#endif