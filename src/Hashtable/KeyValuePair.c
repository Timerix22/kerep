#include "KeyValuePair.h"

kt_define(KVPair, __KVPair_destruct, NULL);

Autoarr_define(KVPair, false)

// proper way to clean a KVP
void KVPair_destruct(KVPair p){
    // free(p.key);
    Unitype_destruct(&p.value);
}
void __KVPair_destruct(void* p){ KVPair_destruct(*(KVPair*)p); }

void printkvp(KVPair p){
    kprintf("{\"%s\", ",p.key);
    printuni(p.value);
    kprintf("}");
}
