#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../../base/std.h"
#include "../../splitmix64/splitmix64.h"


typedef union {
  uint32 s[2];
} xoroshiro128_state;
typedef void* xoroshiro128_statePtr;

xoroshiro128_statePtr xoroshiro128_init(uint64 seed);
#define xoroshiro128plus_init xoroshiro128_init
#define xoroshiro128plusplus_init xoroshiro128_init
#define xoroshiro128starstar_init xoroshiro128_init

static inline xoroshiro128_statePtr xoroshiro128_initFromTime(void) { return xoroshiro128_init(time(NULL)); }
#define xoroshiro128plus_initFromTime xoroshiro128_initFromTime
#define xoroshiro128plusplus_initFromTime xoroshiro128_initFromTime
#define xoroshiro128starstar_initFromTime xoroshiro128_initFromTime

uint64 xoroshiro128plus_next(xoroshiro128_statePtr);
uint64 xoroshiro128plusplus_next(xoroshiro128_statePtr);
uint64 xoroshiro128starstar_next(xoroshiro128_statePtr);

#if __cplusplus
}
#endif