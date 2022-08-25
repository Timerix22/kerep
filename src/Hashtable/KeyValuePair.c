#include "KeyValuePair.h"

kerepTypeId_define(kerepTypeId_KVPair);
kerepTypeId_define(kerepTypeId_KVPairPtr);

Autoarr_define(KVPair)
kerepTypeId_define(kerepTypeId_AutoarrKVPair);
kerepTypeId_define(kerepTypeId_AutoarrKVPairPtr);

// proper way to clear a KVP
void KVPair_free(KVPair p){
    free(p.key);
    Unitype_free(p.value);
}
void __KVPair_free(void* p){ KVPair_free(*(KVPair*)p); }

// func for  KVP array clearing
void __Autoarr_free_KVPair_(Autoarr_KVPair* ar, bool freePtr){
    Autoarr_foreach(ar,k,KVPair_free(k));
    Autoarr_free(ar, freePtr);
}
void ____Autoarr_free_KVPair_(void* ar){
    __Autoarr_free_KVPair_((Autoarr_KVPair*)ar, false);
}

void printkvp(KVPair p){
    printf("{\"%s\", ",p.key);
    printuni(p.value);
    printf("}");
}
