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

void printrowgraph(Hashtable* ht){
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
            char* str0=char_multiply(' ',i>=100?0:(i>=10?1:2));
            char* str1=char_multiply(' ',lgs[i]>=100?0:(lgs[i]>=10?1:2));
            char* str2=char_multiply('#',lgs[i]/100);
            kprintf("\e[94m  length: \e[96m%u %s \e[94mfrequency: \e[96m%u %s \e[90m%s\n",i,str0,lgs[i],str1,str2);
            free(str0);
            free(str1);
            free(str2);
        }
}

char* genkey(u32 i){
    char* key=malloc(12);
    ksprintf(key,12,"key_%u",i);
    return key;
}

void fill(Hashtable* ht){
    for(u32 i=0;i<100000;i++)
        Hashtable_add(ht,genkey(i),UniUInt64(i));
}

Unitype gett(Hashtable* ht){
    Unitype u;
    for(u32 i=0;i<100000;i++){
        char* key=genkey(i);
        u=Hashtable_get(ht,key);
        free(key);
    }
    return u;
}


void test_hashtable(){
    optime("test_hashtable",1,
        kprintf("\e[96m-----------[test_hashtable]-----------\n");
        Hashtable* ht=Hashtable_create();
        kprintf("\e[92mhashtable created\n");
        print_hashtable(ht);
        optime("fill",1,fill(ht));
        optime("get",1,gett(ht));
        printrowgraph(ht);
        print_hashtable(ht);
        Hashtable_free(ht);
        kprintf("\e[92mhashtable freed\n");
    );
}
