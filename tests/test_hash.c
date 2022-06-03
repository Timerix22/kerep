#include "tests.h"
#include "../src/Hashtable/hash.h"
#include "../src/Autoarr/Autoarr.h"

#define AMOUNT_OF_TESTS 400000

#define test_hashf(hasht, hashf, tests_n)\
    optime(#hashf,1,({\
    printf("\e[94mfunction: " #hashf "\n");\
    Autoarr(hasht)* hashes=Autoarr_create(hasht,512,32768);\
    uint32 collisions=0;\
    for(uint32 i=0;i<tests_n;i++){\
        hasht h=hashf((uint8*)&i, 4);\
        bool col=false;\
        Autoarr_foreach(hashes,e,({\
            if(e==h) {\
                col=true;\
                printf("\e[91mcollision: %lu\n", (uint64)h);\
                break;\
            }\
        }));\
        if(col) collisions++;\
        else Autoarr_add(hashes,h);\
    }\
    printf("\e[92m%u collisions detected per %u numbers\n", collisions, tests_n);\
}))

void test_hash_collisions(){
    optime("test_hash_collisions",1,({
        printf("\e[96m--------[test_hash_collisions]--------\n");
        char buf[]="iojihiojopijiugbjmoihftytryfdrh";
        printf("\e[92mhashb_crc32: %x\n", hashb_crc32(buf,cptr_length(buf)));
        printf("\e[92mhashb_sdbm32: %x\n", hashb_sdbm32(buf,cptr_length(buf)));
        test_hashf(uint32, hashb_crc32, 20000);
        test_hashf(uint32, hashb_sdbm32, 20000);
    }));
}