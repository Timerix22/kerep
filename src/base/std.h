#pragma once

#if __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
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
// Usually bool from stdbool.h is defined as macro, 
// so in other macros like ktid_##TYPE it will be replaced by _Bool.
// ktid__Bool will be created instead of ktid_bool
// In C++ bool is a keyword, so there is no need to redefine it.
#if !__cplusplus
typedef uint8 bool;
#define true  1
#define false 0
#endif

#define dbg(N) kprintf("\e[95m%d\n",N)

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


#define __count_args(\
    a0, a1, a2, a3, a4, a5, a6, a7,\
    a8, a9, a10,a11,a12,a13,a14,a15,\
    a16,a17,a18,a19,a20,a21,a22,a23,\
    a24,a25,a26,a27,a28,a29,a30,a31,\
    a32,...) a32
// Macro for counting variadic arguments
// (see usage in kprint.h)
#define count_args(ARGS...) __count_args(\
    ARGS,\
    32,31,30,29,28,27,26,25,\
    24,23,22,21,20,19,18,17,\
    16,15,14,13,12,11,10,9,\
    8, 7, 6, 5, 4, 3, 2, 1, 0)

/*
Cross-platform warning supression.
WARNING_DISABLE( W_EXAMPLE,
    some code producing W_EXAMPLE;
);
You can even embed it into macro in header (see kprint.h)
*/
#ifdef _MSC_VER
    #define PRAGMA_WARNING_PUSH __pragma(warning( push ))
    #define DISABLE_WARNING(wNumber) __pragma(warning( disable : wNumber ))
    #define PRAGMA_WARNING_POP  __pragma(warning( pop ))
#else
    #define _PRAGMA(P) _Pragma(#P)
    #define PRAGMA_WARNING_PUSH _PRAGMA(GCC diagnostic push)
    #define PRAGMA_WARNING_DISABLE(wName) _PRAGMA(GCC diagnostic ignored wName)
    #define PRAGMA_WARNING_POP  _PRAGMA(GCC diagnostic pop)
    #define W_INT_CONVERSION "-Wint-conversion"
#endif
#define WARNING_DISABLE(WARNING, CODE)\
    PRAGMA_WARNING_PUSH\
    PRAGMA_WARNING_DISABLE(WARNING)\
    CODE;\
    PRAGMA_WARNING_POP

#if __cplusplus
}
#endif