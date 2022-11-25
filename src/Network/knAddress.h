#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"


typedef uint16 knPort;

typedef union knIPV4Address {
    uint32 address;
    char bytes[4];
} knIPV4Address;
ktid_declare(knIPV4Address);

#define knIPV4Address_fromBytes(A, B, C, D) (knIPV4Address){.bytes={A,B,C,D}}

///@return Maybe<knIPV4Address> as Maybe<knIPV4Address>
Maybe knIPV4Address_fromStr(char* addrStr);

typedef struct knIPV4Endpoint {
    knIPV4Address address;
    knPort port;
} knIPV4Endpoint;
ktid_declare(knIPV4Endpoint);

#define knIPV4Endpoint_create(ADDR, PORT) (knIPV4Endpoint){ADDR, PORT}

#if __cplusplus
}
#endif