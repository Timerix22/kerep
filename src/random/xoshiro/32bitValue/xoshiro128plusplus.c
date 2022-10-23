/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include "../../krandom.h"

/* This is xoshiro128++ 1.0, one of our 32-bit all-purpose, rock-solid
   generators. It has excellent speed, a state size (128 bits) that is
   large enough for mild parallelism, and it passes all tests we are aware
   of.

   For generating just single-precision (i.e., 32-bit) floating-point
   numbers, xoshiro128+ is even faster.

   The state must be seeded so that it is not everywhere zero. */


static inline uint32 rotl(const uint32 x, int k) {
    return (x << k) | (x >> (32 - k));
}

typedef union {
    uint64 merged[2];
    uint32 s[4];
} _state_t;

uint32 xoshiro128plusplus_next(void* _state){    
    _state_t* state=_state;
    const uint32 result = rotl(state->s[0] + state->s[3], 7) + state->s[0];

    const uint32 t = state->s[1] << 9;

    state->s[2] ^= state->s[0];
    state->s[3] ^= state->s[1];
    state->s[1] ^= state->s[2];
    state->s[0] ^= state->s[3];

    state->s[2] ^= t;

    state->s[3] = rotl(state->s[3], 11);

    return result;
}

void* xoshiro128plusplus_init(uint64 seed){
    _state_t* state=malloc(sizeof(_state_t));
    splitmix64_state splitmix=splitmix64_init(seed);
    state->merged[0]=splitmix64_next(splitmix);
    state->merged[1]=splitmix64_next(splitmix);
    return state;
}
