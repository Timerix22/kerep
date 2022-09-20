#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
typedef uint16 ktId;

#define ktId_declare(TYPE_NAME)\
    extern ktId ktId_##TYPE_NAME
#define ktId_define(TYPE_NAME)\
    ktId ktId_##TYPE_NAME=-1

#if __cplusplus
}
#endif