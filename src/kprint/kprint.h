#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/errors.h"
#include "kprint_colors.h"
#include "kprint_format.h"

#define __kprint_argsToFormats8(\
    a0, a1, a2, a3, a4, a5, a6, a7,...)\
    ((int32[]){ a0,a2,a4,a6 })
#define __kprint_argsToObjects8(\
    a0, a1, a2, a3, a4, a5, a6, a7,...)\
    ((void*[]){ &a1,&a3,&a5,&a7 })
    
#define __kprint_argsToFormats16(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,...)\
    ((int32[]){ a0,a2,a4,a6,a8,a10,a12,a14 })
#define __kprint_argsToObjects16(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,...)\
    ((void*[]){ &a1,&a3,&a5,&a7,&a9,&a11,&a13,&a15 })

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
    ((void*[]){ &a1,&a3,&a5,&a7,&a9,&a11,&a13,&a15,&a17,&a19,&a21,&a23,&a25,&a27,&a29,&a31 })

#define __32zeroes 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define __kprint_argsToArrs(COUNT,ARGS...)\
    (COUNT<=8 ? __kprint_argsToFormats8(ARGS) :\
    COUNT<=16 ? __kprint_argsToFormats16(ARGS) :\
    __kprint_argsToFormats32(ARGS)),\
    (COUNT<=8 ? __kprint_argsToObjects8(ARGS) :\
    COUNT<=16 ? __kprint_argsToObjects16(ARGS) :\
    __kprint_argsToObjects32(ARGS))


Maybe __ksprint(uint8 n, kprint_format* formats, void** objects);
#define ksprint(ARGS...) __ksprint(count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS, __32zeroes))

Maybe __kfprint(FILE* fd, uint8 n, kprint_format* formats, void** objects);
#define kfprint(FD, ARGS...) __kfprint(FD, count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS, __32zeroes))

void __kprint(uint8 n, kprint_format* formats, void** objects);
#define kprint(ARGS...) __kprint(count_args(ARGS), __kprint_argsToArrs(count_args(ARGS),ARGS, __32zeroes))

// can take (bgColor | fgColor) 
void kprint_setColor(kprint_format f);

#if __cplusplus
}
#endif