#include "../../Autoarr/Autoarr.h"
#include "type_system.h"
#include "base_toString.h"

kt_define(Pointer, free, __toString_u64);
kt_define(char,NULL, __toString_char);
kt_define(bool,NULL, __toString_bool);
kt_define(f32, NULL, __toString_f32);
kt_define(f64, NULL, __toString_f64);
kt_define(i8,  NULL, __toString_i8);
kt_define(u8,  NULL, __toString_u8);
kt_define(i16, NULL, __toString_i16);
kt_define(u16, NULL, __toString_u16);
kt_define(i32, NULL, __toString_i32);
kt_define(u32, NULL, __toString_u32);
kt_define(i64, NULL, __toString_i64);
kt_define(u64, NULL, __toString_u64);

kt_define(ktDescriptor, NULL, NULL);

typedef ktDescriptor* ktDescriptor_Ptr;

// type descriptors are stored here during initialization 
Autoarr(Pointer)* __descriptorPointers=NULL;
// here type descriptors are stored when initialization is complited
ktDescriptor** typeDescriptors=NULL;
ktid ktid_last=-1;

ENUM(ktDescriptorsState,
    NotInitialized, Initializing, Initialized
)
ktDescriptorsState initState=NotInitialized;

void ktDescriptors_beginInit(){
    kprintf("\e[94mtype descriptors initializing...\n");
    __descriptorPointers=Autoarr_create(Pointer, 256, 256);
    if(__descriptorPointers==NULL)
        throw(ERR_NULLPTR);
}

void ktDescriptors_endInit(){
    typeDescriptors=(ktDescriptor**)Autoarr_toArray(__descriptorPointers);
    Autoarr_free(__descriptorPointers,true);
    if(typeDescriptors==NULL) throw(ERR_NULLPTR);
    kprintf("\e[92minitialized %u type descriptors\n", ktid_last);
}

void __kt_register(ktDescriptor* descriptor){
    descriptor->id=++ktid_last;
    Autoarr_add(__descriptorPointers, descriptor);
}

ktDescriptor* ktDescriptor_get(ktid id){
    if(id>ktid_last || id==ktid_undefined) {
        kprintf("\ntype id: %u\n",id);
        throw("invalid type id");
    }
    return typeDescriptors[id];
}

void ktDescriptors_free(){
    free(typeDescriptors);
}
