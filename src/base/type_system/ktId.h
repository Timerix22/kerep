#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
typedef uint16 ktId;

#define ktId_declare(ID_VAR_NAME)\
    extern ktId ID_VAR_NAME
#define ktId_define(ID_VAR_NAME)\
    ktId ID_VAR_NAME=-1

#if __cplusplus
}
#endif