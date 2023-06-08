#include "tests.h"
#include "../src/Hashtable/Hashtable.h"

void print_hashtable(Hashtable* ht){
    kprintf("\e[94mHashtable: "
        IFWIN("%llu", "%lu")
        "\n  hein: %u\n"
        "  height: %u\n"
        "  rows: %p\n",
        sizeof(Hashtable),
        ht->hein,
        Hashtable_height(ht),
        ht->rows);
}

void printrowgraph(allocator_ptr al, Hashtable* ht){
    kprintf("\e[94mrow length graph:\n");
    u16 lgs_l=1000;
    u32 lgs[lgs_l];
     for(u32 i=0; i<lgs_l; i++)
        lgs[i]=0; 
    for(u16 h=0;h<Hashtable_height(ht);h++){
        Autoarr(KVPair)* ar=ht->rows[h];
        u32 l=Autoarr_length(ar);
        lgs[l]++;
    }
    for(u32 i=0; i<lgs_l; i++)
        if(lgs[i]>0) {
            char* str0=char_multiply(al, ' ',i>=100?0:(i>=10?1:2));
            char* str1=char_multiply(al, ' ',lgs[i]>=100?0:(lgs[i]>=10?1:2));
            char* str2=char_multiply(al, '#',lgs[i]/100);
            kprintf("\e[94m  length: \e[96m%u %s \e[94mfrequency: \e[96m%u %s \e[90m%s\n",i,str0,lgs[i],str1,str2);
            allocator_free(al, str2);
            allocator_free(al, str1);
            allocator_free(al, str0);
        }
}

char* genkey(allocator_ptr al, u32 i){
    char* key=allocator_alloc(al, 16);
    sprintf_s(key,16,"key_%u",i);
    return key;
}

void fill(allocator_ptr al, Hashtable* ht){
    for(u32 i=0;i<100000;i++)
        Hashtable_add(ht,genkey(al, i), UniUInt64(i));
}

Unitype gett(allocator_ptr al, Hashtable* ht){
    Unitype u;
    for(u32 i=0;i<100000;i++){
        char* key=genkey(al, i);
        u=Hashtable_get(ht,key);
        allocator_free(al, key);
    }
    return u;
}


void test_hashtable(){
    optime("test_hashtable",1,
        kprintf("\e[96m-----------[test_hashtable]-----------\n");
        StackingAllocator _al;
        allocator_ptr al=(allocator_ptr)&_al;
        StackingAllocator_construct(&_al, 4096);
        Hashtable* ht=Hashtable_create();
        kprintf("\e[92mhashtable created\n");
        print_hashtable(ht);
        optime("fill",1,fill(al, ht));
        optime("get",1,gett(al, ht));
        printrowgraph(al, ht);
        print_hashtable(ht);
        Hashtable_destruct(ht);
        kprintf("\e[92mhashtable freed\n");
        StackingAllocator_destruct(&_al);
    );
}
