#pragma once

#if __cplusplus
extern "C" {
#endif

#include "Autoarr_declare.h"
#include "Autoarr_define.h"

Autoarr_declare(uint8)
Autoarr_declare(int8)
Autoarr_declare(uint16)
Autoarr_declare(int16)
Autoarr_declare(uint32)
Autoarr_declare(int32)
Autoarr_declare(uint64)
Autoarr_declare(int64)
Autoarr_declare(float)
Autoarr_declare(double)
Autoarr_declare(Unitype)

// right func to clear array of unitype values
void Autoarr_free_Unitype(Autoarr(Unitype)* ar);

#define Autoarr_foreach(ar,elem,codeblock)({\
    if(ar->blocks_count>0) {\
        typeof(**ar->values) elem;\
        for(uint32 blockI=0;blockI<ar->blocks_count-1;blockI++)\
            for(uint32 elemI=0;elemI<ar->max_block_length;elemI++){\
                elem=ar->values[blockI][elemI];\
                (codeblock);\
            }\
        for(uint32 elemI=0;elemI<ar->block_length;elemI++){\
            elem=ar->values[ar->blocks_count-1][elemI];\
            (codeblock);\
        }\
    }\
})

#if __cplusplus
}
#endif