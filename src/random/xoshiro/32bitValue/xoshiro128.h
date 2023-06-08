#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../splitmix64/splitmix64.h"

typedef union {
    u64 merged[2];
    u32 s[4];
} xoshiro128_state;

void xoshiro128_construct(xoshiro128_state* state, u64 seed);

u32 xoshiro128plus_next(xoshiro128_state*);
u32 xoshiro128plusplus_next(xoshiro128_state*);
u32 xoshiro128starstar_next(xoshiro128_state*);

#if __cplusplus
}
#endif
