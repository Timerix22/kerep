#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../unitype.h"

typedef enum kprint_dataFormat{
    //              00100000 00000000
    //                ^            ^^
    //   dataFmtSet flag          type
    kprint_fmtInt       = 0x20000000, // default
    
    //              00100000 00000001
    kprint_fmtUInt      = 0x20010000, // mandatory for uint
    
    //              00100000 00000010
    kprint_fmtHex       = 0x20020000, // optional

    //              00100000 00000011
    kprint_fmtBin       = 0x20030000, // optional

    //              00110000 00000000
    //                ^^           ^^
    // dataFmtSet flag┘|          type
    //              notInteger flag
    kprint_fmtFloat     = 0x30000000, // mandatory for float
    
    //              00110000 00000001
    kprint_fmtChar      = 0x30010000, // optional for char
    
    //              00110000 00000010
    kprint_fmtString    = 0x30020000, // mandatory for char[], char* and string
    
    //              00110000 00000011
    //kprint_fmt?       = 0x30030000, // unused

    //              00000000 00000100
    //                            ^
    //                 prefix/postfix flag
    kprint_fmtWithPrefix=0x00040000,    // optional for hex or binary
    kprint_fmtWithPostfix=kprint_fmtWithPrefix, // optional for uint or float

    //              00000000 00001000
    //                           ^
    //                      uppercase flag // optional for hex, uint or float
    kprint_fmtUppercase=0x00080000
} kprint_dataFmt;


typedef struct {
    unsigned char fgColorChanged : 1;
    unsigned char bgColorChanged : 1;
    unsigned char dataFmtSet : 1;
    unsigned char notInteger : 1;
    unsigned char fgColor : 4;
    unsigned char bgColor : 4;
    unsigned char uppercase : 1;
    unsigned char withPrefix : 1;
    unsigned char dataFmt : 2;
    kerepTypeId typeId;
} kprint_format;

#if __cplusplus
}
#endif