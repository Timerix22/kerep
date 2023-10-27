#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../Autoarr/Autoarr.h"
#include "string.h"

STRUCT(StringBuilder,
    InternalAllocator_declare(LinearAllocator);
	Autoarr(string) compl_bufs;
	MemoryChunk curr_buf;
    u64 total_length;
)

///@param external_al if null, creates internal allocator 
void StringBuilder_construct(StringBuilder* b, allocator_ptr external_al);
void StringBuilder_destruct(StringBuilder* b);

// Joins all strings from compl_bufs.
// Returns zero-terminated string.
// No need to call string_extract!
// Destructs StringBuilder.
string StringBuilder_build(StringBuilder* b);

/// OBSOLETE! Will be removed later 
void StringBuilder_rmchar(StringBuilder* b);

void StringBuilder_append_char(StringBuilder* b, char c);
void StringBuilder_append_cptr(StringBuilder* b, char* s);
void StringBuilder_append_string(StringBuilder* b, string s);
void StringBuilder_append_i64(StringBuilder* b, i64 a);
void StringBuilder_append_u64(StringBuilder* b, u64 a);
void StringBuilder_append_f64(StringBuilder* b, f64 a);

#if __cplusplus
}
#endif
