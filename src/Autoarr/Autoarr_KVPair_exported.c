#if __cplusplus
extern "C" {
#endif

#include "Autoarr.h"
#include "../Hashtable/KeyValuePair.h"

EXPORT void CALL kerep_Autoarr_KVPair_create(u16 max_blocks_count, u16 max_block_length, Autoarr_KVPair** output){
    *output=Autoarr_create(KVPair, max_blocks_count, max_block_length);
}

EXPORT void CALL kerep_Autoarr_KVPair_free(Autoarr_KVPair* ar){
    Autoarr_free(ar, true);
}

EXPORT void CALL kerep_Autoarr_KVPair_get(Autoarr_KVPair* ar, u32 index, KVPair* output){
    *output=Autoarr_get(ar, index);
}

EXPORT void CALL kerep_Autoarr_KVPair_add(Autoarr_KVPair* ar, KVPair element){
    Autoarr_add(ar, element);
}

EXPORT void CALL kerep_Autoarr_KVPair_set(Autoarr_KVPair* ar, u32 index, KVPair element){
    Autoarr_set(ar, index, element);
}

EXPORT void CALL kerep_Autoarr_KVPair_length(Autoarr_KVPair* ar, u32* output){
    *output=Autoarr_length(ar);
}

EXPORT void CALL kerep_Autoarr_KVPair_max_length(Autoarr_KVPair* ar, u32* output){
    *output=Autoarr_max_length(ar);
}

#if __cplusplus
}
#endif