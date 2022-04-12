#include "tests.h"
#include "../StringFragment/StringFragment.h"

void test_string(){
    optime(__func__,1,({
        printf("\e[96m-------------[test_string]-------------\n");
        char c[]="0123456789abcdef";

        StringFragment s={.ptr=cptr_copy(c),.offset=0,.length=cptr_length(c)};
        printf("\e[92m\"%s\" \e[94m-> StringFragment\n",c);
        if(s.length!=16) throw("StringFragment created with incorrect length");

        StringFragment extr=StringFragment_extract(s);
        printf("\e[94mStringFragment_extract() -> \e[92m\"%s\"\n",extr.ptr);
        if(extr.length!=16) throw("StringFragment extracted with incorrect length");
        free(extr.ptr);

        s.offset+=2; s.length-=4;
        printf("\e[94mStringFragment offset+=2 length-=4\n");
        extr=StringFragment_extract(s);
        printf("\e[94mStringFragment_extract() ->   \e[92m\"%s\"\n",extr.ptr);
        if(extr.length!=12) throw("StringFragment extracted with incorrect length");
        free(s.ptr);
        free(extr.ptr);
    }));
}