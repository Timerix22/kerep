#if __cplusplus
extern "C" {
#endif

#include "Autoarr.h"

EXPORT void CALL kerep_Autoarr_Unitype_create(u16 max_chunks_count, u16 max_chunk_length, Autoarr_Unitype** output){
    *output=Autoarr_create(Unitype, max_chunks_count, max_chunk_length);
}

EXPORT void CALL kerep_Autoarr_Unitype_destruct(Autoarr_Unitype* ar){
    Autoarr_destruct(ar, true);
}

EXPORT void CALL kerep_Autoarr_Unitype_get(Autoarr_Unitype* ar, u32 index, Unitype* output){
    *output=Autoarr_get(ar, index);
}

EXPORT void CALL kerep_Autoarr_Unitype_add(Autoarr_Unitype* ar, Unitype element){
    Autoarr_add(ar, element);
}

EXPORT void CALL kerep_Autoarr_Unitype_set(Autoarr_Unitype* ar, u32 index, Unitype element){
    Autoarr_set(ar, index, element);
}

EXPORT void CALL kerep_Autoarr_Unitype_length(Autoarr_Unitype* ar, u32* output){
    *output=Autoarr_length(ar);
}

EXPORT void CALL kerep_Autoarr_Unitype_max_length(Autoarr_Unitype* ar, u32* output){
    *output=Autoarr_max_length(ar);
}

#if __cplusplus
}
#endif
