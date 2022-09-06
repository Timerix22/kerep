#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../std.h"
typedef uint16 kerepTypeId;

#define kerepTypeId_declare(ID_VAR_NAME)\
    extern kerepTypeId ID_VAR_NAME
#define kerepTypeId_define(ID_VAR_NAME)\
    kerepTypeId ID_VAR_NAME=-1

#if __cplusplus
}
#endif