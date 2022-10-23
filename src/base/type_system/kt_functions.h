#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "ktId.h"
#include "ktDescriptor.h"

extern ktId ktId_last;
void __kt_register(char* name, int16 size, void (*freeMembers)(void*), char* (*toString)(void*, uint32));

#define kt_register(TYPE, ID_VAR_NAME, FREE_MEMBERS_FUNC, TO_STRING_FUNC)\
    __kt_register(#ID_VAR_NAME, sizeof(TYPE), FREE_MEMBERS_FUNC, TO_STRING_FUNC);\
    ID_VAR_NAME=ktId_last;

void ktDescriptors_beginInit();
void ktDescriptors_endInit();

/// @param id id of registered type
ktDescriptor ktDescriptor_get(ktId id);


ktId_declare(Null);

ktId_declare(Char);
ktId_declare(Bool);
ktId_declare(Float32);
ktId_declare(Float64);
ktId_declare(Int8);
ktId_declare(UInt8);
ktId_declare(Int16);
ktId_declare(UInt16);
ktId_declare(Int32);
ktId_declare(UInt32);
ktId_declare(Int64);
ktId_declare(UInt64);

ktId_declare(CharPtr);
ktId_declare(BoolPtr);
ktId_declare(Float32Ptr);
ktId_declare(Float64Ptr);
ktId_declare(Int8Ptr);
ktId_declare(UInt8Ptr);
ktId_declare(Int16Ptr);
ktId_declare(UInt16Ptr);
ktId_declare(Int32Ptr);
ktId_declare(UInt32Ptr);
ktId_declare(Int64Ptr);
ktId_declare(UInt64Ptr);

ktId_declare(ktDescriptor);
ktId_declare(ktDescriptorPtr);

#if __cplusplus
}
#endif