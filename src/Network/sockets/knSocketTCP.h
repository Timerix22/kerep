#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../base/base.h"
#include "../knAddress.h"

typedef struct knSocketTCP {
    i64 socketfd;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
} knSocketTCP;
ktid_declare(knSocketTCP);

///@return Maybe<knSocketTCP*> new socket
Maybe knSocketTCP_open();

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

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<u64> recieved bytes amount
Maybe knSocketTCP_recieve(knSocketTCP* socket, char* buffer, u32 bufferLength);

#if __cplusplus
}
#endif