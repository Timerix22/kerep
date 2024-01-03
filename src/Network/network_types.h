#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

typedef u16 knPort;
#define knPort_INVALID ((knPort)~0)
#define knPort_isINVALID(PORT) (PORT == knPort_INVALID)

typedef union knIPV4Address {
    u32 UintBigEndian;
    char bytes[4];
} knIPV4Address;
kt_declare(knIPV4Address);

#define knIPV4Address_fromBytes(A, B, C, D) ((knIPV4Address){.bytes={A,B,C,D}})
#define knIPV4Address_fromU32(N) ((knIPV4Address){.UintBigEndian=N})


#define knIPV4Address_ANY      knIPV4Address_fromBytes(0,0,0,0)
#define knIPV4Address_LOOPBACK knIPV4Address_fromBytes(127,0,0,1)
#define knIPV4Address_INVALID  knIPV4Address_fromBytes(255,255,255,255)
#define knIPV4Address_isINVALID(ADDR) (ADDR.UintBigEndian == ~0)

///@return Maybe<null>
Maybe knIPV4Address_fromStr(char* addrStr, knIPV4Address* addrPtr);

char* knIPV4Address_toString(knIPV4Address* address);


STRUCT(knIPV4Endpoint,
    knIPV4Address address;
    knPort port;
)

#define knIPV4Endpoint_create(ADDR, PORT) ((knIPV4Endpoint){ADDR, PORT})

#define knIPV4Endpoint_INVALID knIPV4Endpoint_create(knIPV4Address_INVALID, knPort_INVALID)
#define knIPV4Endpoint_isINVALID(ENDP) (knIPV4Address_isINVALID(ENDP.address) || knPort_isINVALID(ENDP.port))

///@return Maybe<null>
Maybe knIPV4Endpoint_fromStr(char* endStr, knIPV4Endpoint* endVal);

char* knIPV4Endpoint_toString(knIPV4Endpoint* end);


typedef enum knShutdownType {
    knShutdownType_Receive = 0,
    knShutdownType_Send = 1,
    knShutdownType_Both = 2,
} knShutdownType;

#if __cplusplus
}
#endif