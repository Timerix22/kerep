#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../errors.h"

// functions for base types
char* __toString_char(void* c, uint32 fmt);
char* __toString_charPtr(void* c, uint32 fmt);
char* __toString_bool(void* c, uint32 fmt);

char* toString_int(int64 n);
char* __toString_int8(void* n, uint32 fmt);
char* __toString_int16(void* n, uint32 fmt);
char* __toString_int32(void* n, uint32 fmt);
char* __toString_int64(void* n, uint32 fmt);

char* toString_uint(uint64 n, bool withPostfix, bool uppercase);
char* __toString_uint8(void* n, uint32 fmt);
char* __toString_uint16(void* n, uint32 fmt);
char* __toString_uint32(void* n, uint32 fmt);
char* __toString_uint64(void* n, uint32 fmt);

char* toString_float(float64 n, bool withPostfix, bool uppercase); // very bad implimentation
char* __toString_float32(void* n, uint32 fmt);
char* __toString_float64(void* n, uint32 fmt);

// universal functions
char* toString_bin(void* bytes, uint32 size, bool withPrefix);
char* toString_hex(void* bytes, uint32 size, bool withPrefix, bool uppercase);

#if __cplusplus
}
#endif