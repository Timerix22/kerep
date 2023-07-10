#include "tests.h"
#include "../src/Autoarr/Autoarr.h"

#define ARR_SZ 256

static void printautoarr(Autoarr(u16)* ar){
    kprintf("\e[94mAutoarr(u16): %lu\n"
        "  length: %u",
        sizeof(Autoarr(u16)),
        Autoarr_length(ar));
}

static void fillar(Autoarr(u16)* ar){
    for (u16 i=0; ARR_SZ; i++)
        Autoarr_add(ar,i);
}
static void resetar(Autoarr(u16)* ar){
    for (u16 i=0; ARR_SZ; i++)
        Autoarr_set(ar,i,ARR_SZ-i-1);
}

static void printallval(Autoarr(u16)* ar){
    kprintf("\e[90m");
    for (u16 i=0; i<Autoarr_length(ar); i++)
        kprintf("%u ",Autoarr_get(ar,i));
    kprintf("\n");
}

void test_autoarr(){
    // optime("test_autoarr",1,
        kprintf("\e[96m------------[test_autoarr]------------\n");
        Autoarr(u16) ar;
        Autoarr_construct(&ar, u16, ARR_SZ, NULL);
        kprintf("\e[92mautoarr created\n");
        fillar(&ar);
        kprintf("\e[92mautoarr filled up\n");
        printautoarr(&ar);
        printallval(&ar);
        resetar(&ar);
        kprintf("\e[92mautoarr values reset\n");
        printallval(&ar);
        Autoarr_destruct(&ar);
        kprintf("\e[92mautoarr deleted\n");
    // );
}
