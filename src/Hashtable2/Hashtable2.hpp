#pragma once

#include "../Hashtable/hash.h"
#include "../Autoarr2/Autoarr2.hpp"

template <typename TKey, typename TVal>
class Hashtable2{
    uint8 hein;
public:
    Autoarr2<TKey>* keys;
    Autoarr2<TVal>* values;

    Hashtable2();
    TVal get(TKey key);
    TVal getptr(TKey key);
    bool addOrSet(TKey key, TVal);
    bool remove(TKey);
    virtual ~Hashtable2();
};


// amount of rows
static const uint16 HT_HEIGHTS[]={17,61,257,1021,4099,16381,65521};
#define HT_HEIN_MIN 0
#define HT_HEIN_MAX 6

#define ARR_BC 2
#define ARR_BL 8

template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::Hashtable2() {
    hein=HT_HEIN_MIN;
    keys=new Autoarr2<TKey>;
    values=new Autoarr2<TVal>;
}

template<typename TKey, typename TVal>
TVal Hashtable2<TKey, TVal>::get(TKey key) {
    
}

template<typename TKey, typename TVal>
TVal Hashtable2<TKey, TVal>::getptr(TKey key) {

}

template<typename TKey, typename TVal>
bool Hashtable2<TKey, TVal>::addOrSet(TKey key, TVal) {

}

template<typename TKey, typename TVal>
bool Hashtable2<TKey, TVal>::remove(TKey) {

}

template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::~Hashtable2() {

}
