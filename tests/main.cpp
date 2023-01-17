#include "tests.h"

void test_all(){
    test_string();
    test_safethrow();
    test_searchtree();
    test_autoarr();
    test_autoarrVsVector();
    test_hash_functions();
    test_hashtable();
    test_dtsod();
    test_rng_algorithms();
    test_kprint_colors();
    kprintf("\e[96m--------------------------------------\e[0m\n");
}
int main(){
    if(!setlocale(LC_ALL, "C.UTF8"))
        kprintf("\e[93msetlocale failed\n");
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_endInit();
    for(ktid id=0; id<ktid_last; id++){
        ktDescriptor d=ktDescriptor_get(id);
        kprintf("{ id:%u name:%s size:%u freeMembers:%p toString:%p }\n",
                    d.id, d.name, d.size, d.freeMembers, d.toString);
    }
    kprintf("\e[97mkerep tests are starting!\n");
    optime("test_all",1,test_all());
    ktDescriptors_free();
    kprintf("\e[0m\n");
    return 0;
}
