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

///@note EXAMPLE 1: socket = open(false); bind(socket, localhost:8080); close(socket); - the socket on port 8080 still unavaliable for several minutes
///@note EXAMPLE 2: socket = open(true); bind(socket, localhost:8080); close(socket); - the socket on port 8080 can be opened again
///@param allowReuse enables binding multiple sockets to single port. Set to TRUE on a listening socket if you want to bind it to the same port after close.
///@return Maybe<knSocketUDP*> new socket
Maybe knSocketUDP_open(bool allowReuse);

///@param direction receive/send/both
///@return Maybe<void> error or nothing
Maybe knSocketUDP_shutdown(knSocketUDP* socket, knShutdownType direction);

/// closes file descriptor and frees socket pointer
///@return Maybe<void> error or nothing
Maybe knSocketUDP_close(knSocketUDP* socket);

/// binds socket to a local endpoint
///@return Maybe<void> error or nothing
Maybe knSocketUDP_bind(knSocketUDP* socket, knIPV4Endpoint localEndp);

/// sends one package to destination endpoint
///@param buffer buffer for receiving data
///@param dataLength 0-64k
///@param destEnd destination endpoint
///@return Maybe<void>
Maybe knSocketUDP_sendTo(knSocketUDP* socket, char* buffer, u32 dataLength, knIPV4Endpoint destEnd);

/// receives one package from anywhere
///@param buffer buffer for receiving data
///@param bufferLength 0-64k
///@param senderEnd [OUT] endpoint UPD package was sent from
///@return Maybe<u64> received bytes amount
Maybe knSocketUDP_receiveAny(knSocketUDP* socket, char* buffer, u32 bufferLength, knIPV4Endpoint* senderEnd);

#if __cplusplus
}
#endif