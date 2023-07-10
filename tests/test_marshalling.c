#include "../src/Hashtable/KeyValuePair.h"

EXPORT void CALL test_marshalling(char* text, KVPair** kptr){
    KVPair* k=allocator_alloc(CstdAllocator_instPtr, sizeof(KVPair));
    k->key="message";
    char* tc=cptr_copy(CstdAllocator_instPtr, text);
    Unitype u=UniHeapPtr(char, tc);
    k->value=u;
    *kptr=k;
}

EXPORT void CALL pinvoke_print(char* msg) {
    kprintf("printed from unmanaged code: %s\n", msg);
}
