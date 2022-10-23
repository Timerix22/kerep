/*  Written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include "../../krandom.h"

/* This is xoshiro256++ 1.0, one of our all-purpose, rock-solid generators.
   It has excellent (sub-ns) speed, a state (256 bits) that is large
   enough for any parallel application, and it passes all tests we are
   aware of.

   For generating just floating-point numbers, xoshiro256+ is even faster.

   The state must be seeded so that it is not everywhere zero. If you have
   a 64-bit seed, we suggest to seed a splitmix64 generator and use its
   output to fill s. */

static inline uint64 rotl(const uint64 x, int k) {
    return (x << k) | (x>>(64 - k));
}

typedef union {
    uint64 s[4];
} _state_t;

uint64 xoshiro256plusplus_next(void* _state) {
    _state_t* state=_state;
    const uint64 result=rotl(state->s[0] + state->s[3], 23) + state->s[0];
    const uint64 t=state->s[1] << 17;
    state->s[2] ^= state->s[0];
    state->s[3] ^= state->s[1];
    state->s[1] ^= state->s[2];
    state->s[0] ^= state->s[3];
    state->s[2] ^= t;
    state->s[3]=rotl(state->s[3], 45);
    return result;
}

void* xoshiro256plusplus_init(uint64 seed){
    _state_t* state=malloc(sizeof(_state_t));
    splitmix64_state splitmix=splitmix64_init(seed);
    state->s[0]=splitmix64_next(splitmix);
    state->s[1]=splitmix64_next(splitmix);
    state->s[2]=splitmix64_next(splitmix);
    state->s[3]=splitmix64_next(splitmix);
    return state;
}
