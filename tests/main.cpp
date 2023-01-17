#include "tests.h"

int main(){
    if(!setlocale(LC_ALL, "C.UTF8"))
        kprintf("\e[93msetlocale failed\n");
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_endInit();
    kprintf("\e[97mkerep tests are starting!\n");
    optime("test_all",1,test_all());
    ktDescriptors_free();
    kprintf("\e[0m\n");
    return 0;
}
