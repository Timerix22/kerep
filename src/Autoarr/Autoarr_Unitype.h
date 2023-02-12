#pragma once

#if __cplusplus
extern "C" {
#endif

#include "Autoarr_declare.h"
#include "Autoarr_define.h"

Autoarr_declare(Unitype)

// this function is injected in kerep_init()
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr);
void ____Autoarr_free_Unitype_(void* ar);

#define Autoarr_foreach(ar,elem,codeblock)({ \
    if(ar->blocks_count>0) { \
        typeof(**ar->values) elem; \
        for(u32 blockI=0;blockI<ar->blocks_count-1;blockI++) \
            for(u32 elemI=0;elemI<ar->max_block_length;elemI++){ \
                elem=ar->values[blockI][elemI]; \
                (codeblock); \
            } \
        for(u32 elemI=0;elemI<ar->block_length;elemI++){ \
            elem=ar->values[ar->blocks_count-1][elemI]; \
            (codeblock); \
        } \
    } \
})

#if __cplusplus
}
#endif