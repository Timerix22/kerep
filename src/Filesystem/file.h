#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "../Array/Array.h"
#include "../String/string.h"

typedef FILE File;
ktid_declare(File);

bool file_exists(const char* path);

///@return Maybe<void>
Maybe file_delete(const char* path, bool recursive);

PACK_ENUM(FileOpenMode,
    // open a file for reading 
    FileOpenMode_Read=1, 
    // (re)create a file for writing
    FileOpenMode_Write=2, 
    // opens file for writing additional data to the end / creates new file 
    FileOpenMode_Append=4,
    // (re)creates file for reading/writing
    FileOpenMode_ReadWrite=FileOpenMode_Read|FileOpenMode_Write, 
    // opens file for readng/writing additional data to the end / creates new file 
    FileOpenMode_ReadAppend=FileOpenMode_Read|FileOpenMode_Append
)

/// @brief opens file
/// @param path path to file
/// @param mode Read/Write/Append/ReadWrite/ReadAppend
/// @return Maybe<File*>
Maybe file_open(const char* path, FileOpenMode mode);

/// @brief closes file descriptor
/// @return Maybe<void>
Maybe file_close(File* file);

/// @brief closes file descriptor
/// @param byte byte to write
/// @return Maybe<void>
Maybe file_writeChar(File* file, char byte);

/// @brief closes file descriptor
/// @param buffer bytes to write
/// @param length buffer length
/// @return Maybe<void>
Maybe file_writeBuffer(File* file, char* buffer, uint64 length);

/// @brief writes all cstring array content to file
/// @param cptr zero-terminated cstring
/// @return Maybe<void>
Maybe file_writeCptr(File* file, char* cptr);


/// @brief reads single byte from file
/// @return Maybe<char>
Maybe file_readChar(File* file);

/// @brief reads byte array of specofied length
/// @param buffer buffer that will be filled with file bytes
/// @param length buffer length
/// @return Maybe<uint64> total number of successfully read bytes (<=length)
Maybe file_readBuffer(File* file, char* buffer, uint64 length);

/// @brief reads all bytes from file
/// @param allBytes ptr to the file's content will be pushed there 
/// @return Maybe<uint64> total number of successfully read bytes
Maybe file_readAll(File* file, char** allBytes);

#if __cplusplus
}
#endif