#include "tests.h"

Maybe dont_throw(){
    return SUCCESS(UniUInt64(9/2));
}

Maybe throw_error(){
    char* k=malloc(64);
    safethrow("test exception",free(k));
}

Maybe throw_errcode(){
    safethrow(ERR_NULLPTR,;);
}

Maybe test_maybe(){
    kprintf("\e[94mdont_throw returns \e[92m");
    tryLast(dont_throw(),rez0,;)
        printMaybe(rez0);
    kprintf("\n");
    try(throw_error(),rez1,;)
        printMaybe(rez1);
    throw("test_maybe failed");
}


Maybe c(){ try(throw_errcode(),_,;) return MaybeNull; }
Maybe b(){ try(c(),_,;) return MaybeNull; }
Maybe a(){ try(b(),_,;) return MaybeNull; }

void test_safethrow(){
    kprintf("\e[96m-----------[test_safethrow]-----------\n");
    optime("test_safethrow", 1, 
        Maybe e=test_maybe();
        kprintf("\e[94mthrow_error:\n\e[92m");
        printMaybe(e);
        Maybe_free(e);
        kprintf("\e[94mthrow_errcode:\n\e[92m");
        e=a();
        printMaybe(e);
        Maybe_free(e);
    );
}
