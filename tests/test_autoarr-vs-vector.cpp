#include "tests.h"
#include "../src/Autoarr/Autoarr.h"
#include <vector>

i64 _autoarrVsVector(u16 chunkCount, u16 chunkLength){
    u32 count=chunkLength*chunkCount;
    kprintf("\e[94mchunk count: %u chunk length: %u count: " IFWIN("%llu", "%lu") "\n", chunkCount, chunkLength, (u64)count);
    Autoarr_i64* ar=Autoarr_create(i64, chunkCount, chunkLength);
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
    Autoarr_destruct(ar, true);
    return t;
}

void test_autoarrVsVector(){
    optime(__func__, 1, 
        kprintf("\e[96m-------[test_autoarr_vs_vector]-------\n");
        _autoarrVsVector(4, 16);
        _autoarrVsVector(16, 64);
        _autoarrVsVector(32, 32);
        _autoarrVsVector(64, 64);
        _autoarrVsVector(32, 1024);
        _autoarrVsVector(256, 256);
        _autoarrVsVector(1024, 1024);
    );
}
