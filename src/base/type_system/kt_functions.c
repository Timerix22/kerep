#include "../../Autoarr/Autoarr.h"

Autoarr_declare(ktDescriptor)
Autoarr_define(ktDescriptor)

ktid ktid_Null=-1;

ktid_define(char);
ktid_define(bool);
ktid_define(f32);
ktid_define(f64);
ktid_define(i8);
ktid_define(u8);
ktid_define(i16);
ktid_define(u16);
ktid_define(i32);
ktid_define(u32);
ktid_define(i64);
ktid_define(u64);

ktid_define(ktDescriptor);

// type descriptors are stored here during initialization 
Autoarr(ktDescriptor)* __ktDescriptors=NULL;
// here type descriptors are stored when initialization is complited
ktDescriptor* typeDescriptors=NULL;
ktid ktid_last=-1;

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
    kprintf("\e[92minitialized %u type descriptors\n", ktid_last);
}

void __kt_register(char* name, i16 size, void (*freeMembers)(void*), char* (*toString)(void*, u32)){
    ktDescriptor typeDesc={
        .name=name,
        .size=size,
        .id=++ktid_last,
        .freeMembers=freeMembers,
        .toString=toString
    };
    Autoarr_add(__ktDescriptors, typeDesc);
}

ktDescriptor ktDescriptor_get(ktid id){
    if(id>ktid_last) {
        kprintf("\ntype id: %u\n",id);
        throw("invalid type id");
    }
    return typeDescriptors[id];
}

void ktDescriptors_free(){
    free(typeDescriptors);
}
