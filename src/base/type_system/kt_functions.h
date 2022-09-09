#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "ktId.h"
#include "ktDescriptor.h"


extern ktId ktId_last;
void __kt_register(char* name, int16 size, void (*freeMembers)(void*), Maybe (*toString)(void*, int32));

#define kt_register(TYPE, ID_VAR_NAME, FREE_MEMBERS_FUNC, TO_STRING_FUNC)\
    __kt_register(#ID_VAR_NAME, sizeof(TYPE), FREE_MEMBERS_FUNC, TO_STRING_FUNC);\
    ID_VAR_NAME=ktId_last;

void ktDescriptors_beginInit();
void ktDescriptors_endInit();
/// @param id id of registered type 
/// @return Maybe<ktDescriptor*>
Maybe ktDescriptor_get(ktId id);


ktId_declare(ktId_Null);

ktId_declare(ktId_Char);
ktId_declare(ktId_Bool);
ktId_declare(ktId_Float32);
ktId_declare(ktId_Float64);
ktId_declare(ktId_Int8);
ktId_declare(ktId_UInt8);
ktId_declare(ktId_Int16);
ktId_declare(ktId_UInt16);
ktId_declare(ktId_Int32);
ktId_declare(ktId_UInt32);
ktId_declare(ktId_Int64);
ktId_declare(ktId_UInt64);

ktId_declare(ktId_CharPtr);
ktId_declare(ktId_BoolPtr);
ktId_declare(ktId_Float32Ptr);
ktId_declare(ktId_Float64Ptr);
ktId_declare(ktId_Int8Ptr);
ktId_declare(ktId_UInt8Ptr);
ktId_declare(ktId_Int16Ptr);
ktId_declare(ktId_UInt16Ptr);
ktId_declare(ktId_Int32Ptr);
ktId_declare(ktId_UInt32Ptr);
ktId_declare(ktId_Int64Ptr);
ktId_declare(ktId_UInt64Ptr);

ktId_declare(ktId_ktDescriptor);
ktId_declare(ktId_ktDescriptorPtr);

#if __cplusplus
}
#endif