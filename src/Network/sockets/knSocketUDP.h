#pragma once

#if __cplusplus
extern "C" {
#endif

#include "knSocketUDP.h"

typedef struct knSocketUDP {
    i64 socketfd;
    knIPV4Endpoint localEndpoint;
} knSocketUDP;
ktid_declare(knSocketUDP);

///@return Maybe<knSocketUDP*> new socket
Maybe knSocketUDP_open();

///@return Maybe<void> error or nothing
Maybe knSocketUDP_close(knSocketUDP* socket);

///start listening at local endpoint
///@return Maybe<void> error or nothing
Maybe knSocketUDP_listen(knSocketUDP* socket, knIPV4Endpoint localEndp);

///@return Maybe<knSocketUDP*> new socket connected to client
Maybe knSocketUDP_accept(knSocketUDP* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocketUDP_sendto(knSocketUDP* socket, char* data, u32 dataLength, knIPV4Endpoint destination);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<u64> recieved bytes amount
Maybe knSocketUDP_recieve(knSocketUDP* socket, char* buffer, u32 bufferLength);


#if __cplusplus
}
#endif