#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#if defined(_WIN32) || defined (_WIN64)
static const char path_sep='\\';
#else
static const char path_sep='/';
#endif

char* __path_concat(uint16 n, char* path_start, ...);
#define path_concat(PATH_PARTS) __path_concat(count_args(PATH_PARTS), PATH_PARTS)

#if __cplusplus
}
#endif