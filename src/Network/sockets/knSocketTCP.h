#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../network_types.h"

typedef struct knSocketTCP {
    i64 socketfd;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
    // TODO socket status enum
} knSocketTCP;
ktid_declare(knSocketTCP);

///@note EXAMPLE 1: socket = open(false); bind(socket, localhost:8080); close(socket); - the socket on port 8080 still unavaliable for several minutes
///@note EXAMPLE 2: socket = open(true); bind(socket, localhost:8080); close(socket); - the socket on port 8080 can be opened again
///@param allowReuse enables binding multiple sockets to single port. Set to TRUE on a listening socket if you want to bind it to the same port after close.
///@return Maybe<knSocketTCP*> new socket
Maybe knSocketTCP_open(bool allowReuse);

///@param direction receive/send/both
///@return Maybe<void> error or nothing
Maybe knSocketTCP_shutdown(knSocketTCP* socket, knShutdownType direction);

/// closes file descriptor and frees socket pointer
///@return Maybe<void> error or nothing
Maybe knSocketTCP_close(knSocketTCP* socket);

///start listening at local endpoint
///@return Maybe<void> error or nothing
Maybe knSocketTCP_listen(knSocketTCP* socket, knIPV4Endpoint localEndp);

///sets socket remote endpoint
///@return Maybe<void> error or nothing
Maybe knSocketTCP_connect(knSocketTCP* socket, knIPV4Endpoint remoteEndp);

///@return Maybe<knSocketTCP*> new socket connected to client
Maybe knSocketTCP_accept(knSocketTCP* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocketTCP_send(knSocketTCP* socket, char* data, u32 dataLength);

///@param buffer buffer for receiving data
///@param bufferLength 0-4294967295
///@return Maybe<u64> received bytes amount
Maybe knSocketTCP_receive(knSocketTCP* socket, char* buffer, u32 bufferLength);

#if __cplusplus
}
#endif