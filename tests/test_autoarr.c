#include "tests.h"
#include "../src/Autoarr/Autoarr.h"

static void printautoarr(Autoarr(u16)* ar){
    kprintf("\e[94mAutoarr(u16): "
        IFWIN("%llu", "%lu")
        "\n  max_chunks_count: %u\n"
        "  chunks_count: %u\n"
        "  max_chunk_length: %u\n"
        "  chunk_length: %u\n"
        "  max_length: %u\n" 
        "  length: %u\n",
        sizeof(Autoarr(u16)),
        ar->max_chunks_count,
        ar->chunks_count,
        ar->max_chunk_length,
        ar->chunk_length,
        Autoarr_max_length(ar),
        Autoarr_length(ar));
}

static void fillar(Autoarr(u16)* ar){
    for (u16 i=0;i<Autoarr_max_length(ar);i++)
        Autoarr_add(ar,i);
}
static void resetar(Autoarr(u16)* ar){
    for (u16 i=0;i<Autoarr_max_length(ar);i++)
        Autoarr_set(ar,i,Autoarr_max_length(ar)-i-1);
}

static void printallval(Autoarr(u16)* ar){
    kprintf("\e[90m");
    for (u16 i=0;i<Autoarr_length(ar);i++)
        kprintf("%u ",Autoarr_get(ar,i));
    kprintf("\n");
}

void test_autoarr(){
    optime("test_autoarr",1,
        kprintf("\e[96m------------[test_autoarr]------------\n");
        Autoarr(u16)* ar=Autoarr_create(u16,10,16);
        kprintf("\e[92mautoarr created\n");
        fillar(ar);
        kprintf("\e[92mautoarr filled up\n");
        printautoarr(ar);
        printallval(ar);
        resetar(ar);
        kprintf("\e[92mautoarr values reset\n");
        printallval(ar);
        Autoarr_destruct(ar, true);
        kprintf("\e[92mautoarr deleted\n");
    );
}
