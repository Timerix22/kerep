#include "KeyValuePair.h"

kt_define(KVPair, NULL, NULL);

Autoarr_define(KVPair)

void printkvp(KVPair p){
    kprintf("{\"%s\", ",p.key);
    printuni(p.value);
    kprintf("}");
}
