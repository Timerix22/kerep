#include "../../Autoarr/Autoarr.h"
#include "types.h"

Autoarr_declare(kerepTypeDescriptor)
Autoarr_define(kerepTypeDescriptor)

kerepTypeId_define(kerepTypeId_Null);

kerepTypeId_define(kerepTypeId_Char);
kerepTypeId_define(kerepTypeId_Bool);
kerepTypeId_define(kerepTypeId_Float32);
kerepTypeId_define(kerepTypeId_Float64);
kerepTypeId_define(kerepTypeId_Int8);
kerepTypeId_define(kerepTypeId_UInt8);
kerepTypeId_define(kerepTypeId_Int16);
kerepTypeId_define(kerepTypeId_UInt16);
kerepTypeId_define(kerepTypeId_Int32);
kerepTypeId_define(kerepTypeId_UInt32);
kerepTypeId_define(kerepTypeId_Int64);
kerepTypeId_define(kerepTypeId_UInt64);

kerepTypeId_define(kerepTypeId_CharPtr);
kerepTypeId_define(kerepTypeId_BoolPtr);
kerepTypeId_define(kerepTypeId_Float32Ptr);
kerepTypeId_define(kerepTypeId_Float64Ptr);
kerepTypeId_define(kerepTypeId_Int8Ptr);
kerepTypeId_define(kerepTypeId_UInt8Ptr);
kerepTypeId_define(kerepTypeId_Int16Ptr);
kerepTypeId_define(kerepTypeId_UInt16Ptr);
kerepTypeId_define(kerepTypeId_Int32Ptr);
kerepTypeId_define(kerepTypeId_UInt32Ptr);
kerepTypeId_define(kerepTypeId_Int64Ptr);
kerepTypeId_define(kerepTypeId_UInt64Ptr);

kerepTypeId_define(kerepTypeId_kerepTypeDescriptor);
kerepTypeId_define(kerepTypeId_kerepTypeDescriptorPtr);

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
    printf("\e[94mtype descriptors initializing...\n");
    __kerepTypeDescriptors=Autoarr_create(kerepTypeDescriptor, 256, 256);
    if(__kerepTypeDescriptors==NULL) throw(ERR_NULLPTR);
}

void kerepTypeDescriptors_endInit(){
    typeDescriptors=Autoarr_toArray(__kerepTypeDescriptors);
    Autoarr_free(__kerepTypeDescriptors,true);
    if(typeDescriptors==NULL) throw(ERR_NULLPTR);
    printf("\e[92minitialized %u type descriptors\n", kerepTypeId_last);
}

void __kerepType_register(char* name, int16 size, void (*freeMembers)(void*), Maybe (*toString)(void*, int32)){
    kerepTypeDescriptor typeDesc={
        .name=name,
        .size=size,
        .id=++kerepTypeId_last,
        .freeMembers=freeMembers,
        .toString=toString
    };
    Autoarr_add(__kerepTypeDescriptors, typeDesc);
}

Maybe kerepTypeDescriptor_get(kerepTypeId id){
    if(id>kerepTypeId_last) safethrow("invalid type id",;);
    return SUCCESS(UniStack(kerepTypeId_kerepTypeDescriptorPtr, &typeDescriptors[id]));
}
