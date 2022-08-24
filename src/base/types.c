#include "../Autoarr/Autoarr.h"
#include "unitype.h"

Autoarr_declare(kerepTypeDescriptor)
Autoarr_define(kerepTypeDescriptor)

// type descriptors are stored here during initialization 
Autoarr(kerepTypeDescriptor)* __kerepTypeDescriptors=NULL;
// here type descriptors are stored when initialization is complited
kerepTypeDescriptor* typeDescriptors=NULL;
kerepTypeId kerepTypeId_last=-1;

typedef enum{
    NotInitialized, Initializing, Initialized
} kerepTypeDescriptorsState;
kerepTypeDescriptorsState initState=NotInitialized;

void kerepTypeDescriptors_beginInit(){
    __kerepTypeDescriptors=Autoarr_create(kerepTypeDescriptor, 256, 256);
    if(__kerepTypeDescriptors==NULL) throw(ERR_NULLPTR);
}

void kerepTypeDescriptors_endInit(){
    typeDescriptors=Autoarr_toArray(__kerepTypeDescriptors);
    Autoarr_free(__kerepTypeDescriptors);
    if(typeDescriptors==NULL) throw(ERR_NULLPTR);
}
void __kerepType_register(char* name, int16 size, void (*free_members)(void*)){
    kerepTypeDescriptor typeDesc={
        .name=name,
        .size=size,
        .free_members=free_members,
        .id=++kerepTypeId_last
    };
    Autoarr_add(__kerepTypeDescriptors, typeDesc);
}

kerepTypeDescriptor typeDescriptor_get(kerepTypeId id){
    return typeDescriptors[id];
}
