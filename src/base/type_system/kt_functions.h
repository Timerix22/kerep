#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
#include "ktid.h"
#include "ktDescriptor.h"

extern ktid ktid_last;
void __kt_register(char* name, int16 size, void (*freeMembers)(void*), char* (*toString)(void*, uint32));

#define kt_register(TYPE, FREE_MEMBERS_FUNC, TO_STRING_FUNC)\
    __kt_register(#TYPE, sizeof(TYPE), FREE_MEMBERS_FUNC, TO_STRING_FUNC);\
    ktid_##TYPE=ktid_last;\
    __kt_register(#TYPE "*", sizeof(TYPE), FREE_MEMBERS_FUNC, TO_STRING_FUNC);\
    ktid_##TYPE##_Ptr=ktid_last;

void ktDescriptors_beginInit();
void ktDescriptors_endInit();

/// @param id id of registered type
ktDescriptor ktDescriptor_get(ktid id);

// call it to free heap-allocated ktDescriptors array
void ktDescriptors_free();

extern ktid ktid_Null;

ktid_declare(char);
ktid_declare(bool);
ktid_declare(float32);
ktid_declare(float64);
ktid_declare(int8);
ktid_declare(uint8);
ktid_declare(int16);
ktid_declare(uint16);
ktid_declare(int32);
ktid_declare(uint32);
ktid_declare(int64);
ktid_declare(uint64);

ktid_declare(ktDescriptor);

#if __cplusplus
}
#endif