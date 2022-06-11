#include "tests.h"
#include "../src/HashFunctions/hash.h"
#include "../src/Autoarr/Autoarr.h"


#define SPEED_TESTS 10000
#define COLLISION_TESTS 16000

char data[]="iojihiojopijiugbjmoihftytryfdrh";

#define test_hashfunc(hasht, hashf)({\
    printf("\e[94mfunction: \e[92m" #hashf "\n");\
    hasht h=0;\
    optime("speed test", 1, ({\
        for(uint32 i=0; i<SPEED_TESTS; i++)\
            h=hashf(h, data, sizeof(data));\
    }));\
    /*printf("\e[94mhash of \"\e[90m%s\e[94m\": \e[92m%x\n",data, h);*/\
    Autoarr(hasht)* hashes=Autoarr_create(hasht,512,32768);\
    optime("collision test",1,({\
        uint32 collisions=0;\
        for(uint64 i=0;i< COLLISION_TESTS;i++){\
            hasht h=hashb(hashf, (uint8*)&i, sizeof(i));\
            bool col=false;\
            Autoarr_foreach(hashes,e,({\
                if(e==h) {\
                    col=true;\
                    break;\
                }\
            }));\
            if(col) collisions++;\
            else Autoarr_add(hashes,h);\
        }\
        printf("\e[93m%u \e[94mcollisions detected in %u hashes\n", collisions, COLLISION_TESTS);\
    }));\
    printf("\e[96m--------------------------------------\n");\
})

void test_hash_functions(){
    optime("test_hash_functions",1,({
        printf("\e[96m--------[test_hash_functions]---------\n");
        test_hashfunc(uint32, hash_crc32);
        test_hashfunc(uint32, hash_sdbm32);
    }));
}