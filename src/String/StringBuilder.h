#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../Autoarr/Autoarr.h"
#include "string.h"

Autoarr_declare(string)

typedef struct StringBuilder{
	Autoarr(string)* compl_bufs;
	Autoarr(int8)* curr_buf;
} StringBuilder;

StringBuilder* StringBuilder_create(void);
void StringBuilder_free(StringBuilder* b);
// Joins all strings from compl_bufs.
// Returns zero-terminated string.
// No need to call string_extract()!
// Frees StringBuilder.
string StringBuilder_build(StringBuilder* b);
// removes last char
void StringBuilder_rmchar(StringBuilder* b);
void StringBuilder_append_char(StringBuilder* b, char c);
void StringBuilder_append_cptr(StringBuilder* b, char* s);
void StringBuilder_append_string(StringBuilder* b, string s);
void StringBuilder_append_int64(StringBuilder* b, int64 a);
void StringBuilder_append_uint64(StringBuilder* b, uint64 a);
void StringBuilder_append_float64(StringBuilder* b, double a);

#if __cplusplus
}
#endif