#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#if defined(_MSC_VER) || defined(_WIN64) || defined(_WIN32)
    #define KN_USE_WINSOCK 1
#endif

#include "knAddress.h"
#include "knSocket.h"
#include "knSocketChanneled.h"

#if __cplusplus
}
#endif