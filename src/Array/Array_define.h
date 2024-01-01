#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Array_define(type) \
kt_define(Array_##type, (freeMembers_t)Array_##type##_free, NULL);

#if __cplusplus
}
#endif