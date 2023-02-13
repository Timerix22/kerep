#include "KeyValuePair.h"

kt_define(KVPair, __KVPair_free, NULL);

Autoarr_define(KVPair)

// proper way to clean a KVP
void KVPair_free(KVPair p){
    free(p.key);
    Unitype_free(p.value);
}
void __KVPair_free(void* p){ KVPair_free(*(KVPair*)p); }

// func for  KVP array cleaning
void __Autoarr_KVPair_free_fixed(Autoarr_KVPair* ar, bool freePtr){
    Autoarr_foreach(ar,k,KVPair_free(k));
    __Autoarr_KVPair_free_g(ar, freePtr);
}
void ____Autoarr_KVPair_free_fixed(void* ar){
    __Autoarr_KVPair_free_fixed((Autoarr_KVPair*)ar, false);
}

void printkvp(KVPair p){
    kprintf("{\"%s\", ",p.key);
    printuni(p.value);
    kprintf("}");
}
