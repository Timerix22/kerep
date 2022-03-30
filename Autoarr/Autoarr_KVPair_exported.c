#if __cplusplus
extern "C" {
#endif

#include "Autoarr.h"
#include "../Hashtable/KeyValuePair.h"

EXPORT void CALL kerep_Autoarr_KeyValuePair_create(uint16 max_blocks_count, uint16 max_block_length, Autoarr_KeyValuePair** output){
    *output=malloc(sizeof(Autoarr_KeyValuePair));
    **output=Autoarr_create(KeyValuePair, max_blocks_count, max_block_length);
}

EXPORT void CALL kerep_Autoarr_KeyValuePair_free(Autoarr_KeyValuePair* ar){
    Autoarr_clear(ar);
    free(ar);
}

EXPORT void CALL kerep_Autoarr_KeyValuePair_get(Autoarr_KeyValuePair* ar, uint32 index, KeyValuePair* output){
    *output=Autoarr_get(ar, index);
}

EXPORT void CALL kerep_Autoarr_KeyValuePair_add(Autoarr_KeyValuePair* ar, KeyValuePair element){
    Autoarr_add(ar, element);
}

EXPORT void CALL kerep_Autoarr_KeyValuePair_set(Autoarr_KeyValuePair* ar, uint32 index, KeyValuePair element){
    Autoarr_set(ar, index, element);
}

EXPORT void CALL kerep_Autoarr_KeyValuePair_length(Autoarr_KeyValuePair* ar, uint32* output){
    *output=Autoarr_length(ar);
}

EXPORT void CALL kerep_Autoarr_KeyValuePair_max_length(Autoarr_KeyValuePair* ar, uint32* output){
    *output=Autoarr_max_length(ar);
}

#if __cplusplus
}
#endif