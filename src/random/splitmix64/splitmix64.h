#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../base/base.h"

typedef uint64 splitmix64_state;
typedef void* splitmix64_statePtr;

splitmix64_statePtr splitmix64_init(uint64 seed);
static inline splitmix64_statePtr splitmix64_initFromTime(void) { return splitmix64_init(time(NULL)); }

uint64 splitmix64_next(splitmix64_statePtr);

#if __cplusplus
}
#endif