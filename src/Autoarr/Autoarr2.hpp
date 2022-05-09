#pragma once

#include "../base/base.h"

template <typename T>
class Autoarr2 {
    uint16 blocks_count;
    uint16 block_length;

    T** values;
public:
    Autoarr2();
    uint32 Length();
    T Get(uint32 index);
    T* GetPtr(uint32 index);
    void Set(uint32 index, T value);
    void Add(T value);
    ~Autoarr2();
};
