#include "tests.h"
#include "../src/Autoarr/Autoarr.h"
#include <vector>

i64 _autoarrVsVector(u32 count){
    kprintf("\e[94mcount: %u\n", count);
    Autoarr_i64 _ar;
    Autoarr_i64* ar=&_ar;
    Autoarr_construct(ar, i64, count, NULL);
    std::vector<i64> vec=std::vector<i64>();
    optime("Autoarr_add", count,
        Autoarr_add(ar, op_i));
    optime("vector_push_back", count, 
        vec.push_back(op_i));
    i64 t=0;
    optime("Autoarr_get", count,
        t=Autoarr_get(ar, op_i));
    optime("vector_get", count,
        t=vec[op_i]);
    Autoarr_destruct(ar);
    return t;
}

void test_autoarrVsVector(){
    optime(__func__, 1, 
        kprintf("\e[96m-------[test_autoarr_vs_vector]-------\n");
        _autoarrVsVector(1);
        _autoarrVsVector(4);
        _autoarrVsVector(16);
        _autoarrVsVector(64);
        _autoarrVsVector(256);
        _autoarrVsVector(1024);
        _autoarrVsVector(4096);
        _autoarrVsVector(16384);
        _autoarrVsVector(65536);
        _autoarrVsVector(524288);
    );
}
