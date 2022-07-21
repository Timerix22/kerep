#include "tests.h"
#include "../src/Autoarr2/Autoarr2.hpp"


#define maxlength 160

void printautoarr2(Autoarr2<uint16>* ar){
    printf("\e[94mAutoarr2<uint16>: "
        IFWIN("%llu", "%lu")
        "\n  blocks_count: %u\n"
        "  max_block_length: %u\n"
        "  block_length: %u\n"
        "  length: %u\n",
        sizeof(Autoarr2<uint16>),
        ar->blocks_count,
        ar->max_block_length,
        ar->block_length,
        ar->length);
}

void fillar2(Autoarr2<uint16>* ar){
    for (uint16 i=0;i<maxlength;i++)
        ar->add(i);
}
void resetar2(Autoarr2<uint16>* ar){
    for (uint16 i=0;i<maxlength;i++)
        ar->set(i,maxlength-i-1);
}

void printallval2(Autoarr2<uint16>* ar){
    printf("\e[90m");
    for (uint16 i=0;i<ar->length;i++)
        printf("%u ",ar->get(i));
    printf("\n");
}

void test_autoarr2(){
    optime("test_autoarr2",1,({
        printf("\e[96m------------[test_autoarr2]-----------\n");
        Autoarr2<uint16>* ar=new Autoarr2<uint16>(16);
        printf("\e[92mautoarr2 created\n");
        fillar2(ar);
        printf("\e[92mautoarr2 filled up\n");
        printautoarr2(ar);
        printallval2(ar);
        resetar2(ar);
        printf("\e[92mautoarr2 values reset\n");
        printallval2(ar);
        delete ar;
        printf("\e[92mautoarr2 deleted\n");
    }));
}
