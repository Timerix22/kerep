#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#if defined(_WIN32) || defined (_WIN64)
static const char path_sep='\\';
static const char path_notSep='/';
#else
static const char path_sep='/';
static const char path_notSep='\\';
#endif

char* __path_concat(uint16 n, ...);
/// @brief merges path parts together and places <path_sep> between them
/// @return new cstr
#define path_concat(PATH_PARTS...) __path_concat(count_args(PATH_PARTS), PATH_PARTS)

/// @brief fixes path separators
/// @param cstr where can be <path_notSep>
/// @return new cstr with correct separators 
char* path_fixSeparators(char* path);

#define path_resolve(PATH_PARTS...) path_fixSeparators(path_concat(PATH_PARTS))

/// @brief calls safethrow() if finds escape sequense in path
/// @param path cstr where can be <..>
/// @return Maybe<void>
Maybe path_throwIfEscapes(char* path);

#if __cplusplus
}
#endif