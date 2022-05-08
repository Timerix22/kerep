#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../Hashtable/Hashtable.h"

#if defined(_MSC_VER) || defined(_WIN64) || defined(_WIN32)
    #include "winsock.h"
#else
    #include "../Hashtable/Hashtable.h"
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <netdb.h> 
#endif

#define KNPAC_MAX_DATA_SIZE 65503

typedef struct knPackage{
    char header[5];             // knpac
    uint8 version;              // protocol version
    uint16 data_size;           // size of data block in bytes (1-)
    uint32 package_num;         // number in sequence of sent packages
    uint32 destination_hash;    // hash32 of knDestination.name
    uint64 data_hash;           // hash64 of data
    uint8* data;                // ptr to data
} knPackage;

typedef struct knDestination{
    char* name;

} knDestination;

typedef struct knSocket {
    Hashtable* destinations;
    int socketfd;
} knSocket;

#if __cplusplus
}
#endif