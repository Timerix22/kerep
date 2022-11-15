#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "file.h"

typedef char* DirPath;
Array_declare(DirPath);

Array_FilePath dir_getFiles(DirPath path);
Array_FilePath dir_findFiles(DirPath path, FilePath searchPattern);

#if __cplusplus
}
#endif