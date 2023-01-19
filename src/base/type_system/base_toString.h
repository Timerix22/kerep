#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../errors.h"

// char and cstring
// has different output for fmtChar and fmtString
char* __toString_char(void* c, uint32 fmt);

// bool
char* __toString_bool(void* c, uint32 fmt);

// signed int
char* toString_int(int64 n);
char* __toString_int8(void* n, uint32 fmt);
char* __toString_int16(void* n, uint32 fmt);
char* __toString_int32(void* n, uint32 fmt);
char* __toString_int64(void* n, uint32 fmt);

// unsigned int
char* toString_uint(uint64 n, bool withPostfix, bool uppercase);
char* __toString_uint8(void* n, uint32 fmt);
char* __toString_uint16(void* n, uint32 fmt);
char* __toString_uint32(void* n, uint32 fmt);
char* __toString_uint64(void* n, uint32 fmt);

// float
#define toString_float32_max_precision 6
#define toString_float64_max_precision 15
#define toString_float_default_precision 6
char* toString_float32(float32 n, uint8 precision, bool withPostfix, bool uppercase); // uses sprintf
char* toString_float64(float64 n, uint8 precision, bool withPostfix, bool uppercase); // uses sprintf
char* __toString_float32(void* n, uint32 fmt);
char* __toString_float64(void* n, uint32 fmt); 


///@param inverse set to true for little endian numbers (their bytes are in reverse order)
char* toString_bin(void* bytes, uint32 size, bool inverse, bool withPrefix);
///@param inverse set to true for little endian numbers (their bytes are in reverse order)
char* toString_hex(void* bytes, uint32 size, bool inverse, bool withPrefix, bool uppercase);

#if __cplusplus
}
#endif