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

char* __path_concat(allocator_ptr al, u32 n, ...);
/// @brief merges path parts together and puts <path_sep> between them
/// @return new cstr
#define path_concat(ALLOCATOR, PATH_PARTS...) __path_concat(ALLOCATOR, count_args(PATH_PARTS), PATH_PARTS)

/// @brief fixes path separators
/// @param cstr where can be <path_notSep>
/// @return new cstr with correct separators
char* path_fixSeparators(allocator_ptr al, const char* path);

#define path_resolve(ALLOCATOR, PATH_PARTS...) path_fixSeparators(ALLOCATOR, path_concat(ALLOCATOR, PATH_PARTS))

/// @brief calls safethrow() if finds escape sequense in path
/// @param path cstr where can be <..>
/// @return Maybe<void>
Maybe path_throwIfEscapes(const char* path);

///@return  path of parent dir
char* path_parentDir(allocator_ptr al, char* path);

///@return file name
char* path_basename(allocator_ptr al, char* path, bool with_extension);

#if __cplusplus
}
#endif
