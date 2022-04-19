#include "tests.h"

#include "../Hashtable/KeyValuePair.h"

void test_all(){
    /* test_autoarr();
    test_string();
    test_safethrow();
    test_searchtree(); */
    test_hashtable();
    //test_dtsod();
    printf("\e[96m---------------------------------------\e[0m\n");
    printf("Unitype: %lu  KVPair: %lu\n", sizeof(Unitype),sizeof(KVPair));
}

int main(){
    setlocale(LC_ALL, "en-US.Unicode");
    printf("\e[92mdtsod parser in c language!\e[97m\n");
    optime("test_all",1,test_all());
    printf("\e[0m\n");
    return 0;
}
