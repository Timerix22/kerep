#include "../base.h"
#include "../../Array/Array.h"
#include "../../Autoarr/Autoarr.h"
#include "../../SearchTree/SearchTree.h"
#include "../../Hashtable/Hashtable.h"
#include "../../String/StringBuilder.h"
#include "base_toString.h"

void ktDescriptors_initKerepTypes(){
    // null
    __kt_register("Null", sizeof(NULL), NULL, NULL);
    ktid_Null=ktid_last;
    // base types
    kt_register(char,    NULL, __toString_char);
    kt_register(bool,    NULL, __toString_bool);
    kt_register(float32, NULL, __toString_float32);
    kt_register(float64, NULL, __toString_float64);
    kt_register(int8,    NULL, __toString_int8);
    kt_register(uint8,   NULL, __toString_uint8);
    kt_register(int16,   NULL, __toString_int16);
    kt_register(uint16,  NULL, __toString_uint16);
    kt_register(int32,   NULL, __toString_int32);
    kt_register(uint32,  NULL, __toString_uint32);
    kt_register(int64,   NULL, __toString_int64);
    kt_register(uint64,  NULL, __toString_uint64);
    
    // ktDescriptor
    kt_register(ktDescriptor, NULL, NULL);


    // base type arrays
    kt_register(Array_char,    (freeMembers_t)Array_char_freeValues, NULL);
    kt_register(Array_bool,    (freeMembers_t)Array_bool_freeValues, NULL);
    kt_register(Array_float32, (freeMembers_t)Array_float32_freeValues, NULL);
    kt_register(Array_float64, (freeMembers_t)Array_float64_freeValues, NULL);
    kt_register(Array_int8,    (freeMembers_t)Array_int8_freeValues, NULL);
    kt_register(Array_uint8,   (freeMembers_t)Array_uint8_freeValues, NULL);
    kt_register(Array_int16,   (freeMembers_t)Array_int16_freeValues, NULL);
    kt_register(Array_uint16,  (freeMembers_t)Array_uint16_freeValues, NULL);
    kt_register(Array_int32,   (freeMembers_t)Array_int32_freeValues, NULL);
    kt_register(Array_uint32,  (freeMembers_t)Array_uint32_freeValues, NULL);
    kt_register(Array_int64,   (freeMembers_t)Array_int64_freeValues, NULL);
    kt_register(Array_uint64,  (freeMembers_t)Array_uint64_freeValues, NULL);

    // base type autoarrs
    kt_register(Autoarr_char,    ____Autoarr_free_char, NULL);
    kt_register(Autoarr_bool,    ____Autoarr_free_bool, NULL);
    kt_register(Autoarr_float32, ____Autoarr_free_float32, NULL);
    kt_register(Autoarr_float64, ____Autoarr_free_float64, NULL);
    kt_register(Autoarr_int8,    ____Autoarr_free_int8, NULL);
    kt_register(Autoarr_uint8,   ____Autoarr_free_uint8, NULL);
    kt_register(Autoarr_int16,   ____Autoarr_free_int16, NULL);
    kt_register(Autoarr_uint16,  ____Autoarr_free_uint16, NULL);
    kt_register(Autoarr_int32,   ____Autoarr_free_int32, NULL);
    kt_register(Autoarr_uint32,  ____Autoarr_free_uint32, NULL);
    kt_register(Autoarr_int64,   ____Autoarr_free_int64, NULL);
    kt_register(Autoarr_uint64,  ____Autoarr_free_uint64, NULL);

    // Unitype
    kt_register(Unitype,         __UnitypePtr_free,         NULL);
    kt_register(Array_Unitype,  (freeMembers_t)Array_Unitype_freeValues, NULL);
    kt_register(Autoarr_Unitype, ____Autoarr_free_Unitype_, NULL);
    // replacing autogenerated freear() function to custom 
    Autoarr_Unitype* _uar=Autoarr_create(Unitype, 1, 1);
    _uar->functions->freear=__Autoarr_free_Unitype_;
    Autoarr_free(_uar, true);

    // SearchTreeNode
    kt_register(STNode, __STNode_free, NULL);

    // KeyValuePair
    kt_register(KVPair, __KVPair_free, NULL);
    kt_register(Autoarr_KVPair, ____Autoarr_free_KVPair_, NULL);
    // replacing autogenerated freear() function to custom 
    Autoarr_KVPair* _kvpar=Autoarr_create(KVPair, 1, 1);
    _kvpar->functions->freear=__Autoarr_free_KVPair_;
    Autoarr_free(_kvpar, true);

    // Hashtable
    kt_register(Hashtable, __Hashtable_free, NULL);

    // string
    kt_register(string, NULL, NULL);
    kt_register(Autoarr_string, ____Autoarr_free_string, NULL);
    // StringBuilder
    kt_register(StringBuilder, __StringBuilder_free, NULL);
}
