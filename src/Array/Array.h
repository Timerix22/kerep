#pragma once

#if __cplusplus
extern "C" {
#endif

#include "Array_declare.h"
#include "Array_define.h"

Array_declare(char)
Array_declare(bool)
Array_declare(f32)
Array_declare(f64)
Array_declare(i8)
Array_declare(u8)
Array_declare(i16)
Array_declare(u16)
Array_declare(i32)
Array_declare(u32)
Array_declare(i64)
Array_declare(u64)

Array_declare(Unitype)

/// use this function instead of auto generated
void Array_Unitype_free_(Array_Unitype* array, bool freeMembers);
void __Array_Unitype_free_(void* ar);

#if __cplusplus
}
#endif