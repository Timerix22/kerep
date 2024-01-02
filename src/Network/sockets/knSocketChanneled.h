#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../../base/base.h"
#include "../knAddress.h"

#define KNPAC_MAX_DATA_SIZE (65535-sizeof(knPackage)+sizeof(u8*))


typedef enum __attribute__((__packed__)) knPacVersion {
    knPac_V1=1
} knPacVersion;

static const char knPacHeader[5]={'k','n','p','a','c'};

typedef struct knPackage {
    char header[5];             // knpac
    knPacVersion version;       // protocol version
    u16 data_size;           // size of data block in bytes (1-KNPAC_MAX_DATA_SIZE)
    u32 channel_id;          // id of knChannel in socket
    u32 package_num;         // number in sequence of sent packages
    u64 data_hash;           // hash64 of data
    u8* data;                // ptr to data
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
    i64 socketfd;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
    u16 channelsAmount;
    knChannel** channels;
} knSocketChanneled;
ktid_declare(knSocketChanneled);


///@return Maybe<knSocketChanneled*> new socket
Maybe knSocketChanneled_open();

///@return Maybe<void> error or nothing
Maybe knSocketChanneled_close(knSocketChanneled* socket);

///@return Maybe<u64> channel index
Maybe knSocketChanneled_createChannel(knSocketChanneled* socket);

///start listening at local endpoint
///@return Maybe<void> error or nothing
Maybe knSocketChanneled_listen(knSocketChanneled* socket, knIPV4Endpoint localEndp);

///sets socket remote endpoint
///@return Maybe<void> error or nothing
Maybe knSocketChanneled_connect(knSocketChanneled* socket, knIPV4Endpoint remoteEndp);

///@return Maybe<knSocketChanneled*> new socket connected to client
Maybe knSocketChanneled_accept(knSocketChanneled* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocketChanneled_send(knSocketChanneled* socket, u16 destinationIndex, u8* data, u32 dataLength);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<u64> received bytes amount
Maybe knSocketChanneled_receive(knSocketChanneled* socket, u16 destinationIndex, u8* buffer, u32 bufferLength);

#if __cplusplus
}
#endif