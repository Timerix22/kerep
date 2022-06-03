#include "tests.h"
#include "../src/Hashtable/hash.h"
#include "../src/Autoarr/Autoarr.h"

#define AMOUNT_OF_TESTS 400000

char __buf[]="iojihiojopijiugbjmoihftytryfdrh";

#define test_hashfunc(hasht, hashf, tests_n)\
    optime(#hashf,1,({\
    printf("\e[94mfunction: \e[92m" #hashf "\n");\
    printf("\e[94mhash of \"%s\": \e[92m%x\n",__buf, hashf(__buf,cptr_length(__buf)));\
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
    printf("\e[93m%u \e[94mcollisions detected in %u hashes\n", collisions, tests_n);\
}))

void test_hash_functions(){
    optime("test_hash_functions",1,({
        printf("\e[96m--------[test_hash_functions]---------\n");
        test_hashfunc(uint32, hashb_crc32, 10000);
        test_hashfunc(uint32, hashb_sdbm32, 10000);
    }));
}