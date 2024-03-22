#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/type_system/base_toString.h"

#define kprintf_INVALID_FORMAT -1
#define kprintf_BUFFER_IS_NULL -2
#define kprintf_BUFFER_IS_TOO_SMALL -3

/// cross-platform printf analog
///@return number of processed format string characters or error code
i32 kprintf(const char* format, ...);

/// @return number of processed format string characters or error code
i32 ksprintf(char* buffer, i32 buffer_size, const char* format, ...);


// printf format terminal color sequence
#define _PRINTF_COLOR(N) "\e["#N"m"

// foreground dark color codes
#define FBLK _PRINTF_COLOR(30)
#define FREDD _PRINTF_COLOR(31)
#define FGRND _PRINTF_COLOR(32)
#define FYELD _PRINTF_COLOR(33)
#define FBLUD _PRINTF_COLOR(34)
#define FMAGD _PRINTF_COLOR(35)
#define FCYND _PRINTF_COLOR(36)
#define FGRY _PRINTF_COLOR(37)

// foreground bright color codes
#define FGRYD _PRINTF_COLOR(90)
#define FRED _PRINTF_COLOR(91)
#define FGRN _PRINTF_COLOR(92)
#define FYEL _PRINTF_COLOR(93)
#define FBLU _PRINTF_COLOR(94)
#define FMAG _PRINTF_COLOR(95)
#define FCYN _PRINTF_COLOR(96)
#define FWHI _PRINTF_COLOR(97)

// background dark color codes
#define BBLK _PRINTF_COLOR(40)
#define BREDD _PRINTF_COLOR(41)
#define BGRND _PRINTF_COLOR(42)
#define BYELD _PRINTF_COLOR(43)
#define BBLUD _PRINTF_COLOR(44)
#define BMAGD _PRINTF_COLOR(45)
#define BCYND _PRINTF_COLOR(46)
#define BGRY _PRINTF_COLOR(47)

// background bright color codes
#define BGRYD _PRINTF_COLOR(100)
#define BRED _PRINTF_COLOR(101)
#define BGRN _PRINTF_COLOR(102)
#define BYEL _PRINTF_COLOR(103)
#define BBLU _PRINTF_COLOR(104)
#define BMAG _PRINTF_COLOR(105)
#define BCYN _PRINTF_COLOR(106)
#define BWHI _PRINTF_COLOR(107)

#if __cplusplus
}
#endif