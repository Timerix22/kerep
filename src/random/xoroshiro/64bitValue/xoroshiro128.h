#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../splitmix64/splitmix64.h"

typedef union {
  u32 s[2];
} xoroshiro128_state;

void xoroshiro128_construct(xoroshiro128_state* state, u64 seed);

u64 xoroshiro128plus_next(xoroshiro128_state*);
u64 xoroshiro128plusplus_next(xoroshiro128_state*);
u64 xoroshiro128starstar_next(xoroshiro128_state*);

#if __cplusplus
}
#endif
