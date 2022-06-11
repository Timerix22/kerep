#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#define hashb(FUNC, BUF, LEN) FUNC(0xFFFFFFFF, BUF, LEN)
#define hashs(FUNC, STR)      FUNC(0xFFFFFFFF, STR, cptr_length(STR))

uint32 hash_sdbm32(uint32 oldhash, void* buf, uint32 len);
uint32 hash_crc32(uint32 oldhash, void* buf, uint32 len);
uint32 hash_xxh32(uint32 oldhash, void* buf, uint32 len);
uint64 hash_xxh3_64(uint32 oldhash, void* buf, uint32 len);

#if __cplusplus
}
#endif