#include "Array.h"

Array_define(char)
Array_define(bool)
Array_define(f32)
Array_define(f64)
Array_define(i8)
Array_define(u8)
Array_define(i16)
Array_define(u16)
Array_define(i32)
Array_define(u32)
Array_define(i64)
Array_define(u64)
Array_define(Pointer)

Array_define(Unitype)

void Array_Unitype_free_(Array_Unitype* array, bool freeMembers){
    if(freeMembers) for (u32 i=0; i<array->length; i++)
        Unitype_free(array->values[i]);
    if(array->allocatedOnHeap)
        free(array->values);
}

void __Array_Unitype_free_(void* ar)
{ Array_Unitype_free_(ar, true); }
