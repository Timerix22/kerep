#include "KeyValuePair.h"

ktid_define(KVPair);

Autoarr_define(KVPair)

// proper way to clear a KVP
void KVPair_free(KVPair p){
    free(p.key);
    Unitype_free(p.value);
}
void __KVPair_free(void* p){ KVPair_free(*(KVPair*)p); }

// func for  KVP array clearing
void __Autoarr_free_KVPair_(Autoarr_KVPair* ar, bool freePtr){
    Autoarr_foreach(ar,k,KVPair_free(k));
    __Autoarr_free_KVPair(ar, freePtr);
}
void ____Autoarr_free_KVPair_(void* ar){
    __Autoarr_free_KVPair_((Autoarr_KVPair*)ar, false);
}

void printkvp(KVPair p){
    kprintf("{\"%s\", ",p.key);
    printuni(p.value);
    kprintf("}");
}
