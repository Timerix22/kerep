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

kerepTypeId_define(kerepTypeId_AutoarrChar);
kerepTypeId_define(kerepTypeId_AutoarrBool);
kerepTypeId_define(kerepTypeId_AutoarrFloat32);
kerepTypeId_define(kerepTypeId_AutoarrFloat64);
kerepTypeId_define(kerepTypeId_AutoarrInt8);
kerepTypeId_define(kerepTypeId_AutoarrUInt8);
kerepTypeId_define(kerepTypeId_AutoarrInt16);
kerepTypeId_define(kerepTypeId_AutoarrUInt16);
kerepTypeId_define(kerepTypeId_AutoarrInt32);
kerepTypeId_define(kerepTypeId_AutoarrUInt32);
kerepTypeId_define(kerepTypeId_AutoarrInt64);
kerepTypeId_define(kerepTypeId_AutoarrUInt64);

kerepTypeId_define(kerepTypeId_AutoarrCharPtr);
kerepTypeId_define(kerepTypeId_AutoarrBoolPtr);
kerepTypeId_define(kerepTypeId_AutoarrFloat32Ptr);
kerepTypeId_define(kerepTypeId_AutoarrFloat64Ptr);
kerepTypeId_define(kerepTypeId_AutoarrInt8Ptr);
kerepTypeId_define(kerepTypeId_AutoarrUInt8Ptr);
kerepTypeId_define(kerepTypeId_AutoarrInt16Ptr);
kerepTypeId_define(kerepTypeId_AutoarrUInt16Ptr);
kerepTypeId_define(kerepTypeId_AutoarrInt32Ptr);
kerepTypeId_define(kerepTypeId_AutoarrUInt32Ptr);
kerepTypeId_define(kerepTypeId_AutoarrInt64Ptr);
kerepTypeId_define(kerepTypeId_AutoarrUInt64Ptr);

Autoarr_define(Unitype)
kerepTypeId_define(kerepTypeId_AutoarrUnitype);
kerepTypeId_define(kerepTypeId_AutoarrUnitypePtr);

// right func to clear array of unitype values
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr){
    Autoarr_foreach(ar, u,Unitype_free(u));
    __Autoarr_free_Unitype(ar, freePtr);
}
void ____Autoarr_free_Unitype_(void* ar) { __Autoarr_free_Unitype_((Autoarr(Unitype)*)ar, false); }