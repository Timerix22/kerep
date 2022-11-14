#include "../base.h"
#include "../../Array/Array.h"
#include "../../Autoarr/Autoarr.h"
#include "../../SearchTree/SearchTree.h"
#include "../../Hashtable/Hashtable.h"
#include "../../String/StringBuilder.h"
#include "base_toString.h"

void ktDescriptors_initKerepTypes(){
    // null
    kt_register(NULL, ktId_Null, NULL, NULL);
    // base types
    kt_register(char,    ktId_Char,    NULL, __toString_char);
    kt_register(bool,    ktId_Bool,    NULL, __toString_bool);
    kt_register(float32, ktId_Float32, NULL, __toString_float32);
    kt_register(float64, ktId_Float64, NULL, __toString_float64);
    kt_register(int8,    ktId_Int8,    NULL, __toString_int8);
    kt_register(uint8,   ktId_UInt8,   NULL, __toString_uint8);
    kt_register(int16,   ktId_Int16,   NULL, __toString_int16);
    kt_register(uint16,  ktId_UInt16,  NULL, __toString_uint16);
    kt_register(int32,   ktId_Int32,   NULL, __toString_int32);
    kt_register(uint32,  ktId_UInt32,  NULL, __toString_uint32);
    kt_register(int64,   ktId_Int64,   NULL, __toString_int64);
    kt_register(uint64,  ktId_UInt64,  NULL, __toString_uint64);
    // base type pointers
    kt_register(char*,    ktId_CharPtr,    NULL, __toString_charPtr);
    kt_register(bool*,    ktId_BoolPtr,    NULL, NULL);
    kt_register(float32*, ktId_Float32Ptr, NULL, NULL);
    kt_register(float64*, ktId_Float64Ptr, NULL, NULL);
    kt_register(int8*,    ktId_Int8Ptr,    NULL, NULL);
    kt_register(uint8*,   ktId_UInt8Ptr,   NULL, NULL);
    kt_register(int16*,   ktId_Int16Ptr,   NULL, NULL);
    kt_register(uint16*,  ktId_UInt16Ptr,  NULL, NULL);
    kt_register(int32*,   ktId_Int32Ptr,   NULL, NULL);
    kt_register(uint32*,  ktId_UInt32Ptr,  NULL, NULL);
    kt_register(int64*,   ktId_Int64Ptr,   NULL, NULL);
    kt_register(uint64*,  ktId_UInt64Ptr,  NULL, NULL);
    
    // ktDescriptor
    kt_register(ktDescriptor,  ktId_ktDescriptor,  NULL, NULL);
    kt_register(ktDescriptor*,  ktId_ktDescriptorPtr,  NULL, NULL);


    // base type arrays
    kt_register(Array_char,    ktId_ArrayChar,    Array_char_freeValues, NULL);
    kt_register(Array_bool,    ktId_ArrayBool,    Array_bool_freeValues, NULL);
    kt_register(Array_float32, ktId_ArrayFloat32, Array_float32_freeValues, NULL);
    kt_register(Array_float64, ktId_ArrayFloat64, Array_float64_freeValues, NULL);
    kt_register(Array_int8,    ktId_ArrayInt8,    Array_int8_freeValues, NULL);
    kt_register(Array_uint8,   ktId_ArrayUInt8,   Array_uint8_freeValues, NULL);
    kt_register(Array_int16,   ktId_ArrayInt16,   Array_int16_freeValues, NULL);
    kt_register(Array_uint16,  ktId_ArrayUInt16,  Array_uint16_freeValues, NULL);
    kt_register(Array_int32,   ktId_ArrayInt32,   Array_int32_freeValues, NULL);
    kt_register(Array_uint32,  ktId_ArrayUInt32,  Array_uint32_freeValues, NULL);
    kt_register(Array_int64,   ktId_ArrayInt64,   Array_int64_freeValues, NULL);
    kt_register(Array_uint64,  ktId_ArrayUInt64,  Array_uint64_freeValues, NULL);
    // base type array pointers
    kt_register(Array_char*,    ktId_ArrayCharPtr,    Array_char_freeValues, NULL);
    kt_register(Array_bool*,    ktId_ArrayBoolPtr,    Array_bool_freeValues, NULL);
    kt_register(Array_float32*, ktId_ArrayFloat32Ptr, Array_float32_freeValues, NULL);
    kt_register(Array_float64*, ktId_ArrayFloat64Ptr, Array_float64_freeValues, NULL);
    kt_register(Array_int8*,    ktId_ArrayInt8Ptr,    Array_int8_freeValues, NULL);
    kt_register(Array_uint8*,   ktId_ArrayUInt8Ptr,   Array_uint8_freeValues, NULL);
    kt_register(Array_int16*,   ktId_ArrayInt16Ptr,   Array_int16_freeValues, NULL);
    kt_register(Array_uint16*,  ktId_ArrayUInt16Ptr,  Array_uint16_freeValues, NULL);
    kt_register(Array_int32*,   ktId_ArrayInt32Ptr,   Array_int32_freeValues, NULL);
    kt_register(Array_uint32*,  ktId_ArrayUInt32Ptr,  Array_uint32_freeValues, NULL);
    kt_register(Array_int64*,   ktId_ArrayInt64Ptr,   Array_int64_freeValues, NULL);
    kt_register(Array_uint64*,  ktId_ArrayUInt64Ptr,  Array_uint64_freeValues, NULL);

    // base type autoarrs
    kt_register(Autoarr_char,    ktId_AutoarrChar,    ____Autoarr_free_char, NULL);
    kt_register(Autoarr_bool,    ktId_AutoarrBool,    ____Autoarr_free_bool, NULL);
    kt_register(Autoarr_float32, ktId_AutoarrFloat32, ____Autoarr_free_float32, NULL);
    kt_register(Autoarr_float64, ktId_AutoarrFloat64, ____Autoarr_free_float64, NULL);
    kt_register(Autoarr_int8,    ktId_AutoarrInt8,    ____Autoarr_free_int8, NULL);
    kt_register(Autoarr_uint8,   ktId_AutoarrUInt8,   ____Autoarr_free_uint8, NULL);
    kt_register(Autoarr_int16,   ktId_AutoarrInt16,   ____Autoarr_free_int16, NULL);
    kt_register(Autoarr_uint16,  ktId_AutoarrUInt16,  ____Autoarr_free_uint16, NULL);
    kt_register(Autoarr_int32,   ktId_AutoarrInt32,   ____Autoarr_free_int32, NULL);
    kt_register(Autoarr_uint32,  ktId_AutoarrUInt32,  ____Autoarr_free_uint32, NULL);
    kt_register(Autoarr_int64,   ktId_AutoarrInt64,   ____Autoarr_free_int64, NULL);
    kt_register(Autoarr_uint64,  ktId_AutoarrUInt64,  ____Autoarr_free_uint64, NULL);
    // base type autoarr pointers
    kt_register(Autoarr_char*,    ktId_AutoarrCharPtr,    ____Autoarr_free_char, NULL);
    kt_register(Autoarr_bool*,    ktId_AutoarrBoolPtr,    ____Autoarr_free_bool, NULL);
    kt_register(Autoarr_float32*, ktId_AutoarrFloat32Ptr, ____Autoarr_free_float32, NULL);
    kt_register(Autoarr_float64*, ktId_AutoarrFloat64Ptr, ____Autoarr_free_float64, NULL);
    kt_register(Autoarr_int8*,    ktId_AutoarrInt8Ptr,    ____Autoarr_free_int8, NULL);
    kt_register(Autoarr_uint8*,   ktId_AutoarrUInt8Ptr,   ____Autoarr_free_uint8, NULL);
    kt_register(Autoarr_int16*,   ktId_AutoarrInt16Ptr,   ____Autoarr_free_int16, NULL);
    kt_register(Autoarr_uint16*,  ktId_AutoarrUInt16Ptr,  ____Autoarr_free_uint16, NULL);
    kt_register(Autoarr_int32*,   ktId_AutoarrInt32Ptr,   ____Autoarr_free_int32, NULL);
    kt_register(Autoarr_uint32*,  ktId_AutoarrUInt32Ptr,  ____Autoarr_free_uint32, NULL);
    kt_register(Autoarr_int64*,   ktId_AutoarrInt64Ptr,   ____Autoarr_free_int64, NULL);
    kt_register(Autoarr_uint64*,  ktId_AutoarrUInt64Ptr,  ____Autoarr_free_uint64, NULL);

    // Unitype
    kt_register(Unitype, ktId_Unitype, __UnitypePtr_free, NULL);
    kt_register(Unitype*, ktId_UnitypePtr, __UnitypePtr_free, NULL);
    kt_register(Autoarr_Unitype,  ktId_AutoarrUnitype,  ____Autoarr_free_Unitype_, NULL);
    kt_register(Autoarr_Unitype*,  ktId_AutoarrUnitypePtr,  ____Autoarr_free_Unitype_, NULL);
    // replacing autogenerated freear() function to custom 
    Autoarr_Unitype* _uar=Autoarr_create(Unitype, 1, 1);
    _uar->functions->freear=__Autoarr_free_Unitype_;
    Autoarr_free(_uar, true);

    // SearchTreeNode
    kt_register(STNode,  ktId_STNode,    __STNode_free, NULL);
    kt_register(STNode*, ktId_STNodePtr, __STNode_free, NULL);

    // KeyValuePair
    kt_register(KVPair, ktId_KVPair, __KVPair_free, NULL);
    kt_register(KVPair*, ktId_KVPairPtr, __KVPair_free, NULL);
    kt_register(Autoarr_KVPair, ktId_AutoarrKVPair, ____Autoarr_free_KVPair_, NULL);
    kt_register(Autoarr_KVPair*, ktId_AutoarrKVPairPtr, ____Autoarr_free_KVPair_, NULL);
    // replacing autogenerated freear() function to custom 
    Autoarr_KVPair* _kvpar=Autoarr_create(KVPair, 1, 1);
    _kvpar->functions->freear=__Autoarr_free_KVPair_;
    Autoarr_free(_kvpar, true);

    // Hashtable
    kt_register(Hashtable,  ktId_Hashtable,    __Hashtable_free, NULL);
    kt_register(Hashtable*, ktId_HashtablePtr, __Hashtable_free, NULL);

    // string
    kt_register(string,  ktId_string,    NULL, NULL);
    kt_register(string*, ktId_stringPtr, NULL, NULL);
    kt_register(string,  ktId_AutoarrString,    ____Autoarr_free_string, NULL);
    kt_register(string*, ktId_AutoarrStringPtr, ____Autoarr_free_string, NULL);
    // StringBuilder
    kt_register(StringBuilder,  ktId_StringBuilder,    __StringBuilder_free, NULL);
    kt_register(StringBuilder*, ktId_StringBuilderPtr, __StringBuilder_free, NULL);
}