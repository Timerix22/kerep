#pragma once

#if __cplusplus
extern "C" {
#endif

#include "ktid.h"

typedef struct Unitype{
    union {
        i64 Int64;
        u64 UInt64;
        f64 Float64;
        bool Bool;
        void* VoidPtr;
        char Bytes[8];
    };
    ktid typeId;
    bool allocatedInHeap; // should Unitype_free call free() to VoidPtr*
} Unitype;
ktid_declare(Unitype);


#define __UniDef(FIELD, TYPE, VAL) (Unitype){\
    .FIELD=VAL, .typeId=ktid_name(TYPE), .allocatedInHeap=false}

#define UniInt64(VAL)   __UniDef(Int64,   i64,   VAL)
#define UniUInt64(VAL)  __UniDef(UInt64,  u64,  VAL)
#define UniFloat64(VAL) __UniDef(Float64, f64, VAL)
#define UniBool(VAL)    __UniDef(Bool,    bool,    VAL)

#define UniStackPtr(TYPE, VAL) (Unitype){\
    .VoidPtr=VAL, .typeId=ktid_ptrName(TYPE), .allocatedInHeap=false}
#define UniHeapPtr(TYPE, VAL) (Unitype){\
    .VoidPtr=VAL, .typeId=ktid_ptrName(TYPE), .allocatedInHeap=true}

#define UniNull  (Unitype){.Int64=0, .typeId=ktid_Null, .allocatedInHeap=false}
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