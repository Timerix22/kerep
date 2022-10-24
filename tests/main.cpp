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
    printf("\e[96m--------------------------------------\e[0m\n");
}
int main(){
    setlocale(LC_ALL, "en-US.Unicode");
    ktDescriptors_beginInit();
    ktDescriptors_initKerepTypes();
    ktDescriptors_endInit();
    printf("\e[97mkerep tests are starting!\n");
    // optime("test_all",1,test_all());
    test_rng_algorithms();
    test_kprint_colors();
    ktDescriptors_free();
    printf("\e[0m\n");
    return 0;
}
