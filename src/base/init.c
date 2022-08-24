#include "base.h"

void kerepInit(){
    kerepType_register(NULL, Null, NULL);

    kerepType_register(char, Char, NULL);
    kerepType_register(bool, Bool, NULL);
    kerepType_register(float32, Float32, NULL);
    kerepType_register(float64, Float64, NULL);
    kerepType_register(int8, Int8, NULL);
    kerepType_register(uint8, UInt8, NULL);
    kerepType_register(int16, Int16, NULL);
    kerepType_register(uint16, UInt16, NULL);
    kerepType_register(int32, Int32, NULL);
    kerepType_register(uint32, UInt32, NULL);
    kerepType_register(int64, Int64, NULL);
    kerepType_register(uint64, UInt64, NULL);

    kerepType_register(char*, CharPtr, NULL);
    kerepType_register(bool*, BoolPtr, NULL);
    kerepType_register(float32*, Float32Ptr, NULL);
    kerepType_register(float64*, Float64Ptr, NULL);
    kerepType_register(int8*, Int8Ptr, NULL);
    kerepType_register(uint8*, UInt8Ptr, NULL);
    kerepType_register(int16*, Int16Ptr, NULL);
    kerepType_register(uint16*, UInt16Ptr, NULL);
    kerepType_register(int32*, Int32Ptr, NULL);
    kerepType_register(uint32*, UInt32Ptr, NULL);
    kerepType_register(int64*, Int64Ptr, NULL);
    kerepType_register(uint64*, UInt64Ptr, NULL);

    kerepType_register(Unitype, Unitype, __UnitypePtr_free);
    kerepType_register(Unitype*, UnitypePtr, __UnitypePtr_free);

    kerepType_register(, AutoarrChar, Autoarr_free);
    kerepType_register(, AutoarrBool, Autoarr_free);
    kerepType_register(, AutoarrFloat32, Autoarr_free);
    kerepType_register(, AutoarrFloat64, Autoarr_free);
    kerepType_register(, AutoarrInt8, Autoarr_free);
    kerepType_register(, AutoarrUInt8, Autoarr_free);
    kerepType_register(, AutoarrInt16, Autoarr_free);
    kerepType_register(, AutoarrUInt16, Autoarr_free);
    kerepType_register(, AutoarrInt32, Autoarr_free);
    kerepType_register(, AutoarrUInt32, Autoarr_free);
    kerepType_register(, AutoarrInt64, Autoarr_free);
    kerepType_register(, AutoarrUInt64, Autoarr_free);

    kerepType_register(, AutoarrCharPtr, Autoarr_free);
    kerepType_register(, AutoarrBoolPtr, Autoarr_free);
    kerepType_register(, AutoarrFloat32Ptr, Autoarr_free);
    kerepType_register(, AutoarrFloat64Ptr, Autoarr_free);
    kerepType_register(, AutoarrInt8Ptr, Autoarr_free);
    kerepType_register(, AutoarrUInt8Ptr, Autoarr_free);
    kerepType_register(, AutoarrInt16Ptr, Autoarr_free);
    kerepType_register(, AutoarrUInt16Ptr, Autoarr_free);
    kerepType_register(, AutoarrInt32Ptr, Autoarr_free);
    kerepType_register(, AutoarrUInt32Ptr, Autoarr_free);
    kerepType_register(, AutoarrInt64Ptr, Autoarr_free);
    kerepType_register(, AutoarrUInt64Ptr, Autoarr_free);

    kerepType_register(, STNode, STNode_free);
    kerepType_register(, STNodePtr, STNode_free);

    kerepType_register(, Hashtable, Hashtable_free);
    kerepType_register(, HashtablePtr, Hashtable_free);
}
