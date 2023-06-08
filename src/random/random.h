#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/std.h"
#include "splitmix64/splitmix64.h"
#include "xoroshiro/32bitValue/xoroshiro64.h"
#include "xoroshiro/64bitValue/xoroshiro128.h"
#include "xoshiro/32bitValue/xoshiro128.h"
#include "xoshiro/64bitValue/xoshiro256.h"


#define random_seedFromTime() time(NULL)

/// divides random number by 2^32
/// @return value between 0 and 1
static inline f32 random_toFloat32(u32 random_value)   { return (f32)random_value / (f32)0xffff; }
/// divides random number by 2^64
/// @return value between 0 and 1
static inline f64 random_nextFloat64(u64 random_value) { return (f64)random_value / (f64)0xffffffff; }

///@param probability (0-1.0) probability of success
///@return is action sucsessfull or not
static inline bool random_probability(u32 random_value, float probability){
    i32 limit=1.0f/probability + 0.0002f;
    return random_value%limit == 0;
}

#if __cplusplus
}
#endif
