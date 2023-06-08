#include "tests.h"
#include "../src/HashFunctions/hash.h"
#include "../src/Autoarr/Autoarr.h"
#include "../src/random/random.h"

#define SPEED_TESTS 1000000
#define COLLISION_TESTS 64000
char data[]="iojihi2ojo8la14nhvi3311pi[jiugbja38mo0ih6gfty88tryf-drh0lanvj03";

#define rng() splitmix64_next(&rng_state)

#define test_hashfunc(hasht, hashf) { \
    kprintf("\e[94mfunction: \e[92m" #hashf "\n"); \
    hasht h=0; \
    optime("speed test", SPEED_TESTS,  \
        h=hashf(h, data, sizeof(data)); \
    ); \
    /*kprintf("\e[94mhash of \"\e[90m%s\e[94m\": \e[92m%x\n",data, h);*/ \
    Autoarr(hasht)* hashes=Autoarr_create(hasht,1,COLLISION_TESTS); \
    splitmix64_state rng_state; \
    splitmix64_construct(&rng_state, random_seedFromTime()); \
    optime("collision test",1, \
        u32 collisions=0; \
        for(u64 i=0;i< COLLISION_TESTS;i++){ \
            u64 rn[8]; \
            rn[0]=rng(); rn[1]=rng(); rn[2]=rng(); rn[3]=rng();\
            rn[4]=rng(); rn[5]=rng(); rn[6]=rng(); rn[7]=rng();\
            hasht h=hashb(hashf, rn, sizeof(rn)); \
            bool col=false; \
            Autoarr_foreach(hashes,e, \
                if(e==h) { \
                    col=true; \
                    break; \
                } \
            ); \
            if(col) collisions++; \
            else Autoarr_add(hashes,h); \
        } \
        kprintf("\e[93m%u \e[94mcollisions detected in %u hashes\n", collisions, COLLISION_TESTS); \
    ); \
    Autoarr_destruct(hashes, true); \
    kprintf("\e[96m--------------------------------------\n"); \
}

void test_hash_functions(){
    optime("test_hash_functions",1,
        kprintf("\e[96m--------[test_hash_functions]---------\n");
        test_hashfunc(u32, hash_sdbm32);
        test_hashfunc(u32, hash_crc32);
    );
}
