#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "hash.h"
#include "KeyValuePair.h"

typedef struct Hashtable{
    uint8 hein;  // height=HT_HEIGHTS[hein] 
    Autoarr(KVPair)** rows; // Autoarr[height]
} Hashtable;

Hashtable* Hashtable_create();
void Hashtable_free(Hashtable* ht);

// amount of rows
uint16 Hashtable_height(Hashtable* ht);

// don't add pairs with the same keys,
// or something weird will happen
// if not sure, use Hashtable_addOrSet()
void Hashtable_add(Hashtable* ht, char* key, Unitype u);

void Hashtable_addOrSet(Hashtable* ht, char* key, Unitype u);

// returns null or pointer to value in hashtable
Unitype* Hashtable_getptr(Hashtable* ht, char* key);

Unitype Hashtable_get(Hashtable* ht, char* key);
bool Hashtable_try_get(Hashtable* ht, char* key, Unitype* output);

#define Hashtable_foreach(HT, EL, codeblock)({\
    uint16 hmax=Hashtable_height(HT);\
    for(uint16 h=0; h<hmax; h++){\
        Autoarr(KVPair)* AR=HT->rows[h];\
        Autoarr_foreach(AR, EL, codeblock);\
    }\
})

#if __cplusplus
}
#endif