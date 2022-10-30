#pragma once

#include "../src/base/base.h"

#if __cplusplus
extern "C" {
#endif

void test_string();
void test_safethrow();
void test_searchtree();
void test_autoarr();
void test_hash_functions();
void test_hashtable();
void test_dtsod();
void test_kprint_colors();
void test_autoarrVsVector();
void test_rng_algorithms();

#define PRINT_SIZEOF(T) kprintf("\e[94m" #T " size: \e[96m" IFWIN("%llu", "%lu") "\n", sizeof(T))

#if __cplusplus
}
#endif
