#include "filesystem.h"
#include "io_includes.h"

bool dir_exists(char* path){
#if KFS_USE_WINDOWS_H
    DWORD dwAttrib = GetFileAttributes(path);
    return (bool)(
        (dwAttrib != INVALID_FILE_ATTRIBUTES) & // file exists
        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)); // file is a directory
#else
    struct stat stats;
    int rez=stat(path, &stats);
    return (bool)(
        (rez!=-1) & // file exists
        (S_ISDIR(stats.st_mode))); // file is a directory
#endif
}

Maybe dir_create(char* path){
    if (dir_exists(path))
        return MaybeNull;
    char* parentDir=path_parentDir(path);
    dir_create(parentDir);
    free(parentDir);
    throw(ERR_NOTIMPLEMENTED);
    return MaybeNull;
}

Maybe dir_delete(char* path){
    throw(ERR_NOTIMPLEMENTED);
    return MaybeNull;
}

Maybe dir_getFiles(char* path, bool recursive){
    throw(ERR_NOTIMPLEMENTED);
    return MaybeNull;
}
Maybe dir_getDirs(char* path, bool recursive){
    throw(ERR_NOTIMPLEMENTED);
    return MaybeNull;
}

Maybe dir_findFiles(char* path, char* searchPattern, bool recursive){
    throw(ERR_NOTIMPLEMENTED);
    return MaybeNull;
}
Maybe dir_findDirs(char* path, char* searchPattern, bool recursive){
    throw(ERR_NOTIMPLEMENTED);
    return MaybeNull;
}
