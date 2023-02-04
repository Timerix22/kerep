#include "Array.h"

Array_define(char)
Array_define(bool)
Array_define(float32)
Array_define(float64)
Array_define(int8)
Array_define(uint8)
Array_define(int16)
Array_define(uint16)
Array_define(int32)
Array_define(uint32)
Array_define(int64)
Array_define(uint64)

Array_define(Unitype)

void Array_Unitype_free_(Array_Unitype* array, bool freeMembers){
    if(freeMembers) for (int32 i=0; i<array->length; i++)
        Unitype_free(array->values[i]);
    if(array->allocatedOnHeap)
        free(array->values);
}

void __Array_Unitype_free_(void* ar)
{ Array_Unitype_free_(ar, true); }
