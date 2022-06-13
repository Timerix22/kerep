#pragma once

#include "../HashFunctions/hash.h"
#include "../Autoarr2/Autoarr2.hpp"

// amount of rows
typedef uint16 HT_HEIGHT_T;
typedef uint32 HT_HASH_T;
#define HT_HASH(K) hashb_sdbm32(K, sizeof(K))

#define STORE_HASHES 1

static const HT_HEIGHT_T HT_HEIGHTS[]={17,61,257,1021,4099,16381,65521};
#define _HT_HEIN_MIN 0
#define _HT_HEIN_MAX 6

#define _HT_ARR_BC 2
#define _HT_ARR_BL 8


template<typename TKey, typename TVal>
class Hashtable2{
    using cmp_func_t=bool (*)(TKey, TKey);

#if STORE_HASHES
    Autoarr2<HT_HASH_T>** hashes;
    
#endif
    cmp_func_t keyComparFunc;
    Autoarr2<TKey>** keys;
    Autoarr2<TVal>** values;
    uint8 hein;
    HT_HEIGHT_T _height;
    void expand();
    bool uint32_compare(uint32& a, uint32& b) { return a==b; }
#if STORE_HASHES
public:
#endif
    Hashtable2();
#if !STORE_HASHES
public:
    explicit Hashtable2(cmp_func_t _keyComparFunc);
#endif

    virtual ~Hashtable2();
    inline HT_HEIGHT_T height(){ return _height; }
    TVal* getptr(TKey key);
    TVal get(TKey key);
    bool addOrSet(TKey key, TVal);
    bool remove(TKey);
};


template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::Hashtable2(){
    hein=_HT_HEIN_MIN;
    _height=HT_HEIGHTS[hein];
#if STORE_HASHES
    hashes=new Autoarr2<HT_HASH_T>*[_height];
#endif
    keys=new Autoarr2<TKey>*[_height];
    values=new Autoarr2<TVal>*[_height];
    for(HT_HEIGHT_T i=0; i<_height; i++){
#if STORE_HASHES
        hashes[i]=new Autoarr2<HT_HASH_T>(_HT_ARR_BL);
        keyComparFunc=NULL;
#endif
        keys[i]=new Autoarr2<TKey>(_HT_ARR_BL);
        values[i]=new Autoarr2<TVal>(_HT_ARR_BL);
    }
}

#if !STORE_HASHES
template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::Hashtable2(cmp_func_t _keyComparFunc) : Hashtable2() {
    keyComparFunc=_keyComparFunc;
}
#endif


template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::~Hashtable2(){
    for(uint32 i=0; i< _height; i++){
        delete keys[i];
        delete values[i];
#if STORE_HASHES
        delete hashes[i];
#endif
    }

    delete keys;
    delete values;
#if STORE_HASHES
    delete hashes;
#endif
}


template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::expand(){
    if(hein>=_HT_HEIN_MAX) 
        throw_id(ERR_MAXLENGTH);
    uint32 newHeight=HT_HEIGHTS[++hein];
    Autoarr2<TKey>** newKeys=new Autoarr2<TKey>*[newHeight];
    Autoarr2<TVal>** newValues=new Autoarr2<TVal>*[newHeight];
#if STORE_HASHES
    Autoarr2<HT_HASH_T>** newHashes=new Autoarr2<HT_HASH_T>*[newHeight];
#endif

    for(HT_HEIGHT_T i=0; i<newHeight; i++){
        newKeys[i]=new Autoarr2<TKey>(_HT_ARR_BL);
        newValues[i]=new Autoarr2<TVal>(_HT_ARR_BL);
#if STORE_HASHES
        newHashes[i]=new Autoarr2<HT_HASH_T>(_HT_ARR_BL);
#endif
    }

    for(HT_HEIGHT_T rowN=0; rowN<_height; rowN++){
        Autoarr2<TKey>* oldKeysRow=keys[rowN];
        Autoarr2<TVal>* oldValuesRow=values[rowN];
#if STORE_HASHES
        Autoarr2<HT_HASH_T>* oldHashesRow=hashes[rowN];
#endif

        for(uint32 k=0; k < oldKeysRow->length; k++){
            TKey currentKey=oldKeysRow->get(k);
#if STORE_HASHES
            HT_HASH_T currentHash=oldHashesRow->get(k);
#else 
            HT_HASH_T currentHash=HT_HASH(currentKey);
#endif
            HT_HEIGHT_T newRowN=currentHash%newHeight;
#if STORE_HASHES
            newHashes[newRowN]->add(currentHash);
#endif
            newKeys[newRowN]->add(currentKey);
            newValues[newRowN]->add(values[rowN]->get(k));
        }
    }

    ~Hashtable2();
    _height=newHeight;
    keys=newKeys;
    values=newValues;
#if STORE_HASHES
    hashes=newHashes;
#endif
}


template<typename TKey, typename TVal>
TVal* Hashtable2<TKey, TVal>::getptr(TKey key){
    HT_HASH_T keyHash=HT_HASH(key);
    HT_HEIGHT_T rowN=keyHash%_height;
#if STORE_HASHES
    uint32 index=hashes[rowN]->search(keyHash, uint32_compare);
#else
    uint32 index=keys[rowN]->search(key, keyComparFunc);
#endif
    if(index==Autoarr2_NO_REZULT) 
        return NULL;
    return values[rowN]->getptr(index);
}


template<typename TKey, typename TVal>
TVal Hashtable2<TKey, TVal>::get(TKey key){
    
}


template<typename TKey, typename TVal>
bool Hashtable2<TKey, TVal>::addOrSet(TKey key, TVal){
    //expand
}


template<typename TKey, typename TVal>
bool Hashtable2<TKey, TVal>::remove(TKey){

}
