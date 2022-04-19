#include "tests.h"
#include "../String/string.h"

void test_string(){
    optime(__func__,1,({
        printf("\e[96m-------------[test_string]-------------\n");
        char c[]="0123456789abcdef";
        string s=string_cpFromCharPtr(c);
        printf("\e[92m\"%s\" \e[94m-> string_cpFromCharPtr()\n",c);
        if(s.length!=16) throw("string created with incorrect length");
        char* p=string_cpToCptr(s);
        printf("\e[94mstring_cpToCptr() -> \e[92m\"%s\"\n",p);
        free(p);
        free(s.ptr);
    }));
}