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
kerepType_declare(KVPair);
kerepType_declare(KVPairPtr);

Autoarr_declare(KVPair)
kerepType_declare(AutoarrKVPair);
kerepType_declare(AutoarrKVPairPtr);

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