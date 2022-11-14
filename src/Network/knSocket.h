#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "knAddress.h"


typedef enum __attribute__((__packed__)) knSocketProtocol {
    knSocketProtocol_TCP, knSocketProtocol_UDP, knSocket_Channeled
} knSocketProtocol;
ktId_declare(knSocketProtocol);

typedef struct knSocket {
    knSocketProtocol type;
    int64 socketfd;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
    // uint16 channelsAmount;
    // knChannel** channels;
} knSocket;
ktId_declare(knSocket);

///@return Maybe<knSocket*> new socket
Maybe knSocket_open(knSocketProtocol sockType);

///@return Maybe<void> error or nothing
Maybe knSocket_close(knSocket* socket);

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