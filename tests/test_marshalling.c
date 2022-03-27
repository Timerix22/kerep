#include "../Hashtable/KeyValuePair.h"

EXPORT void CALL test_marshalling(char* text, KeyValuePair** kptr){
    KeyValuePair* k=malloc(sizeof(KeyValuePair));
    k->key="message";
    char* tc=cptr_copy(text);
    Unitype u={.VoidPtr=tc, .type=CharPtr};
    k->value=u;
    *kptr=k;
}

EXPORT void CALL pinvoke_print(char* msg) {
    printf("printed from unmanaged code: %s\n", msg);
}
