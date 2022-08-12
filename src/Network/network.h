#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../Hashtable/Hashtable.h"


#if defined(_MSC_VER) || defined(_WIN64) || defined(_WIN32) || 1
    #define KN_USE_WINSOCK 1
#endif

#if KN_USE_WINSOCK
    #include "winsock.h"
#else
    #include "../Hashtable/Hashtable.h"
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h> 
#endif

#define KNPAC_MAX_DATA_SIZE (65535-sizeof(knPackage)+sizeof(uint8*))


typedef enum __attribute__((__packed__)) knPacVersion {
    knPac_V1
} knPacVersion;

typedef struct knPackage {
    char header[5];             // knpac
    knPacVersion version;       // protocol version
    uint16 data_size;           // size of data block in bytes (1-KNPAC_MAX_DATA_SIZE)
    uint32 package_num;         // number in sequence of sent packages
    uint32 destination_hash;    // hash32 of knDestination.name
    uint64 data_hash;           // hash64 of data
    uint8* data;                // ptr to data
} knPackage;

typedef struct knPackageQueueElem knPackageQueueElem;
struct knPackageQueueElem {
    union{
        knPackage;
        knPackage package;
    };
    knPackageQueueElem* previousElem;
    knPackageQueueElem* nextElem;
};

typedef struct knDestination {
    knPackageQueueElem* queueStart;

} knDestination;

typedef union knIPV4Address {
    uint32 address;
    char bytes[4];
} knIPV4Address;

#define knIPV4Address_fromBytes(A, B, C, D) (knIPV4Address){.bytes={A,B,C,D}}

///@return Maybe<uint64> as Maybe<knIPV4Address>
Maybe knIPV4Address_fromStr(char* addrStr);

typedef uint16 knPort;

typedef struct __attribute__((__packed__)) knIPV4Endpoint {
    knIPV4Address address;
    knPort port;
} knIPV4Endpoint;

#define knIPV4Endpoint_create(ADDR, PORT) (knIPV4Endpoint){ADDR, PORT}

typedef enum __attribute__((__packed__)) knSockType {
    knSockType_TCP, knSockType_UDP 
} knSockType;

typedef struct knSocket {
    knDestination* destinations;
    int socketfd;
    knSockType type;
    knIPV4Endpoint localEndpoint;
    knIPV4Endpoint remoteEndpoint;
} knSocket;

///@returns Maybe<knSocket*> new socket
Maybe knSocket_open(knSockType sockType);

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
Maybe knSocket_send(knSocket* socket, uint8* data, uint32 dataLength);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<uint64> recieved bytes amount
Maybe knSocket_recieve(knSocket* socket, uint8* buffer, uint32 bufferLength);         


#if __cplusplus
}
#endif