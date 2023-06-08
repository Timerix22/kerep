#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../splitmix64/splitmix64.h"

typedef union {
    u64 s[4];
} xoshiro256_state;

void xoshiro256_construct(xoshiro256_state* state, u64 seed);

u64 xoshiro256plus_next(xoshiro256_state*);
u64 xoshiro256plusplus_next(xoshiro256_state*);
u64 xoshiro256starstar_next(xoshiro256_state*);

#if __cplusplus
}
#endif
