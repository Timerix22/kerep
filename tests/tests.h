#pragma once

#include "../src/base/base.h"

#if __cplusplus
extern "C" {
#endif

void test_cptr();
void test_string();
void test_safethrow();
void test_searchtree();
void test_autoarr();
void test_hash_functions();
void test_hashtable();
void test_dtsod();
void test_autoarrVsVector();
void test_rng_algorithms();
void test_kprint_colors();
void test_kprint();
void test_type_system();

inline void test_all(){
    kprintf("\e[97mkerep tests are starting!\n");
    optime(__func__, 1,
        test_cptr();
        test_type_system();
        test_string();
        test_safethrow();
        test_searchtree();
        test_autoarr();
        test_autoarrVsVector();
        test_rng_algorithms();
        test_kprint_colors();
        test_kprint();
        test_hash_functions();
        test_hashtable();
        test_dtsod();
        kprintf("\e[96m--------------------------------------\e[0m\n");
    );
}

#define PRINT_SIZEOF(T) kprintf("\e[94m" #T " size: \e[96m" IFWIN("%llu", "%lu") "\n", sizeof(T))

#if __cplusplus
}
#endif
