#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "knSocket.h"

#define KNPAC_MAX_DATA_SIZE (65535-sizeof(knPackage)+sizeof(uint8*))


typedef enum __attribute__((__packed__)) knPacVersion {
    knPac_V1
} knPacVersion;
ktid_declare(knPacVersion);

static const char knPacHeader[5]={'k','n','p','a','c'};

typedef struct knPackage {
    char header[5];             // knpac
    knPacVersion version;       // protocol version
    uint16 data_size;           // size of data block in bytes (1-KNPAC_MAX_DATA_SIZE)
    uint32 channel_id;          // id of knChannel in socket
    uint32 package_num;         // number in sequence of sent packages
    uint64 data_hash;           // hash64 of data
    uint8* data;                // ptr to data
} knPackage;
ktid_declare(knPackage);

typedef struct knPackageQueueElem knPackageQueueElem;
struct knPackageQueueElem {
    knPackage package;
    knPackageQueueElem* previousElem;
    knPackageQueueElem* nextElem;
};
ktid_declare(knPackageQueueElem);

typedef struct knChannel {
    knPackageQueueElem* queueStart;
} knChannel;
ktid_declare(knChannel);

typedef struct knSocketChanneled{
    knSocketProtocol type;
    int64 socketfd;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
    uint16 channelsAmount;
    knChannel** channels;
} knSocketChanneled;
ktid_declare(knSocketChanneled);


///@return Maybe<knSocketChanneled*> new socket
Maybe knSocketChanneled_open(knSocketProtocol sockType);

///@return Maybe<void> error or nothing
Maybe knSocketChanneled_close(knSocketChanneled* socket);

///@return Maybe<uint64> channel index
Maybe knSocketChanneled_createChannel(knSocketChanneled* socket);

///sets socket local endpoint
///@return Maybe<void> error or nothing
Maybe knSocketChanneled_bind(knSocketChanneled* socket, knIPV4Endpoint localEndp);

///sets socket remote endpoint
///@return Maybe<void> error or nothing
Maybe knSocketChanneled_connect(knSocketChanneled* socket, knIPV4Endpoint remoteEndp);

///@return Maybe<knSocketChanneled*> new socket connected to client
Maybe knSocketChanneled_accept(knSocketChanneled* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocketChanneled_send(knSocketChanneled* socket, uint16 destinationIndex, uint8* data, uint32 dataLength);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<uint64> recieved bytes amount
Maybe knSocketChanneled_recieve(knSocketChanneled* socket, uint16 destinationIndex, uint8* buffer, uint32 bufferLength);

#if __cplusplus
}
#endif