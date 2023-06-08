#include "../src/Hashtable/KeyValuePair.h"

EXPORT void CALL test_marshalling(char* text, KVPair** kptr){
    CstdAllocator _al;
    allocator_ptr al=(allocator_ptr)&_al;
    CstdAllocator_construct(&_al);
    KVPair* k=allocator_alloc(al, sizeof(KVPair));
    k->key="message";
    char* tc=cptr_copy(al, text);
    Unitype u=UniHeapPtr(char,tc);
    k->value=u;
    *kptr=k;
}

EXPORT void CALL pinvoke_print(char* msg) {
    kprintf("printed from unmanaged code: %s\n", msg);
}
