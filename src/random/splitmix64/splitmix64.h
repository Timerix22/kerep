#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../base/base.h"

typedef u64 splitmix64_state;

static inline void splitmix64_construct(splitmix64_state* state, u64 seed){
    *state=seed;
}

u64 splitmix64_next(splitmix64_state* state_ptr);

#if __cplusplus
}
#endif
