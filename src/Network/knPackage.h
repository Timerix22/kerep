#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"


#define KNPAC_MAX_DATA_SIZE (65535-sizeof(knPackage)+sizeof(uint8*))


typedef enum __attribute__((__packed__)) knPacVersion {
    knPac_V1
} knPacVersion;

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

typedef struct knPackageQueueElem knPackageQueueElem;
struct knPackageQueueElem {
    union {
        knPackage;
        knPackage package;
    };
    knPackageQueueElem* previousElem;
    knPackageQueueElem* nextElem;
};

typedef struct knChannel {
    knPackageQueueElem* queueStart;
} knChannel;

#if __cplusplus
}
#endif