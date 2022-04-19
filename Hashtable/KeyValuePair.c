#include "KeyValuePair.h"

define_Autoarr(KVPair)


// proper way to clear a KVP
void KVPair_free(KVPair p){
    free(p.key);
    Unitype_free(p.value);
}

// func for  KVP array clearing
void Autoarr_free_KVPair(Autoarr_KVPair* ar){
    Autoarr_foreach(ar,k,KVPair_free(k));
    Autoarr_free(ar);
}

void printkvp(KVPair p){
    printf("{\"%s\", ",p.key);
    printuni(p.value);
    printf("}");
}
