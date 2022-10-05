#include "tests.h"
#include "../src/Autoarr/Autoarr.h"
#include <vector>

int64 _autoarrVsVector(uint16 blockCount, uint16 blockLength){
    uint32 count=blockLength*blockCount;
    printf("\e[94mblock count: %u block length: %u count: %llu\n", blockCount, blockLength, (uint64)count);
    Autoarr_int64* ar=Autoarr_create(int64, blockCount, blockLength);
    std::vector<int64> vec=std::vector<int64>();
    optime("Autoarr_add", 1, ({
        for(uint32 i=0; i< count; i++)
            Autoarr_add(ar, i);
    }));
    optime("vector_push_back", 1, ({
        for(uint32 i=0; i< count; i++)
            vec.push_back(i);
    }));
    int64 t;
    optime("Autoarr_get", 1, ({
        for(uint32 i=0; i< count; i++)
            t=Autoarr_get(ar, i);
    }));
    optime("vector_get", 1, ({
        for(uint32 i=0; i< count; i++)
            t=vec[i];
    }));
    Autoarr_free(ar, true);
    return t;
}

void test_autoarrVsVector(){
    printf("\e[96m-------[test_autoarr_vs_vector]-------\n");
    _autoarrVsVector(4, 16);
    _autoarrVsVector(16, 64);
    _autoarrVsVector(32, 32);
    _autoarrVsVector(64, 64);
    _autoarrVsVector(32, 1024);
    _autoarrVsVector(256, 256);
    _autoarrVsVector(1024, 1024);
}
