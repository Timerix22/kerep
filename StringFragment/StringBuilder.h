#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../Autoarr/Autoarr.h"
#include "StringFragment.h"

typedef Autoarr(int8) StringBuilder;

StringBuilder StringBuilder_create(uint16 max_blocks_count, uint16 max_block_length);
void StringBuilder_append_char(StringBuilder* b, char c);
void StringBuilder_append_cptr(StringBuilder* b, char* s);
void StringBuilder_append_string(StringBuilder* b, StringFragment s);
void StringBuilder_append_int64(StringBuilder* b, int64 a);
void StringBuilder_append_uint64(StringBuilder* b, uint64 a);
void StringBuilder_append_double(StringBuilder* b, double a);
// returns StringFragment with '\0' at the end
StringFragment StringBuilder_build(StringBuilder* b);

#if __cplusplus
}
#endif