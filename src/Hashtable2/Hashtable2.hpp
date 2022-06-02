#pragma once

#include "../Hashtable/hash.h"
#include "../Autoarr2/Autoarr2.hpp"

template <typename TKey, typename TValue>
class Hashtable2{
    uint8 hein;
public:
    Autoarr2<TKey>* keys;
    Autoarr2<TValue>* values;

    Hashtable2();
    TValue get(TKey key);
    TValue getptr(TKey key);
    bool addOrSet(TKey key, TValue);
    bool remove(TKey);
    virtual ~Hashtable2();
};
