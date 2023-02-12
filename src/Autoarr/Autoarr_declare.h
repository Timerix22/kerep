#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define Autoarr_declare(type) \
\
struct Autoarr_##type; \
\
STRUCT(__functions_list_t_##type, \
    void (*add)(struct Autoarr_##type* ar, type element); \
    type (*get)(struct Autoarr_##type* ar, u32 index); \
    type* (*getptr)(struct Autoarr_##type* ar, u32 index); \
    void (*set)(struct Autoarr_##type* ar, u32 index, type element); \
    void (*freear)(struct Autoarr_##type* ar, bool freePtr); \
    type* (*toArray)(struct Autoarr_##type* ar); \
) \
\
STRUCT(Autoarr_##type, \
    u16 blocks_count; \
    u16 max_blocks_count; \
    u16 block_length; \
    u16 max_block_length; \
    type** values; \
    __functions_list_t_##type* functions; \
) \
\
Autoarr_##type* __Autoarr_create_##type(u16 max_blocks_count, u16 max_block_length); \
void __Autoarr_free_##type(Autoarr_##type* ar, bool freePtr); \
void ____Autoarr_free_##type(void* ar);

#define Autoarr(type) Autoarr_##type

#define Autoarr_create(type, max_blocks_count, max_block_length) \
    __Autoarr_create_##type(max_blocks_count, max_block_length)
#define Autoarr_add(autoarr, element) \
    autoarr->functions->add(autoarr, element)
#define Autoarr_get(autoarr, index) \
    autoarr->functions->get(autoarr,index)
#define Autoarr_getptr(autoarr, index) \
    autoarr->functions->getptr(autoarr,index)
#define Autoarr_set(autoarr, index, element) \
    autoarr->functions->set(autoarr, index, element)
#define Autoarr_free(autoarr, freePtr) \
    autoarr->functions->freear(autoarr, freePtr)
#define Autoarr_toArray(autoarr) \
    autoarr->functions->toArray(autoarr)

#define Autoarr_length(autoarr) \
    (u32)(!autoarr->blocks_count ? 0 : \
    autoarr->max_block_length*(autoarr->blocks_count-1)+autoarr->block_length)
#define Autoarr_max_length(autoarr) \
    (u32)(autoarr->max_block_length*autoarr->max_blocks_count)

#define Autoarr_pop(AR){ \
    if(AR->block_length==1){ \
        AR->blocks_count--; \
        AR->block_length=AR->max_block_length; \
        free(AR->values[AR->blocks_count]); \
    } \
    else AR->block_length--; \
}

#if __cplusplus
}
#endif