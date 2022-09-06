#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../errors.h"
#include "kprint_colors.h"
#include "kprint_format.h"

#define __count_args(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31,\
    a32) a32
#define count_args(ARGS...) __count_args(\
    ARGS,\
    32,31,30,29,28,27,26,25,\
    24,23,22,21,20,19,18,17,\
    16,15,14,13,12,11,10,9,\
    8, 7, 6, 5, 4, 3, 2, 1, 0)

#define __kprint_argsToFormats8(\
    a0, a1, a2, a3, a4, a5, a6, a7)\
    (kprint_format[]{ a0,a2,a4,a6 })
#define __kprint_argsToObjects8(\
    a0, a1, a2, a3, a4, a5, a6, a7)\
    (void*[]{ a1,a3,a5,a7 })
    
#define __kprint_argsToFormats16(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15)\
    (kprint_format[]{ a0,a2,a4,a6,a8,a10,a12,a14 })
#define __kprint_argsToObjects16(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15)\
    (void*[]{ a1,a3,a5,a7,a9,a11,a13,a15 })
    
#define __kprint_argsToFormats32(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31)\
    (kprint_format[]{ a0,a2,a4,a6,a8,a10,a12,a14,a16,a18,a20,a22,a24,a26,a28,a30 }
#define __kprint_argsToObjects32(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31)\
    (void*[]{ a1,a3,a5,a7,a9,a11,a13,a15,a17,a19,a21,a23,a25,a27,a29,a31 })

#define __32zeroes 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define __kprint_argsToArrs(COUNT,ARGS...)(\
    (COUNT<=8 __kprint_argsToFormats8(ARGS,__32zeroes) :\
    COUNT<=16 __kprint_argsToFormats16(ARGS,__32zeroes) :\
    __kprint_argsToFormats32(ARGS,__32zeroes)),\
    (COUNT<=8 __kprint_argsToObjects8(ARGS,__32zeroes) :\
    COUNT<=16 __kprint_argsToObjects16(ARGS) :\
    __kprint_argsToObjects32(ARGS,__32zeroes))


Maybe __ksprint(uint8 n, kprint_format* formats, void** objects);
#define ksprint(ARGS...) __ksprint(count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS))

Maybe __kfprint(FILE* fd, uint8 n, kprint_format* formats, void** objects);
#define kfprint(FD, ARGS...) __kfprint(FD, count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS))

void __kprint(uint8 n, kprint_format* formats, void** objects);
#define kprint(ARGS...) __kprint(count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS))

#if __cplusplus
}
#endif