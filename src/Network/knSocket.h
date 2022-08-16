#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "knAddress.h"
#include "knPackage.h"


typedef enum __attribute__((__packed__)) knSocketType {
    knSocketType_TCP, knSocketType_UDP 
} knSocketType;

typedef struct knSocket {
    knSocketType type;
    uint16 channelsAmount;
    knChannel** channels;
    int64 socketfd;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
} knSocket;

///@return Maybe<knSocket*> new socket
Maybe knSocket_open(knSocketType sockType);

///@return Maybe<void> error or nothing
Maybe knSocket_close(knSocket* socket);

///@return Maybe<uint64> channel index
Maybe knSocket_createChannel(knSocket* socket);

///sets socket local endpoint
///@return Maybe<void> error or nothing
Maybe knSocket_bind(knSocket* socket, knIPV4Endpoint localEndp);

///sets socket remote endpoint
///@return Maybe<void> error or nothing
Maybe knSocket_connect(knSocket* socket, knIPV4Endpoint remoteEndp);

///@return Maybe<knSocket*> new socket connected to client
Maybe knSocket_accept(knSocket* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocket_send(knSocket* socket, uint16 destinationIndex, uint8* data, uint32 dataLength);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<uint64> recieved bytes amount
Maybe knSocket_recieve(knSocket* socket, uint16 destinationIndex, uint8* buffer, uint32 bufferLength);


#if __cplusplus
}
#endif