#pragma once

#if __cplusplus
extern "C" {
#endif

#include "Autoarr_declare.h"
#include "Autoarr_define.h"

Autoarr_declare(Pointer)
Autoarr_declare(char)
Autoarr_declare(bool)
Autoarr_declare(f32)
Autoarr_declare(f64)
Autoarr_declare(i8)
Autoarr_declare(u8)
Autoarr_declare(i16)
Autoarr_declare(u16)
Autoarr_declare(i32)
Autoarr_declare(u32)
Autoarr_declare(i64)
Autoarr_declare(u64)

Autoarr_declare(Unitype)

#define Autoarr_foreach(ar, elem, codeblock...) { \
    if(ar->chunks_count>0) { \
        typeof(**ar->chunks) elem; \
        for(u16 chunkI=0;chunkI<ar->chunks_count-1;chunkI++) \
            for(u32 elemI=0;elemI<ar->max_chunk_length;elemI++){ \
                elem=ar->chunks[chunkI][elemI]; \
                { codeblock; } \
            } \
        for(u16 elemI=0;elemI<ar->chunk_length;elemI++){ \
            elem=ar->chunks[ar->chunks_count-1][elemI]; \
            { codeblock; } \
        } \
    } \
}

#if __cplusplus
}
#endif