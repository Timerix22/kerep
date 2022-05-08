#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "../Autoarr/Autoarr.h"

typedef struct KVPair{
    char* key;
    Unitype value;
} KVPair;

declare_Autoarr(KVPair)

// proper way to clear a KVP
void KVPair_free(KVPair p);

// func to clear KVP array
void Autoarr_free_KVPair(Autoarr_KVPair* ar);

void printkvp(KVPair p);

#if __cplusplus
}
#endif