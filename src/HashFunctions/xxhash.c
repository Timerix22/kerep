#include "hash.h"
#define XXH_INLINE_ALL
#define XXH_STATIC_LINKING_ONLY   /* access advanced declarations */
#define XXH_IMPLEMENTATION   /* access definitions */
#include "./xxhash.h"

uint32 hash_xxh32(uint32 oldhash, void* buf, uint32 len){
    return XXH32(buf,len,oldhash);
}
uint64 hash_xxh3_64(uint32 oldhash, void* buf, uint32 len){
    return XXH3_64bits_withSeed(buf,len,oldhash);
}