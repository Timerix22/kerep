#include "tests.h"
#include "../src/random/random.h"

#define test_alg(ALG, STATE_TYPE, EXPECTED_FROM_ZERO) { \
    kprintf("\e[94mrng algorithm: \e[96m" #ALG "\n"); \
    STATE_TYPE##_state state; \
    STATE_TYPE##_construct(&state, 0); \
    u64 rn=ALG##_next(&state); \
    kprintf("\e[97m  next from zero seed:"); \
    if(rn != EXPECTED_FROM_ZERO){ \
        kprintf("\e[91m %lu\n", rn); \
        throw(ERR_UNEXPECTEDVAL); \
    } \
    kprintf("\e[92m %lu\n", rn); \
    STATE_TYPE##_construct(&state, random_seedFromTime()); \
    rn=ALG##_next(&state); \
    kprintf("\e[97m  next from time seed:\e[92m %lu\n", rn); \
}

void test_rng_algorithms(){
    // optime("test_rng_algorithms",1,
        kprintf("\e[96m--------[test_rng_algorithms]---------\n");
        // splitmix64
        test_alg(splitmix64,            splitmix64, 16294208416658607535ULL)
        // 32-bit
        // xoroshiro64
        test_alg(xoroshiro64star,       xoroshiro64, 932574677ULL)
        test_alg(xoroshiro64starstar,   xoroshiro64, 3183060286ULL)
        // xoshiro128
        test_alg(xoshiro128plus,        xoshiro128, 3918949401ULL)
        test_alg(xoshiro128plusplus,    xoshiro128, 1179900579ULL)
        test_alg(xoshiro128starstar,    xoshiro128, 3737715805ULL)
        // 64-bit
        // xoroshiro128
        test_alg(xoroshiro128plus,      xoroshiro128, 4778832803ULL)
        test_alg(xoroshiro128plusplus,  xoroshiro128, 626373238705583ULL)
        test_alg(xoroshiro128starstar,  xoroshiro128, 11897572417920ULL)
        // xoshiro256
        test_alg(xoshiro256plus,        xoshiro256, 15757075719729598363ULL)
        test_alg(xoshiro256plusplus,    xoshiro256, 5987356902031041503ULL)
        test_alg(xoshiro256starstar,    xoshiro256, 11091344671253066420ULL)
    // );
}
