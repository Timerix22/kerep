#pragma once

#if __cplusplus
extern "C" {
#endif

#include "std.h"

// returns length of char buffer (without \0)
u32 cptr_length(char* str);

// allocates new char[] and copies src there
char* cptr_copy(char* src);

// compares two char buffers, NullPtr-friendly
bool cptr_compare(char* key0, char* key1);

// multiplies char n times
char* char_multiply(char c, u32 n);

bool cptr_startsWith(char* ptr, char* fragment);

bool cptr_endsWith(char* ptr, char* fragment);

/// @brief search for <fragment> in <ptr>
/// @return index of first <fragment> inclusion or -1 if not found
u32 cptr_indexOf(char* ptr, char* fragment);
/// @brief search for <fragment> in <ptr>
/// @return index of first <fragment> inclusion or -1 if not found
u32 cptr_indexOfChar(char* ptr, char fragment);
/// @brief search for <fragment> in <ptr>
/// @return index of last <fragment> inclusion or -1 if not found
u32 cptr_lastIndexOf(char* ptr, char* fragment);
/// @brief search for <fragment> in <ptr>
/// @return index of last <fragment> inclusion or -1 if not found
u32 cptr_lastIndexOfChar(char* ptr, char fragment);

static inline bool cptr_contains(char* ptr, char* fragment){
    // if(cptr_indexOf(ptr, fragment)==-1)
    //     return false;
    // return true;
    return cptr_indexOf(ptr, fragment) +1;
}

void memcopy(void* from, void* to, u32 size);

char* __cptr_concat(u16 n, ...);
#define cptr_concat(STR...) __cptr_concat(count_args(STR), STR)

#if __cplusplus
}
#endif