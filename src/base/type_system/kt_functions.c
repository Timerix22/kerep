#include "../../Autoarr/Autoarr.h"

Autoarr_declare(ktDescriptor)
Autoarr_define(ktDescriptor)

ktId_define(ktId_Null);

ktId_define(ktId_Char);
ktId_define(ktId_Bool);
ktId_define(ktId_Float32);
ktId_define(ktId_Float64);
ktId_define(ktId_Int8);
ktId_define(ktId_UInt8);
ktId_define(ktId_Int16);
ktId_define(ktId_UInt16);
ktId_define(ktId_Int32);
ktId_define(ktId_UInt32);
ktId_define(ktId_Int64);
ktId_define(ktId_UInt64);

ktId_define(ktId_CharPtr);
ktId_define(ktId_BoolPtr);
ktId_define(ktId_Float32Ptr);
ktId_define(ktId_Float64Ptr);
ktId_define(ktId_Int8Ptr);
ktId_define(ktId_UInt8Ptr);
ktId_define(ktId_Int16Ptr);
ktId_define(ktId_UInt16Ptr);
ktId_define(ktId_Int32Ptr);
ktId_define(ktId_UInt32Ptr);
ktId_define(ktId_Int64Ptr);
ktId_define(ktId_UInt64Ptr);

ktId_define(ktId_ktDescriptor);
ktId_define(ktId_ktDescriptorPtr);

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
    printf("\e[94mtype descriptors initializing...\n");
    __ktDescriptors=Autoarr_create(ktDescriptor, 256, 256);
    if(__ktDescriptors==NULL) throw(ERR_NULLPTR);
}

void ktDescriptors_endInit(){
    typeDescriptors=Autoarr_toArray(__ktDescriptors);
    Autoarr_free(__ktDescriptors,true);
    if(typeDescriptors==NULL) throw(ERR_NULLPTR);
    printf("\e[92minitialized %u type descriptors\n", ktId_last);
}

void __kt_register(char* name, int16 size, void (*freeMembers)(void*), Maybe (*toString)(void*, int32)){
    ktDescriptor typeDesc={
        .name=name,
        .size=size,
        .id=++ktId_last,
        .freeMembers=freeMembers,
        .toString=toString
    };
    Autoarr_add(__ktDescriptors, typeDesc);
}

Maybe ktDescriptor_get(ktId id){
    if(id>ktId_last) safethrow("invalid type id",;);
    return SUCCESS(UniStack(ktId_ktDescriptorPtr, &typeDescriptors[id]));
}
