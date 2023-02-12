#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "../HashFunctions/hash.h"
#include "KeyValuePair.h"

STRUCT(Hashtable,
    u8 hein;  // height=HT_HEIGHTS[hein] 
    Autoarr(KVPair)** rows; // Autoarr[height]
)

Hashtable* Hashtable_create();
void Hashtable_free(Hashtable* ht);
void __Hashtable_free(void* ht);

// amount of rows
u16 Hashtable_height(Hashtable* ht);

// don't add pairs with the same keys,
// or something weird will happen
// if not sure, use Hashtable_addOrSet()
void Hashtable_add(Hashtable* ht, char* key, Unitype u);

void Hashtable_addOrSet(Hashtable* ht, char* key, Unitype u);

// returns null or pointer to value in hashtable
Unitype* Hashtable_getptr(Hashtable* ht, char* key);

Unitype Hashtable_get(Hashtable* ht, char* key);
bool Hashtable_try_get(Hashtable* ht, char* key, Unitype* output);

#define Hashtable_foreach(HT, EL, codeblock)({ \
    u16 hmax=Hashtable_height(HT); \
    for(u16 h=0; h<hmax; h++){ \
        Autoarr(KVPair)* AR=HT->rows[h]; \
        Autoarr_foreach(AR, EL, codeblock); \
    } \
})

#if __cplusplus
}
#endif