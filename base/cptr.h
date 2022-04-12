#pragma once

#if __cplusplus
extern "C" {
#endif

#include "types.h"

//returns length of string (without \0)
uint32 cptr_length(char* str);

//allocates new char[] and copies src there
char* cptr_copy(char* src);

//compares two char buffers, NullPtr-friendly
bool cptr_compare(char* key0, char* key1);

//multiplies char n times
char* char_multiply(char c, uint32 n);

#if __cplusplus
}
#endif