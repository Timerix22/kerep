#include "../../Autoarr/Autoarr.h"

Autoarr_declare(ktDescriptor)
Autoarr_define(ktDescriptor)

ktId_define(Null);

ktId_define(Char);
ktId_define(Bool);
ktId_define(Float32);
ktId_define(Float64);
ktId_define(Int8);
ktId_define(UInt8);
ktId_define(Int16);
ktId_define(UInt16);
ktId_define(Int32);
ktId_define(UInt32);
ktId_define(Int64);
ktId_define(UInt64);

ktId_define(CharPtr);
ktId_define(BoolPtr);
ktId_define(Float32Ptr);
ktId_define(Float64Ptr);
ktId_define(Int8Ptr);
ktId_define(UInt8Ptr);
ktId_define(Int16Ptr);
ktId_define(UInt16Ptr);
ktId_define(Int32Ptr);
ktId_define(UInt32Ptr);
ktId_define(Int64Ptr);
ktId_define(UInt64Ptr);

ktId_define(ktDescriptor);
ktId_define(ktDescriptorPtr);

// type descriptors are stored here during initialization 
Autoarr(ktDescriptor)* __ktDescriptors=NULL;
// here type descriptors are stored when initialization is complited
ktDescriptor* typeDescriptors=NULL;
ktId ktId_last=-1;

typedef enum{
    NotInitialized, Initializing, Initialized
} ktDescriptorsState;
ktDescriptorsState initState=NotInitialized;

void ktDescriptors_beginInit(){
    kprintf("\e[94mtype descriptors initializing...\n");
    __ktDescriptors=Autoarr_create(ktDescriptor, 256, 256);
    if(__ktDescriptors==NULL) throw(ERR_NULLPTR);
}

void ktDescriptors_endInit(){
    typeDescriptors=Autoarr_toArray(__ktDescriptors);
    Autoarr_free(__ktDescriptors,true);
    if(typeDescriptors==NULL) throw(ERR_NULLPTR);
    kprintf("\e[92minitialized %u type descriptors\n", ktId_last);
}

void __kt_register(char* name, int16 size, void (*freeMembers)(void*), char* (*toString)(void*, uint32)){
    ktDescriptor typeDesc={
        .name=name,
        .size=size,
        .id=++ktId_last,
        .freeMembers=freeMembers,
        .toString=toString
    };
    Autoarr_add(__ktDescriptors, typeDesc);
}

ktDescriptor ktDescriptor_get(ktId id){
    if(id>ktId_last) {
        kprintf("\ntype id: %u\n",id);
        throw("invalid type id");
    }
    return typeDescriptors[id];
}

void ktDescriptors_free(){
    free(typeDescriptors);
}
