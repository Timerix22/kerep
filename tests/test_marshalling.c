#include "../src/Hashtable/KeyValuePair.h"

EXPORT void CALL test_marshalling(char* text, KVPair** kptr){
    KVPair* k=malloc(sizeof(KVPair));
    k->key="message";
    char* tc=cptr_copy(text);
    Unitype u=UniPtrHeap(kerepTypeId_CharPtr,tc);
    k->value=u;
    *kptr=k;
}

EXPORT void CALL pinvoke_print(char* msg) {
    printf("printed from unmanaged code: %s\n", msg);
}
