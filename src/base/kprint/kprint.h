#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../errors.h"
#include "kprint_colors.h"
#include "kprint_format.h"

#define __count_va_args(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31,\
    a32) a32
#define count_va_args(ARGS...) __count_va_args(\
    ARGS,\
    32,31,30,29,28,27,26,25,\
    24,23,22,21,20,19,18,17,\
    16,15,14,13,12,11,10,9,\
    8, 7, 6, 5, 4, 3, 2, 1, 0)

#define get_va_args_sizes(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31)\ 
    (uint16[]{\
        sizeof(a0), sizeof(a1), sizeof(a2), sizeof(a3), sizeof(a4), sizeof(a5), sizeof(a6), sizeof(a7),\
        sizeof(a8), sizeof(a9), sizeof(a10),sizeof(a11),sizeof(a12),sizeof(a13),sizeof(a14),sizeof(a15),\
        sizeof(a16),sizeof(a17),sizeof(a18),sizeof(a19),sizeof(a20),sizeof(a21),sizeof(a22),sizeof(a23),\
        sizeof(a24),sizeof(a25),sizeof(a26),sizeof(a27),sizeof(a28),sizeof(a29),sizeof(a30),sizeof(a31)\
    })
#define get_va_args_sizes(ARGS...) get_va_args_sizes(ARGS,\
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)


Maybe __ksprint(uint8 n, uint16 sizes[32], ...);
#define ksprint(ARGS...) __ksprint(count_va_args(ARGS), get_va_args_sizes(ARGS), ARGS)

Maybe __kfprint(FILE* fd, uint8 n, uint16 sizes[32], ...);
#define kfprint(FD, ARGS...) __kfprint(FD, count_va_args(ARGS), get_va_args_sizes(ARGS), ARGS)

void __kprint(uint8 n, uint16 sizes[32], ...);
#define kprint(ARGS...) __kprint(count_va_args(ARGS), get_va_args_sizes(ARGS), ARGS)

#if __cplusplus
}
#endif