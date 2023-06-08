#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../splitmix64/splitmix64.h"

typedef union {
    u64 merged;
    u32 s[2];
} xoroshiro64_state;

void xoroshiro64_construct(xoroshiro64_state* state_ptr, u64 seed);

u32 xoroshiro64star_next(xoroshiro64_state*);
u32 xoroshiro64starstar_next(xoroshiro64_state*);

#if __cplusplus
}
#endif
