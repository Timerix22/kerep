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

ktId_define(AutoarrChar);
ktId_define(AutoarrBool);
ktId_define(AutoarrFloat32);
ktId_define(AutoarrFloat64);
ktId_define(AutoarrInt8);
ktId_define(AutoarrUInt8);
ktId_define(AutoarrInt16);
ktId_define(AutoarrUInt16);
ktId_define(AutoarrInt32);
ktId_define(AutoarrUInt32);
ktId_define(AutoarrInt64);
ktId_define(AutoarrUInt64);

ktId_define(AutoarrCharPtr);
ktId_define(AutoarrBoolPtr);
ktId_define(AutoarrFloat32Ptr);
ktId_define(AutoarrFloat64Ptr);
ktId_define(AutoarrInt8Ptr);
ktId_define(AutoarrUInt8Ptr);
ktId_define(AutoarrInt16Ptr);
ktId_define(AutoarrUInt16Ptr);
ktId_define(AutoarrInt32Ptr);
ktId_define(AutoarrUInt32Ptr);
ktId_define(AutoarrInt64Ptr);
ktId_define(AutoarrUInt64Ptr);

Autoarr_define(Unitype)
ktId_define(AutoarrUnitype);
ktId_define(AutoarrUnitypePtr);

// right func to clear array of unitype values
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr){
    Autoarr_foreach(ar, u,Unitype_free(u));
    __Autoarr_free_Unitype(ar, freePtr);
}
void ____Autoarr_free_Unitype_(void* ar) { __Autoarr_free_Unitype_((Autoarr(Unitype)*)ar, false); }