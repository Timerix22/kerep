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

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef float float32;
typedef double float64;

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
        #define typeof(X) __typeof__(X)
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

#ifndef sprintf_s
    #define sprintf_s(BUF, BUFSIZE, FORMAT, ...) sprintf(BUF, FORMAT, ## __VA_ARGS__)
#endif

#if __cplusplus
}
#endif