#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/errors.h"
#include "kprint_colors.h"
#include "kprint_format.h"

typedef union {
    int64 i64;
    uint64 u64;
    float64 f64;
    void* ptr;
} __kprint_value_union; 
#define __kprintVU(value) (__kprint_value_union){ value }

#define __kprint_argsToFormats8(\
    a0, a1, a2, a3, a4, a5, a6, a7,...)\
    ((int32[]){ a0,a2,a4,a6 })
#define __kprint_argsToObjects8(\
    a0, a1, a2, a3, a4, a5, a6, a7,...)\
    ((__kprint_value_union[]){ __kprintVU(a1),__kprintVU(a3),__kprintVU(a5),__kprintVU(a7) })
    
#define __kprint_argsToFormats16(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,...)\
    ((int32[]){ a0,a2,a4,a6,a8,a10,a12,a14 })
#define __kprint_argsToObjects16(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,...)\
    ((__kprint_value_union[]){ __kprintVU(a1),__kprintVU(a3),__kprintVU(a5),__kprintVU(a7),__kprintVU(a9),__kprintVU(a11),__kprintVU(a13),__kprintVU(a15) })

#define __kprint_argsToFormats32(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31,...)\
    ((int32[]){ a0,a2,a4,a6,a8,a10,a12,a14,a16,a18,a20,a22,a24,a26,a28,a30 })
#define __kprint_argsToObjects32(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31,...)\
    ((__kprint_value_union[]){ __kprintVU(a1),__kprintVU(a3),__kprintVU(a5),__kprintVU(a7),__kprintVU(a9),__kprintVU(a11),__kprintVU(a13),__kprintVU(a15),__kprintVU(a17),__kprintVU(a19),__kprintVU(a21),__kprintVU(a23),__kprintVU(a25),__kprintVU(a27),__kprintVU(a29),__kprintVU(a31) })

#define __32zeroes 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define __kprint_argsToArrs(COUNT,ARGS...)\
    (kprint_format*)(COUNT<=8 ? __kprint_argsToFormats8(ARGS) :\
    COUNT<=16 ? __kprint_argsToFormats16(ARGS) :\
    __kprint_argsToFormats32(ARGS)),\
    (__kprint_value_union*)(COUNT<=8 ? __kprint_argsToObjects8(ARGS) :\
    COUNT<=16 ? __kprint_argsToObjects16(ARGS) :\
    __kprint_argsToObjects32(ARGS))


Maybe __ksprint(uint8 n, kprint_format* formats, __kprint_value_union* objects);
#define ksprint(ARGS...) __ksprint(count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS, __32zeroes))

Maybe __kfprint(FILE* fd, uint8 n, kprint_format* formats, __kprint_value_union* objects);
#define kfprint(FD, ARGS...) __kfprint(FD, count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS, __32zeroes))

void __kprint(uint8 n, kprint_format* formats, __kprint_value_union* objects);
#define kprint(ARGS...) __kprint(count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS, __32zeroes))

// cross-platform printf analog
void kprintf(char* format, ...);

// can take (bgColor | fgColor) 
void kprint_setColor(kprint_format f);

#if __cplusplus
}
#endif