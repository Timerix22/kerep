#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/std.h"

/*
You can choose any algorithm that has required functions:

    some_alg64_state some_alg64_init(uint64 seed);
    uint64 some_alg64_next(some_alg64_state);

    #define KRAND_ALG64 some_alg64
    #include "kerep/random/krandom.h"

The same way it works for 32-bit RNGs:

    some_alg64_state some_alg32_init(uint32 seed);
    uint32 some_alg32_next(some_alg64_state);

    #define KRAND_ALG32 some_alg32
    #include "kerep/random/krandom.h"
*/

// default rng_next function
#ifndef KRAND_ALG32
    #define KRAND_ALG32 xoroshiro128plus
#endif
#ifndef KRAND_ALG64
    #define KRAND_ALG64 xoshiro128plus
#endif

typedef void* KRAND_ALG32_state;
typedef void* KRAND_ALG64_state;
#define KRAND_ALG32_next(STATE)    xoshiro128plus##_next(STATE)
#define KRAND_ALG32_init(SEED)     xoshiro128plus##_init(SEED)
#define KRAND_ALG32_initFromTime() xoshiro128plus##_initFromTime()
#define KRAND_ALG64_next(STATE)    xoshiro256plus##_next(STATE)
#define KRAND_ALG64_init(SEED)     xoshiro256plus##_init(SEED)
#define KRAND_ALG64_initFromTime() xoshiro256plus##_initFromTime()


#define __krand_declare_alg(ALG, VALUE_SIZE)\
    typedef void* ALG##_state;\
    ALG##_state ALG##_init(uint64 seed);\
    static inline ALG##_state  ALG##_initFromTime(void) { return ALG##_init(time(NULL)); }\
    uint##VALUE_SIZE ALG##_next(ALG##_state);

// different algorithm declarations
// for ALG32
    // xoroshiro64
__krand_declare_alg(xoroshiro64star,      32)
__krand_declare_alg(xoroshiro64starstar,  32)
    // xoshiro128
__krand_declare_alg(xoshiro128plus,       32)
__krand_declare_alg(xoshiro128plusplus,   32)
__krand_declare_alg(xoshiro128starstar,   32)
// for ALG64
    // xoroshiro128
__krand_declare_alg(xoroshiro128plus,     64)
__krand_declare_alg(xoroshiro128plusplus, 64)
__krand_declare_alg(xoroshiro128starstar, 64)
    // xoshiro256
__krand_declare_alg(xoshiro256plus,       64)
__krand_declare_alg(xoshiro256plusplus,   64)
__krand_declare_alg(xoshiro256starstar,         64)
    // splitmix64
__krand_declare_alg(splitmix64, 64)


#define __krand_next_definition(VALUE_SIZE) { return from+KRAND_ALG##VALUE_SIZE##_next(state)%(to-from); }

// ready-to-use functions
static inline int8  krand_next8 (KRAND_ALG32_state state, int8  from, int8  to) __krand_next_definition(32)
static inline int16 krand_next16(KRAND_ALG32_state state, int16 from, int16 to) __krand_next_definition(32)
static inline int32 krand_next32(KRAND_ALG32_state state, int32 from, int32 to) __krand_next_definition(32)
static inline int64 krand_next64(KRAND_ALG64_state state, int64 from, int64 to) __krand_next_definition(64)

// divides random number by 2^64 to return a value between 0 and 1
static inline float32 krand_nextFloat32(KRAND_ALG32_state state) {return (uint32)KRAND_ALG32_next(state)/0xffffffff; }
static inline float64 krand_nextFloat64(KRAND_ALG64_state state) {return KRAND_ALG64_next(state)/0xffffffff; }


///@param chance (0-1.0) is probability of success
bool fate(float chance);

#if __cplusplus
}
#endif