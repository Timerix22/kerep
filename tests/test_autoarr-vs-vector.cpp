#include "tests.h"
#include "../src/Autoarr/Autoarr.h"
#include <vector>

int64 _autoarrVsVector(uint16 blockCount, uint16 blockLength){
    uint32 count=blockLength*blockCount;
    kprintf("\e[94mblock count: %u block length: %u count: " IFWIN("%llu", "%lu") "\n", blockCount, blockLength, (uint64)count);
    Autoarr_int64* ar=Autoarr_create(int64, blockCount, blockLength);
    std::vector<int64> vec=std::vector<int64>();
    optime("Autoarr_add", count,
        Autoarr_add(ar, op_i));
    optime("vector_push_back", count, 
        vec.push_back(op_i));
    int64 t=0;
    optime("Autoarr_get", count,
        t=Autoarr_get(ar, op_i));
    optime("vector_get", count,
        t=vec[op_i]);
    Autoarr_free(ar, true);
    return t;
}

void test_autoarrVsVector(){
    optime(__func__, 1, ({
        kprintf("\e[96m-------[test_autoarr_vs_vector]-------\n");
        _autoarrVsVector(4, 16);
        _autoarrVsVector(16, 64);
        _autoarrVsVector(32, 32);
        _autoarrVsVector(64, 64);
        _autoarrVsVector(32, 1024);
        _autoarrVsVector(256, 256);
        _autoarrVsVector(1024, 1024);
    }));
}
