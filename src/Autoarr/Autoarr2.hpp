#pragma once

#include "../base/base.h"


template <typename T>
class Autoarr2 {
    T** values;
    uint16 blocks_count;
    uint16 block_length;
    uint16 max_block_length;
public:
    uint32 Length;
    Autoarr2();
    explicit Autoarr2(uint16 _max_block_length);
    T* GetPtr(uint32 index);
    T Get(uint32 index);
    void Set(uint32 index, T value);
    void Add(T value);
    ~Autoarr2();
};
