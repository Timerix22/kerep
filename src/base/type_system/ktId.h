#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
typedef uint16 ktid;

#define ktid_name(TYPE) ktid_##TYPE
#define ktid_ptrName(TYPE) ktid_##TYPE##_Ptr

#define ktid_declare(TYPE)\
    extern ktid ktid_##TYPE;\
    extern ktid ktid_##TYPE##_Ptr;

#define ktid_define(TYPE)\
    ktid ktid_##TYPE=-1;\
    ktid ktid_##TYPE##_Ptr=-1;

#if __cplusplus
}
#endif