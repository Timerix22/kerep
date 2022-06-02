//
//
//

#pragma once

#include "../base/base.h"

template <typename T>
class Autoarr2 {
public:
    T** values;
    uint16 blocks_count;
    uint16 block_length;
    uint16 max_block_length;
    uint32 length;
    Autoarr2();
    explicit Autoarr2(uint16 _max_block_length);
    T* getptr(uint32 index);
    T get(uint32 index);
    void set(uint32 index, T value);
    void add(T value);
    virtual ~Autoarr2();
};
