#include "base.h"
#include "../Autoarr/Autoarr.h"
#include "../SearchTree/SearchTree.h"
#include "../Hashtable/Hashtable.h"
#include "../String/StringBuilder.h"

void kerepTypeDescriptors_initKerepTypes(){
    // null
    kerepType_register(NULL, kerepTypeId_Null, NULL);
    // base types
    kerepType_register(char,    kerepTypeId_Char,    NULL);
    kerepType_register(bool,    kerepTypeId_Bool,    NULL);
    kerepType_register(float32, kerepTypeId_Float32, NULL);
    kerepType_register(float64, kerepTypeId_Float64, NULL);
    kerepType_register(int8,    kerepTypeId_Int8,    NULL);
    kerepType_register(uint8,   kerepTypeId_UInt8,   NULL);
    kerepType_register(int16,   kerepTypeId_Int16,   NULL);
    kerepType_register(uint16,  kerepTypeId_UInt16,  NULL);
    kerepType_register(int32,   kerepTypeId_Int32,   NULL);
    kerepType_register(uint32,  kerepTypeId_UInt32,  NULL);
    kerepType_register(int64,   kerepTypeId_Int64,   NULL);
    kerepType_register(uint64,  kerepTypeId_UInt64,  NULL);
    // base type pointers
    kerepType_register(char*,    kerepTypeId_CharPtr,    NULL);
    kerepType_register(bool*,    kerepTypeId_BoolPtr,    NULL);
    kerepType_register(float32*, kerepTypeId_Float32Ptr, NULL);
    kerepType_register(float64*, kerepTypeId_Float64Ptr, NULL);
    kerepType_register(int8*,    kerepTypeId_Int8Ptr,    NULL);
    kerepType_register(uint8*,   kerepTypeId_UInt8Ptr,   NULL);
    kerepType_register(int16*,   kerepTypeId_Int16Ptr,   NULL);
    kerepType_register(uint16*,  kerepTypeId_UInt16Ptr,  NULL);
    kerepType_register(int32*,   kerepTypeId_Int32Ptr,   NULL);
    kerepType_register(uint32*,  kerepTypeId_UInt32Ptr,  NULL);
    kerepType_register(int64*,   kerepTypeId_Int64Ptr,   NULL);
    kerepType_register(uint64*,  kerepTypeId_UInt64Ptr,  NULL);

    // base type autoarrs
    kerepType_register(Autoarr_char,    kerepTypeId_AutoarrChar,    ____Autoarr_free_char);
    kerepType_register(Autoarr_bool,    kerepTypeId_AutoarrBool,    ____Autoarr_free_bool);
    kerepType_register(Autoarr_float32, kerepTypeId_AutoarrFloat32, ____Autoarr_free_float32);
    kerepType_register(Autoarr_float64, kerepTypeId_AutoarrFloat64, ____Autoarr_free_float64);
    kerepType_register(Autoarr_int8,    kerepTypeId_AutoarrInt8,    ____Autoarr_free_int8);
    kerepType_register(Autoarr_uint8,   kerepTypeId_AutoarrUInt8,   ____Autoarr_free_uint8);
    kerepType_register(Autoarr_int16,   kerepTypeId_AutoarrInt16,   ____Autoarr_free_int16);
    kerepType_register(Autoarr_uint16,  kerepTypeId_AutoarrUInt16,  ____Autoarr_free_uint16);
    kerepType_register(Autoarr_int32,   kerepTypeId_AutoarrInt32,   ____Autoarr_free_int32);
    kerepType_register(Autoarr_uint32,  kerepTypeId_AutoarrUInt32,  ____Autoarr_free_uint32);
    kerepType_register(Autoarr_int64,   kerepTypeId_AutoarrInt64,   ____Autoarr_free_int64);
    kerepType_register(Autoarr_uint64,  kerepTypeId_AutoarrUInt64,  ____Autoarr_free_uint64);
    // base type autoarr pointers
    kerepType_register(Autoarr_char*,    kerepTypeId_AutoarrCharPtr,    ____Autoarr_free_char);
    kerepType_register(Autoarr_bool*,    kerepTypeId_AutoarrBoolPtr,    ____Autoarr_free_bool);
    kerepType_register(Autoarr_float32*, kerepTypeId_AutoarrFloat32Ptr, ____Autoarr_free_float32);
    kerepType_register(Autoarr_float64*, kerepTypeId_AutoarrFloat64Ptr, ____Autoarr_free_float64);
    kerepType_register(Autoarr_int8*,    kerepTypeId_AutoarrInt8Ptr,    ____Autoarr_free_int8);
    kerepType_register(Autoarr_uint8*,   kerepTypeId_AutoarrUInt8Ptr,   ____Autoarr_free_uint8);
    kerepType_register(Autoarr_int16*,   kerepTypeId_AutoarrInt16Ptr,   ____Autoarr_free_int16);
    kerepType_register(Autoarr_uint16*,  kerepTypeId_AutoarrUInt16Ptr,  ____Autoarr_free_uint16);
    kerepType_register(Autoarr_int32*,   kerepTypeId_AutoarrInt32Ptr,   ____Autoarr_free_int32);
    kerepType_register(Autoarr_uint32*,  kerepTypeId_AutoarrUInt32Ptr,  ____Autoarr_free_uint32);
    kerepType_register(Autoarr_int64*,   kerepTypeId_AutoarrInt64Ptr,   ____Autoarr_free_int64);
    kerepType_register(Autoarr_uint64*,  kerepTypeId_AutoarrUInt64Ptr,  ____Autoarr_free_uint64);

    // Unitype
    kerepType_register(Unitype, kerepTypeId_Unitype, __UnitypePtr_free);
    kerepType_register(Unitype*, kerepTypeId_UnitypePtr, __UnitypePtr_free);
    kerepType_register(Autoarr_Unitype,  kerepTypeId_AutoarrUnitype,  ____Autoarr_free_Unitype_);
    kerepType_register(Autoarr_Unitype*,  kerepTypeId_AutoarrUnitypePtr,  ____Autoarr_free_Unitype_);
    // replacing autogenerated freear() function to custom 
    Autoarr_Unitype* _uar=Autoarr_create(Unitype, 1, 1);
    _uar->functions->freear=__Autoarr_free_Unitype_;
    Autoarr_free(_uar, true);

    // SearchTreeNode
    kerepType_register(STNode,  kerepTypeId_STNode,    __STNode_free);
    kerepType_register(STNode*, kerepTypeId_STNodePtr, __STNode_free);

    // KeyValuePair
    kerepType_register(KVPair, kerepTypeId_KVPair, __KVPair_free);
    kerepType_register(KVPair*, kerepTypeId_KVPairPtr, __KVPair_free);
    kerepType_register(Autoarr_KVPair, kerepTypeId_AutoarrKVPair, ____Autoarr_free_KVPair_);
    kerepType_register(Autoarr_KVPair*, kerepTypeId_AutoarrKVPairPtr, ____Autoarr_free_KVPair_);
    // replacing autogenerated freear() function to custom 
    Autoarr_KVPair* _kvpar=Autoarr_create(KVPair, 1, 1);
    _kvpar->functions->freear=__Autoarr_free_KVPair_;
    Autoarr_free(_kvpar, true);

    // Hashtable
    kerepType_register(Hashtable,  kerepTypeId_Hashtable,    __Hashtable_free);
    kerepType_register(Hashtable*, kerepTypeId_HashtablePtr, __Hashtable_free);

    // StringBuilder
    kerepType_register(Autoarr_string,  kerepTypeId_AutoarrString,    ____Autoarr_free_string);
    kerepType_register(Autoarr_string*, kerepTypeId_AutoarrStringPtr, ____Autoarr_free_string);
    kerepType_register(StringBuilder,  kerepTypeId_StringBuilder,    __StringBuilder_free);
    kerepType_register(StringBuilder*, kerepTypeId_StringBuilderPtr, __StringBuilder_free);
}