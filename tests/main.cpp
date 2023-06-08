#include "tests.h"

i32 main(){
    if(setlocale(LC_CTYPE, "C.UTF-8")!=0)
        kprintf("\e[93msetlocale failed\n");
    kt_beginInit();
    kt_initKerepTypes();
    kt_endInit();
    test_all();
    kt_deinit();
    kprintf("\e[0m\n");
    return 0;
}
