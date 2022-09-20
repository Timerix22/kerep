#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

// my fixed length string struct
// doesn't store '\0' at the end
typedef struct string{
    char* ptr;      // char pointer
    uint32 length;  // amount of chars in ptr value
} string;
ktId_declare(string);
ktId_declare(stringPtr);

static const string stringNull={NULL,0};

// copies str content to new char pointer value (adding '\0' at the end)
char* string_extract(string str);

// copies src.ptr content to new string
string string_copy(string src);

// compares two strings, NullPtr-friendly
bool string_compare(string str0, string str1);

// creates new string which is reversed variant of <s>
string string_reverse(string s);

#if __cplusplus
}
#endif