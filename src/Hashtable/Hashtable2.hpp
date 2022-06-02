//
//
//

#pragma once

#include "hash.h"
#include "../Autoarr/Autoarr2.hpp"

template <typename TKey, typename TValue>
class Hashtable2{
    uint8 hein;
public:
    Autoarr2<TKey>* Keys;
    Autoarr2<TValue>* Values;

    Hashtable2();
    TValue Get(TKey key);
    TValue GetPtr(TKey key);
    bool AddOrSet(TKey key, TValue);
    bool Remove(TKey);
    ~Hashtable2();
};

