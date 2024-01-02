#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../network_types.h"

typedef struct knSocketUDP {
    i64 socketfd;
    knIPV4Endpoint localEndpoint;
    // TODO socket status enum
} knSocketUDP;
ktid_declare(knSocketUDP);

///@return Maybe<knSocketUDP*> new socket
Maybe knSocketUDP_open();

///@param direction receive/send/both
///@return Maybe<void> error or nothing
Maybe knSocketUDP_shutdown(knSocketUDP* socket, knShutdownType direction);

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

///@param buffer buffer for receiving data
///@param bufferLength 0-4294967295
///@return Maybe<u64> received bytes amount
Maybe knSocketUDP_receive(knSocketUDP* socket, char* buffer, u32 bufferLength);


#if __cplusplus
}
#endif