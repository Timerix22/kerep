#include "../../Autoarr/Autoarr.h"
#include "type_system.h"
#include "base_toString.h"

kt_define(Pointer, NULL, __toString_u64);
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


char* ktDescriptor_toString(allocator_ptr al, ktDescriptor* d){
    const char* n="null";
    char *s0 = toString_u64(al, d->id, 0,0);
    char *s1 = toString_u64(al, d->size, 0,0);
    char *s2 = d->toString ? toString_hex(al, d->toString, sizeof(void*), 0,1,0) : n;
    char *s3 = d->destruct ? toString_hex(al, d->destruct, sizeof(void*), 0,1,0) : n;
    char *rez=cptr_concat(al, "ktDescriptor {"
        " name:", d->name,
        " id:",s0,
        " size:",s1,
        " toString:",s2,
        " destruct:",s3,
        " }");
    if(s3!=n) allocator_free(al, s3);
    if(s2!=n) allocator_free(al, s2);
    allocator_free(al, s1);
    allocator_free(al, s0);
    return rez;
}

char* _ktDescriptor_toString(allocator_ptr al, void* _d, u32 fmt) { return ktDescriptor_toString(al, _d); }

kt_define(ktDescriptor, NULL, _ktDescriptor_toString);

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

void kt_beginInit(){
    kprintf("\e[94mtype descriptors initializing...\n");
    Autoarr_construct(__descriptorPointers, Pointer, 256, NULL);
}

void kt_endInit(){
    if(__descriptorPointers==NULL)
        throw(ERR_NULLPTR);
    typeDescriptors=(ktDescriptor**)Autoarr_toArray(__descriptorPointers, CstdAllocator_instPtr);
    Autoarr_destruct(__descriptorPointers);
    if(typeDescriptors==NULL)
        throw(ERR_NULLPTR);
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

void kt_deinit(){
    free(typeDescriptors);
}
