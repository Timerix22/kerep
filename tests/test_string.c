#include "tests.h"
#include "../src/String/string.h"

void test_string(){
    optime(__func__,1,({
        printf("\e[96m-------------[test_string]-------------\n");
        char c[]="0123456789abcdef";
        string s={.ptr=c, .length=cptr_length(c)};
        if(s.length!=sizeof(c)-1) throw("string created with incorrect length");
        char* p=string_extract(s);
        printf("\e[94mstring_extract() -> \e[92m\"%s\"\n",p);
        free(p);
    }));
}