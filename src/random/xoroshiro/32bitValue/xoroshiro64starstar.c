/*  Written in 2018 by David Blackman and Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include "../../krandom.h"

/* This is xoroshiro64** 1.0, our 32-bit all-purpose, rock-solid,
   small-state generator. It is extremely fast and it passes all tests we
   are aware of, but its state space is not large enough for any parallel
   application.

   For generating just single-precision (i.e., 32-bit) floating-point
   numbers, xoroshiro64* is even faster.

   The state must be seeded so that it is not everywhere zero. */


static inline uint32 rotl(const uint32 x, int k) {
    return (x << k) | (x >> (32 - k));
}

typedef union {
    uint64 merged;
    uint32 s[2];
} _state_t;

uint32 xoroshiro64starstar_next(void* _state) {
    _state_t* state=_state;
    const uint32 s0 = state->s[0];
    uint32 s1 = state->s[1];
    const uint32 result = rotl(s0 * 0x9E3779BB, 5) * 5;

    s1 ^= s0;
    state->s[0] = rotl(s0, 26) ^ s1 ^ (s1 << 9); // a, b
    state->s[1] = rotl(s1, 13); // c

    return result;
}

void* xoroshiro64starstar_init(uint64 seed){
    _state_t* state=malloc(sizeof(_state_t));
    splitmix64_state splitmix=splitmix64_init(seed);
    state->merged=splitmix64_next(splitmix);
    return state;
}
