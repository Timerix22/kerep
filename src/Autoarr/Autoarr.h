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

kerepType_declare(AutoarrChar);
kerepType_declare(AutoarrBool);
kerepType_declare(AutoarrFloat32);
kerepType_declare(AutoarrFloat64);
kerepType_declare(AutoarrInt8);
kerepType_declare(AutoarrUInt8);
kerepType_declare(AutoarrInt16);
kerepType_declare(AutoarrUInt16);
kerepType_declare(AutoarrInt32);
kerepType_declare(AutoarrUInt32);
kerepType_declare(AutoarrInt64);
kerepType_declare(AutoarrUInt64);

kerepType_declare(AutoarrCharPtr);
kerepType_declare(AutoarrBoolPtr);
kerepType_declare(AutoarrFloat32Ptr);
kerepType_declare(AutoarrFloat64Ptr);
kerepType_declare(AutoarrInt8Ptr);
kerepType_declare(AutoarrUInt8Ptr);
kerepType_declare(AutoarrInt16Ptr);
kerepType_declare(AutoarrUInt16Ptr);
kerepType_declare(AutoarrInt32Ptr);
kerepType_declare(AutoarrUInt32Ptr);
kerepType_declare(AutoarrInt64Ptr);
kerepType_declare(AutoarrUInt64Ptr);

Autoarr_declare(Unitype)
kerepType_declare(AutoarrUnitype);
kerepType_declare(AutoarrUnitypePtr);

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