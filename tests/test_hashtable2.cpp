#include "tests.h"
#include "../src/Hashtable2/Hashtable2.hpp"

#define TKey char*
#define TVal uint64
#define HT_TYPE Hashtable2<TKey, TVal>
#define HT_TYPE_NAME "Hashtable2<char*, uint64>"

void print_hashtable(HT_TYPE* ht){
    printf("\e[94m" HT_TYPE_NAME ": "
        IFWIN("%llu", "%lu")
        "\n  height: %u\n",
        sizeof(HT_TYPE),
        ht->height());
}

char* genkey(uint32 i){
    char* key=new char[16];
    IFMSC(
        sprintf_s(key,16,"key_%u",i),
        sprintf(key,"key_%u",i)
    );
    return key;
}

void fill(HT_TYPE* ht){
    //for(uint32 i=0;i<100000;i++)
    //    ht->add(genkey(i),Uni(UInt64,i));
}

TVal gett(HT_TYPE* ht){
    TVal u;
    for(uint32 i=0;i<100000;i++){
        TKey key=genkey(i);
        //u=ht->get(key);
        delete[] key;
    }
    return u;
}


void test_hashtable2(){
    optime("test_hashtable2",1,({
        printf("\e[96m-----------[test_hashtable2]-----------\n");
#if STORE_HASHES
        HT_TYPE* ht=new HT_TYPE();
#else
        HT_TYPE* ht=new HT_TYPE(cptr_compare);
#endif
        printf("\e[92m" HT_TYPE_NAME " created\n");
        print_hashtable(ht);
        optime("fill",1,fill(ht));
        optime("get",1,gett(ht));
        print_hashtable(ht);
        delete ht;
        printf("\e[92m" HT_TYPE_NAME " deleted\n");
    }));
}
