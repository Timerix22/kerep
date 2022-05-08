#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

// djb2 hash function from http:// www.cse.yorku.ca/~oz/hash.html
uint32 hash32(char *str);
// sdbm hash function
uint64 hash64(char* str);

#if __cplusplus
}
#endif