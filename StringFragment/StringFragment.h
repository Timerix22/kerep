#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

// part of string
typedef struct StringFragment{
    char* ptr; // may be without '\0' at the end
    uint32 offset;
    uint32 length;
} StringFragment;

static const StringFragment stringNull={NULL,0,0};

// copies <length> characters from <ptr+offset> to new StringFragment (adding '\0' at the end)
StringFragment StringFragment_extract(StringFragment str);

// compares two strings, NullPtr-friendly
bool StringFragment_compare(StringFragment str0, StringFragment str1);

// creates new StringFragment which is reversed variant of <s>
StringFragment StringFragment_reverse(StringFragment s);

#if __cplusplus
}
#endif