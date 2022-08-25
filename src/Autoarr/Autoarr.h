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

kerepTypeId_declare(kerepTypeId_AutoarrChar);
kerepTypeId_declare(kerepTypeId_AutoarrBool);
kerepTypeId_declare(kerepTypeId_AutoarrFloat32);
kerepTypeId_declare(kerepTypeId_AutoarrFloat64);
kerepTypeId_declare(kerepTypeId_AutoarrInt8);
kerepTypeId_declare(kerepTypeId_AutoarrUInt8);
kerepTypeId_declare(kerepTypeId_AutoarrInt16);
kerepTypeId_declare(kerepTypeId_AutoarrUInt16);
kerepTypeId_declare(kerepTypeId_AutoarrInt32);
kerepTypeId_declare(kerepTypeId_AutoarrUInt32);
kerepTypeId_declare(kerepTypeId_AutoarrInt64);
kerepTypeId_declare(kerepTypeId_AutoarrUInt64);

kerepTypeId_declare(kerepTypeId_AutoarrCharPtr);
kerepTypeId_declare(kerepTypeId_AutoarrBoolPtr);
kerepTypeId_declare(kerepTypeId_AutoarrFloat32Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrFloat64Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrInt8Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrUInt8Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrInt16Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrUInt16Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrInt32Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrUInt32Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrInt64Ptr);
kerepTypeId_declare(kerepTypeId_AutoarrUInt64Ptr);

Autoarr_declare(Unitype)
kerepTypeId_declare(kerepTypeId_AutoarrUnitype);
kerepTypeId_declare(kerepTypeId_AutoarrUnitypePtr);

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