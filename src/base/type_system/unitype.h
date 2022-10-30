#pragma once

#if __cplusplus
extern "C" {
#endif

#include "ktId.h"

typedef struct Unitype{
    union {
        int64 Int64;
        uint64 UInt64;
        double Float64;
        bool Bool;
        void* VoidPtr;
        char Bytes[8];
    };
    ktId typeId;
    bool allocatedInHeap; // should Unitype_free call free() to VoidPtr*
} Unitype;
ktId_declare(Unitype);
ktId_declare(UnitypePtr);


#define __UniDef(TYPE, VAL) (Unitype){\
    .TYPE=VAL, .typeId=ktId_##TYPE, .allocatedInHeap=false}

#define UniInt64(VAL)   __UniDef(Int64,   VAL)
#define UniUInt64(VAL)  __UniDef(UInt64,  VAL)
#define UniFloat64(VAL) __UniDef(Float64, VAL)
#define UniBool(VAL)    __UniDef(Bool,    VAL)

#define UniStack(ID_VAR_NAME, VAL) (Unitype){\
    .VoidPtr=VAL, .typeId=ID_VAR_NAME, .allocatedInHeap=false}
#define UniHeap(ID_VAR_NAME, VAL) (Unitype){\
    .VoidPtr=VAL, .typeId=ID_VAR_NAME, .allocatedInHeap=true}

#define UniNull  UniStack(ktId_Null, NULL)
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