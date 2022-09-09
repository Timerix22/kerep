#include "Autoarr.h"

Autoarr_define(char)
Autoarr_define(bool)
Autoarr_define(float32)
Autoarr_define(float64)
Autoarr_define(uint8)
Autoarr_define(int8)
Autoarr_define(uint16)
Autoarr_define(int16)
Autoarr_define(uint32)
Autoarr_define(int32)
Autoarr_define(uint64)
Autoarr_define(int64)

ktId_define(ktId_AutoarrChar);
ktId_define(ktId_AutoarrBool);
ktId_define(ktId_AutoarrFloat32);
ktId_define(ktId_AutoarrFloat64);
ktId_define(ktId_AutoarrInt8);
ktId_define(ktId_AutoarrUInt8);
ktId_define(ktId_AutoarrInt16);
ktId_define(ktId_AutoarrUInt16);
ktId_define(ktId_AutoarrInt32);
ktId_define(ktId_AutoarrUInt32);
ktId_define(ktId_AutoarrInt64);
ktId_define(ktId_AutoarrUInt64);

ktId_define(ktId_AutoarrCharPtr);
ktId_define(ktId_AutoarrBoolPtr);
ktId_define(ktId_AutoarrFloat32Ptr);
ktId_define(ktId_AutoarrFloat64Ptr);
ktId_define(ktId_AutoarrInt8Ptr);
ktId_define(ktId_AutoarrUInt8Ptr);
ktId_define(ktId_AutoarrInt16Ptr);
ktId_define(ktId_AutoarrUInt16Ptr);
ktId_define(ktId_AutoarrInt32Ptr);
ktId_define(ktId_AutoarrUInt32Ptr);
ktId_define(ktId_AutoarrInt64Ptr);
ktId_define(ktId_AutoarrUInt64Ptr);

Autoarr_define(Unitype)
ktId_define(ktId_AutoarrUnitype);
ktId_define(ktId_AutoarrUnitypePtr);

// right func to clear array of unitype values
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr){
    Autoarr_foreach(ar, u,Unitype_free(u));
    __Autoarr_free_Unitype(ar, freePtr);
}
void ____Autoarr_free_Unitype_(void* ar) { __Autoarr_free_Unitype_((Autoarr(Unitype)*)ar, false); }