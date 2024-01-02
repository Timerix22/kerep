#include "tests.h"

i32 main(){
    if(setlocale(LC_CTYPE, "C.UTF-8")!=0)
        kprintf("\e[93msetlocale failed\n");
    kt_beginInit();
    kt_initKerepTypes();
    kt_endInit();
    // test_all();
    test_network();
    kt_free();
    kprintf("\e[37m\n");
    return 0;
}
