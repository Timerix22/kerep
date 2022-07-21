#include "tests.h"
#include "../src/Hashtable2/Hashtable2.hpp"
#include <memory>

#define TKey std::shared_ptr<char>
#define TVal uint64
#define HT_TYPE Hashtable2<TKey, TVal>
#define HT_TYPE_NAME "Hashtable2<std::shared_ptr<char*>, uint64>"

void print_hashtable(HT_TYPE* ht){
    printf("\e[94m" HT_TYPE_NAME ": "
        IFWIN("%llu", "%lu")
        "\n  height: %u\n",
        sizeof(HT_TYPE),
        ht->height);
}

std::shared_ptr<char> genkey(uint32 i){
    char* key=new char[24];
    IFMSC(
        sprintf_s(key,24,"key_%u",i),
        sprintf(key,"key_%u",i)
    );
    dbg(i);
    return std::shared_ptr<char>(key, [](char* s){ delete[] s;});
}

void fill(HT_TYPE* ht){
    for(uint32 i=0;i<260;i++)
        ht->add(genkey(i), 555666);
    print_hashtable(ht);
}

TVal gett(HT_TYPE* ht){
    TVal u;
    for(uint32 i=0;i<1000;i++){
        TKey key=genkey(i);
        u=ht->get(key);
    }
    return u;
}


void test_hashtable2(){
    //optime("test_hashtable2",1,({
        printf("\e[96m-----------[test_hashtable2]-----------\n");
#if STORE_HASHES
        HT_TYPE* ht=new HT_TYPE(
            [](TKey k) { return hashs(hash_sdbm32,k.get()); });
#else
        HT_TYPE* ht=new HT_TYPE(
            [](TKey k) -> HT_HASH_T { return hashs(hash_sdbm32,k.get()); },
            [](TKey k0, TKey k1) -> bool { return cptr_compare(k0.get(), k1.get()); });
#endif
        printf("\e[92mhashtable created\n");
        print_hashtable(ht);
        optime("fill",1,fill(ht));
        // TVal r;
        // optime("get",1,r=gett(ht));
        // dbg((uint32)r);
        // print_hashtable(ht);
        delete ht;
        printf("\e[92mhashtable deleted\n");
    //}));
}
