#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Array_define(type)\
ktid_define(Array_##type);

#if __cplusplus
}
#endif