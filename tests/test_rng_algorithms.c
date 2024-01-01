#include "tests.h"
#include "../src/random/krandom.h"


#define test_alg(ALG, VALUE_SIZE, EXPECTED_FROM_ZERO) { \
    kprintf("\e[94mrng algorithm: \e[96m" #ALG "\n"); \
    void* s= ALG##_init(0); \
    u##VALUE_SIZE r=ALG##_next(s); \
    kprintf("\e[97m  next from zero seed:"); \
    if(r!=EXPECTED_FROM_ZERO){ \
        kprintf("\e[91m " IFWIN("%llu\n","%lu\n"), (u64)r); \
        throw(ERR_UNEXPECTEDVAL); \
    } \
    kprintf("\e[92m " IFWIN("%llu\n","%lu\n"), (u64)r); \
    ALG##_free(s); \
    s= ALG##_initFromTime(); \
    r=ALG##_next(s); \
    ALG##_free(s); \
    kprintf("\e[97m  next from time seed:\e[92m " IFWIN("%llu\n","%lu\n"), (u64)r); \
}

void test_rng_algorithms(){
    optime("test_rng_algorithms",1,
        kprintf("\e[96m--------[test_rng_algorithms]---------\n");  
        // for ALG32      
            // xoroshiro64
        test_alg(xoroshiro64star, 32, 932574677ULL)
        test_alg(xoroshiro64starstar, 32, 3183060286ULL)
            // xoshiro128
        test_alg(xoshiro128plus, 32, 3918949401ULL)
        test_alg(xoshiro128plusplus, 32, 1179900579ULL)
        test_alg(xoshiro128starstar, 32, 3737715805ULL)
        // for ALG64
            // xoroshiro128
        test_alg(xoroshiro128plus, 64, 4778832803ULL)
        test_alg(xoroshiro128plusplus, 64, 626373238705583ULL)
        test_alg(xoroshiro128starstar, 64, 11897572417920ULL)
            // xoshiro256
        test_alg(xoshiro256plus, 64, 15757075719729598363ULL)
        test_alg(xoshiro256plusplus, 64, 5987356902031041503ULL)
        test_alg(xoshiro256starstar, 64, 11091344671253066420ULL)
            // splitmix64
        test_alg(splitmix64, 64, 16294208416658607535ULL)
    );
}