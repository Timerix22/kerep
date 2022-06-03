#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

uint32 hash_sdbm32(uint32 oldhash, void* buf, uint32 len);
#define hashb_sdbm32(BUF, LEN) hash_sdbm32(0xFFFFFFFF, BUF, LEN)
#define hashs_sdbm32(STR)      hash_sdbm32(0xFFFFFFFF, STR, cptr_length(STR))

uint32 hash_crc32(uint32 oldhash, void* buf, uint32 len);
#define hashb_crc32(BUF, LEN) hash_crc32(0xFFFFFFFF, BUF, LEN)
#define hashs_crc32(STR)      hash_crc32(0xFFFFFFFF, STR, cptr_length(STR))

#if __cplusplus
}
#endif