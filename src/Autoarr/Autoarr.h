#pragma once

#if __cplusplus
extern "C" {
#endif

#include "Autoarr_declare.h"
#include "Autoarr_define.h"

Autoarr_declare(char)
Autoarr_declare(bool)
Autoarr_declare(float32)
Autoarr_declare(float64)
Autoarr_declare(int8)
Autoarr_declare(uint8)
Autoarr_declare(int16)
Autoarr_declare(uint16)
Autoarr_declare(int32)
Autoarr_declare(uint32)
Autoarr_declare(int64)
Autoarr_declare(uint64)

ktId_declare(ktId_AutoarrChar);
ktId_declare(ktId_AutoarrBool);
ktId_declare(ktId_AutoarrFloat32);
ktId_declare(ktId_AutoarrFloat64);
ktId_declare(ktId_AutoarrInt8);
ktId_declare(ktId_AutoarrUInt8);
ktId_declare(ktId_AutoarrInt16);
ktId_declare(ktId_AutoarrUInt16);
ktId_declare(ktId_AutoarrInt32);
ktId_declare(ktId_AutoarrUInt32);
ktId_declare(ktId_AutoarrInt64);
ktId_declare(ktId_AutoarrUInt64);

ktId_declare(ktId_AutoarrCharPtr);
ktId_declare(ktId_AutoarrBoolPtr);
ktId_declare(ktId_AutoarrFloat32Ptr);
ktId_declare(ktId_AutoarrFloat64Ptr);
ktId_declare(ktId_AutoarrInt8Ptr);
ktId_declare(ktId_AutoarrUInt8Ptr);
ktId_declare(ktId_AutoarrInt16Ptr);
ktId_declare(ktId_AutoarrUInt16Ptr);
ktId_declare(ktId_AutoarrInt32Ptr);
ktId_declare(ktId_AutoarrUInt32Ptr);
ktId_declare(ktId_AutoarrInt64Ptr);
ktId_declare(ktId_AutoarrUInt64Ptr);

Autoarr_declare(Unitype)
ktId_declare(ktId_AutoarrUnitype);
ktId_declare(ktId_AutoarrUnitypePtr);

// this function is injected in kerep_init()
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr);
void ____Autoarr_free_Unitype_(void* ar);

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