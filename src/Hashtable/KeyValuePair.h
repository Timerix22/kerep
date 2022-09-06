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
ktId_declare(ktId_KVPair);
ktId_declare(ktId_KVPairPtr);

Autoarr_declare(KVPair)
ktId_declare(ktId_AutoarrKVPair);
ktId_declare(ktId_AutoarrKVPairPtr);

// proper way to clear a KVP
void KVPair_free(KVPair p);
void __KVPair_free(void* p);

// func to clear KVP array
void __Autoarr_free_KVPair_(Autoarr_KVPair* ar, bool freePtr);
void ____Autoarr_free_KVPair_(void* ar);

void printkvp(KVPair p);

#if __cplusplus
}
#endif