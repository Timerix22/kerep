#pragma once

#if __cplusplus
extern "C" {
#endif

#include "Array_declare.h"
#include "Array_define.h"

Array_declare(char)
Array_declare(bool)
Array_declare(float32)
Array_declare(float64)
Array_declare(int8)
Array_declare(uint8)
Array_declare(int16)
Array_declare(uint16)
Array_declare(int32)
Array_declare(uint32)
Array_declare(int64)
Array_declare(uint64)

Array_declare(Unitype)

#if __cplusplus
}
#endif