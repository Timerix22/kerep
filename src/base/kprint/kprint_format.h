#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../type_system/ktId.h"

typedef enum kprint_dataFormat{
    // 00000000 00000000  00000000 00000000
    //              ^^^^
    //              type
    kprint_fmtInt       = 0x00000000,
    kprint_fmtUInt      = 0x00010000,
    kprint_fmtHex       = 0x00020000,
    kprint_fmtBin       = 0x00030000,
    kprint_fmtFloat     = 0x00040000,
    kprint_fmtChar      = 0x00050000,
    kprint_fmtString    = 0x00060000,
    
    // 00100000 00000000  00000000 00000000
    //   ^
    // prefix/postfix flag
    kprint_fmtWithPrefix=0x20000000,
    kprint_fmtWithPostfix=kprint_fmtWithPrefix,

    // 00010000 00000000  00000000 00000000
    //    ^
    // uppercase flag
    kprint_fmtUppercase=0x10000000
} kprint_dataFormat;


typedef struct {
    unsigned char fgColorChanged : 1;
    unsigned char bgColorChanged : 1;
    unsigned char withPrefix : 1;
    unsigned char uppercase : 1;
    unsigned char fgColor : 4;
    unsigned char bgColor : 4;
    unsigned char dataFmt : 4;
    ktId typeId;
} kprint_format;

#if __cplusplus
}
#endif