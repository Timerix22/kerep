#pragma once

#if __cplusplus
extern "C" {
#endif

typedef enum kprint_fgColor{
    //              10000000 00000000  00000000 00000000
    //              ^   ^^^^
    //              |   color num
    // fgColorChanged flag   

    kprint_fgBlack      = 0x80000000,
    kprint_fgDarkRed    = 0x81000000,
    kprint_fgDarkGreen  = 0x82000000,
    kprint_fgDarkYellow = 0x83000000,
    kprint_fgDarkBlue   = 0x84000000,
    kprint_fgDarkMagneta= 0x85000000,
    kprint_fgDarkCyan   = 0x86000000,
    kprint_fgGray       = 0x87000000,
    kprint_fgDarkGray   = 0x88000000,
    kprint_fgRed        = 0x89000000,
    kprint_fgGreen      = 0x8a000000,
    kprint_fgYellow     = 0x8b000000,
    kprint_fgBlue       = 0x8c000000,
    kprint_fgMagneta    = 0x8d000000,
    kprint_fgCyan       = 0x8e000000,
    kprint_fgWhite      = 0x8f000000 
} kprint_fgColor;

typedef enum kprint_bgColor{
    //              01000000 00000000  00000000 00000000
    //               ^       ^^^^
    // bgColorChanged flag   color num
    kprint_bgBlack      = 0x40000000,
    kprint_bgDarkRed    = 0x40100000,
    kprint_bgDarkGreen  = 0x40200000,
    kprint_bgDarkYellow = 0x40300000,
    kprint_bgDarkBlue   = 0x40400000,
    kprint_bgDarkMagneta= 0x40500000,
    kprint_bgDarkCyan   = 0x40600000,
    kprint_bgGray       = 0x40700000,
    kprint_bgDarkGray   = 0x40800000,
    kprint_bgRed        = 0x40900000,
    kprint_bgGreen      = 0x40a00000,
    kprint_bgYellow     = 0x40b00000,
    kprint_bgBlue       = 0x40c00000,
    kprint_bgMagneta    = 0x40d00000,
    kprint_bgCyan       = 0x40e00000,
    kprint_bgWhite      = 0x40f00000 
} kprint_bgColor;

#if __cplusplus
}
#endif