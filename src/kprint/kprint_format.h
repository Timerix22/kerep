#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/std.h"
#include "../base/type_system/ktid.h"

/// kprint_format
typedef uint32 kp_fmt;

typedef enum kp_dataFmt{
// 00000000 00000000  00000000 00000000
//              ^^^^
//              type
    kp_i = 0x00000000,
    kp_u = 0x00010000,
    kp_h = 0x00020000,
    kp_b = 0x00030000,
    kp_f = 0x00040000,
    kp_c = 0x00050000,
    kp_s = 0x00060000,
    
// 00100000 00000000  00000000 00000000
//   ^
// prefix/postfix flag
    kp_pre=0x20000000,
    kp_post=kp_pre,

// 00010000 00000000  00000000 00000000
//    ^
// uppercase flag
    kp_upper=0x10000000
} kp_dataFmt;

#define kp_fmt_fgColorSet(FMT) (bool)((FMT&0x80000000)!=0)
#define kp_fmt_bgColorSet(FMT) (bool)((FMT&0x40000000)!=0)
#define kp_fmt_withPrefix(FMT) (bool)((FMT&kp_pre)!=0)
#define kp_fmt_withPostfix(FMT) (bool)((FMT&kp_post)!=0)
#define kp_fmt_isUpper(FMT) (bool)((FMT&kp_upper)!=0)
#define kp_fmt_fgColor(FMT) (kp_fgColor)(FMT&0x8f000000)
#define kp_fmt_bgColor(FMT) (kp_bgColor)(FMT&0x40f00000)
#define kp_fmt_dataFormat(FMT) (kp_dataFmt)(FMT&0x000f0000)
#define kp_fmt_ktid(FMT) (ktid)(FMT&0x0000ffff)

#if __cplusplus
}
#endif