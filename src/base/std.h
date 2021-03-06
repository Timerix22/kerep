#pragma once

#if __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>
#include <setjmp.h>


#define dbg(N) printf("\e[95m%d\n",N)


#ifdef _MSC_VER
    #pragma comment(lib, "mincore_downlevel.lib") // Support OS older than SDK
    #define _CRT_SECURE_NO_WARNINGS 1
    #define EXPORT __declspec(dllexport)
    #define CALL  __cdecl
#elif defined(__GNUC__)
    #define EXPORT __attribute__((visibility("default")))
    #if __SIZEOF_POINTER__ == 4
        #define CALL  __attribute__((__cdecl__))
    #else
        #define CALL
    #endif
    #ifndef typeof
        #define typeof __typeof__
    #endif
#else
    #pragma GCC error "unknown compiler"
#endif

#ifdef _MSC_VER
    #define IFWIN(YES, NO) YES
    #define IFMSC(YES, NO) YES
#elif defined(_WIN64) || defined(_WIN32)
    #define IFWIN(YES, NO) YES
    #define IFMSC(YES, NO) NO
#elif defined(__GNUC__)
    #define IFWIN(YES, NO) NO
    #define IFMSC(YES, NO) NO
#else
    #pragma GCC error "unknown compiler"
#endif

#ifndef NULL
    #define NULL ((void*)0)
#endif

#if __cplusplus
}
#endif