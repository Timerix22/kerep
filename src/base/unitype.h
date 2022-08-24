#pragma once

#if __cplusplus
extern "C" {
#endif

#include "types.h"

typedef struct Unitype{
    union {
        int64 Int64;
        uint64 UInt64;
        double Float64;
        bool Bool;
        void* VoidPtr;
        char Bytes[8];
    };
    kerepTypeId typeId;
    bool allocatedInHeap; // should Unitype_free call free() to VoidPtr*
} Unitype;
kerepType_declare(Unitype);
kerepType_declare(UnitypePtr);


#define __Uni(TYPE,VAL) (Unitype){\
    .TYPE_NAME=VAL, .typeId=kerepTypeId_##TYPE, .allocatedInHeap=false}

#define UniInt64(VAL) __Uni(Int64, VAL)
#define UniUInt64(VAL) __Uni(UInt64, VAL)
#define UniFloat64(VAL) __Uni(Float64, VAL)
#define UniBool(VAL) __Uni(Bool, VAL)

#define UniPtrStack(TYPE_NAME,VAL) (Unitype){\
    .VoidPtr=VAL, .typeId=kerepTypeId_##TYPE_NAME, .allocatedInHeap=false}
#define UniPtrHeap (TYPE_NAME,VAL) (Unitype){\
    .VoidPtr=VAL, .typeId=kerepTypeId_##TYPE_NAME, .allocatedInHeap=true}

#define UniNull  UniPtrStack(Null, NULL)
#define UniTrue  UniBool(true)
#define UniFalse UniBool(false)

// frees VoidPtr value or does nothing if type isn't pointer
void Unitype_free(Unitype u);
void __UnitypePtr_free(void* u);
void printuni(Unitype v);
char* sprintuni(Unitype v);

#if __cplusplus
}
#endif