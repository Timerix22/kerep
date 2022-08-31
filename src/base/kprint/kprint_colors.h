#pragma once

#if __cplusplus
extern "C" {
#endif

typedef enum kprint_fgColor{
    //              01000000 0000000
    //               ^  ^^^^
    //               |  color num
    // fgColorChanged flag   

    kprint_fgBlack      = 0x80000000, // optional
    kprint_fgDarkRed    = 0x81000000, // optional
    kprint_fgDarkGreen  = 0x82000000, // optional
    kprint_fgDarkYellow = 0x83000000, // optional
    kprint_fgDarkBlue   = 0x84000000, // optional
    kprint_fgDarkMagneta= 0x85000000, // optional
    kprint_fgDarkCyan   = 0x86000000, // optional
    kprint_fgGray       = 0x87000000, // optional
    kprint_fgDarkGray   = 0x88000000, // optional
    kprint_fgRed        = 0x89000000, // optional
    kprint_fgGreen      = 0x8a000000, // optional
    kprint_fgYellow     = 0x8b000000, // optional
    kprint_fgBlue       = 0x8c000000, // optional
    kprint_fgMagneta    = 0x8d000000, // optional
    kprint_fgCyan       = 0x8e000000, // optional
    kprint_fgWhite      = 0x8f000000  // optional
} kprint_fgColor;

typedef enum kprint_bgColor{
    //              01000000 0000000
    //               ^       ^^^^
    // bgColorChanged flag   color num
    kprint_bgBlack      = 0x40000000, // optional
    kprint_bgDarkRed    = 0x40100000, // optional
    kprint_bgDarkGreen  = 0x40200000, // optional
    kprint_bgDarkYellow = 0x40300000, // optional
    kprint_bgDarkBlue   = 0x40400000, // optional
    kprint_bgDarkMagneta= 0x40500000, // optional
    kprint_bgDarkCyan   = 0x40600000, // optional
    kprint_bgGray       = 0x40700000, // optional
    kprint_bgDarkGray   = 0x40800000, // optional
    kprint_bgRed        = 0x40900000, // optional
    kprint_bgGreen      = 0x40a00000, // optional
    kprint_bgYellow     = 0x40b00000, // optional
    kprint_bgBlue       = 0x40c00000, // optional
    kprint_bgMagneta    = 0x40d00000, // optional
    kprint_bgCyan       = 0x40e00000, // optional
    kprint_bgWhite      = 0x40f00000  // optional
} kprint_bgColor;

#if __cplusplus
}
#endif