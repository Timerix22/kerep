#pragma once

#if __cplusplus
extern "C" {
#endif

#include "knSocket.h"


typedef struct knChanneledSocket{
    union {
        knSocket;
        knSocket base;
    };
    uint16 channelsAmount;
    knChannel** channels;
} knChanneledSocket;

#if __cplusplus
}
#endif