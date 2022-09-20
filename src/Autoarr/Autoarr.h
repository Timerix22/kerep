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

ktId_declare(AutoarrChar);
ktId_declare(AutoarrBool);
ktId_declare(AutoarrFloat32);
ktId_declare(AutoarrFloat64);
ktId_declare(AutoarrInt8);
ktId_declare(AutoarrUInt8);
ktId_declare(AutoarrInt16);
ktId_declare(AutoarrUInt16);
ktId_declare(AutoarrInt32);
ktId_declare(AutoarrUInt32);
ktId_declare(AutoarrInt64);
ktId_declare(AutoarrUInt64);

ktId_declare(AutoarrCharPtr);
ktId_declare(AutoarrBoolPtr);
ktId_declare(AutoarrFloat32Ptr);
ktId_declare(AutoarrFloat64Ptr);
ktId_declare(AutoarrInt8Ptr);
ktId_declare(AutoarrUInt8Ptr);
ktId_declare(AutoarrInt16Ptr);
ktId_declare(AutoarrUInt16Ptr);
ktId_declare(AutoarrInt32Ptr);
ktId_declare(AutoarrUInt32Ptr);
ktId_declare(AutoarrInt64Ptr);
ktId_declare(AutoarrUInt64Ptr);

Autoarr_declare(Unitype)
ktId_declare(AutoarrUnitype);
ktId_declare(AutoarrUnitypePtr);

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