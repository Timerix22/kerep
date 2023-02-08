#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "file.h"

bool dir_exists(char* path);
///@return Maybe<void>
Maybe dir_create(char* path);
///@return Maybe<void>
Maybe dir_delete(char* path);

///@return Maybe<Array_string>
Maybe dir_getFiles(char* path, bool recursive);
///@return Maybe<Array_string>
Maybe dir_getDirs(char* path, bool recursive);

///@return Maybe<Array_string>
Maybe dir_findFiles(char* path, char* searchPattern, bool recursive);
///@return Maybe<Array_string>
Maybe dir_findDirs(char* path, char* searchPattern, bool recursive);

#if __cplusplus
}
#endif