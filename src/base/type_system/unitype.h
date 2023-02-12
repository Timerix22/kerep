#pragma once

#if __cplusplus
extern "C" {
#endif

#include "ktid.h"
#include "typedef_macros.h"

STRUCT(Unitype,
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
)


#define __UniDef(FIELD, TYPE, VAL) (Unitype){ \
    .FIELD=VAL, .typeId=ktid_name(TYPE), .allocatedInHeap=false}

#define UniInt64(VAL)   __UniDef(Int64,   i64,   VAL)
#define UniUInt64(VAL)  __UniDef(UInt64,  u64,  VAL)
#define UniFloat64(VAL) __UniDef(Float64, f64, VAL)
#define UniBool(VAL)    __UniDef(Bool,    bool,    VAL)

#define UniStackPtr(TYPE, VAL) (Unitype){ \
    .VoidPtr=VAL, .typeId=ktid_ptrName(TYPE), .allocatedInHeap=false}
#define UniHeapPtr(TYPE, VAL) (Unitype){ \
    .VoidPtr=VAL, .typeId=ktid_ptrName(TYPE), .allocatedInHeap=true}

                                    // 0==ktid_Pointer
#define UniNull  (Unitype){.Int64=0, .typeId=0, .allocatedInHeap=false}
#define UniTrue  UniBool(true)
#define UniFalse UniBool(false)

#define Unitype_isUniNull(UNI) (UNI.typeId==ktid_Pointer && UNI.VoidPtr==NULL)

// frees VoidPtr value or does nothing if type isn't pointer
void Unitype_free(Unitype u);
void __UnitypePtr_free(void* u);
char* Unitype_toString(Unitype v, u32 fmt);
void printuni(Unitype v);

#if __cplusplus
}
#endif