#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/std.h"
#include "../base/type_system/ktId.h"

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

typedef uint32 kprint_format;

#define kprint_format_fgColorChanged(FMT) (FMT&0x80000000)
#define kprint_format_bgColorChanged(FMT) (FMT&0x40000000)
#define kprint_format_withPrefix(FMT) (FMT&kprint_fmtWithPrefix)
#define kprint_format_withPostfix(FMT) (FMT&kprint_fmtWithPostfix)
#define kprint_format_uppercase(FMT) (FMT&kprint_fmtUppercase)
#define kprint_format_fgColor(FMT) (kprint_fgColor)(FMT&0x8f000000)
#define kprint_format_bgColor(FMT) (kprint_bgColor)(FMT&0x40f00000)
#define kprint_format_dataFormat(FMT) (kprint_dataFormat)(FMT&0x000f0000)
#define kprint_format_ktId(FMT) (kprint_dataFormat)(FMT&0x0000ffff)

#if __cplusplus
}
#endif