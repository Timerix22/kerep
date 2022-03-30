#if __cplusplus
extern "C" {
#endif

#include "Autoarr.h"

EXPORT void CALL kerep_Autoarr_Unitype_create(uint16 max_blocks_count, uint16 max_block_length, Autoarr_Unitype** output){
    *output=malloc(sizeof(Autoarr_Unitype));
    **output=Autoarr_create(Unitype, max_blocks_count, max_block_length);
}

EXPORT void CALL kerep_Autoarr_Unitype_free(Autoarr_Unitype* ar){
    Autoarr_clear(ar);
    free(ar);
}

EXPORT void CALL kerep_Autoarr_Unitype_get(Autoarr_Unitype* ar, uint32 index, Unitype* output){
    *output=Autoarr_get(ar, index);
}

EXPORT void CALL kerep_Autoarr_Unitype_add(Autoarr_Unitype* ar, Unitype element){
    Autoarr_add(ar, element);
}

EXPORT void CALL kerep_Autoarr_Unitype_set(Autoarr_Unitype* ar, uint32 index, Unitype element){
    Autoarr_set(ar, index, element);
}

EXPORT void CALL kerep_Autoarr_Unitype_length(Autoarr_Unitype* ar, uint32* output){
    *output=Autoarr_length(ar);
}

EXPORT void CALL kerep_Autoarr_Unitype_max_length(Autoarr_Unitype* ar, uint32* output){
    *output=Autoarr_max_length(ar);
}

#if __cplusplus
}
#endif