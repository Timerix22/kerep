#include "tests.h"

int main(){
    if(!setlocale(LC_ALL, "C.UTF8"))
        kprintf("\e[93msetlocale failed\n");
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_endInit();
    test_all();
    ktDescriptors_free();
    kprintf("\e[0m\n");
    return 0;
}
