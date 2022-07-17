#pragma once

#include "../HashFunctions/hash.h"
#include "../Autoarr2/Autoarr2.hpp"

// amount of rows
typedef uint32 HT_HEIGHT_T;
typedef uint32 HT_HASH_T;

#define STORE_HASHES 0

static const HT_HEIGHT_T HT_HEIGHTS[]={17,61,257,1021,4099,16381,65521};
#define _HT_HEIN_MIN 0
#define _HT_HEIN_MAX 6

#define _HT_ARR_BC 2
#define _HT_ARR_BL 8


template<typename TKey, typename TVal>
class Hashtable2{
// internal types
    struct KeyValue{
        TKey key;
        TVal value;
#if STORE_HASHES
        HT_HASH_T hash;
#endif
    };
    using HashKeyFunc_t=HT_HASH_T (*)(TKey);
    using KeyCmpFunc_t=bool (*)(TKey, TKey);

// fields
    Autoarr2<KeyValue>** rows;

    HashKeyFunc_t hashKeyFunc;
#if !STORE_HASHES
    KeyCmpFunc_t keyComparFunc;
#endif
public:
    HT_HEIGHT_T height;
private:
    uint8 hein;

// constructors
#if STORE_HASHES
public:
#endif
    Hashtable2(HashKeyFunc_t _hashKeyFunc);
#if !STORE_HASHES
public:
    explicit Hashtable2(HashKeyFunc_t _hashKeyFunc, KeyCmpFunc_t _keyComparFunc);
#endif


// methods
private:
    void free_rows();
    TVal* getptr(TKey key, HT_HASH_T& keyHash,  HT_HEIGHT_T& rowN);
    void expand();
    void add(TKey& key, TVal& value, HT_HASH_T keyHash, HT_HEIGHT_T rowN);

public:
    virtual ~Hashtable2();
    TVal* getptr(TKey key);
    TVal get(TKey key);
    bool tryGet(TKey key, TVal* output);
    void add(TKey key, TVal value);
    void addOrSet(TKey key, TVal value);
    void remove(TKey key);
};


template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::Hashtable2(HashKeyFunc_t _hashKeyFunc){
    hashKeyFunc=_hashKeyFunc;
    hein=_HT_HEIN_MIN;
    height=HT_HEIGHTS[hein];
    rows=new Autoarr2<KeyValue>*[height];
    for(HT_HEIGHT_T i=0; i<height; i++)
        rows[i]=new Autoarr2<KeyValue>(_HT_ARR_BL);
}

#if !STORE_HASHES
template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::Hashtable2(HashKeyFunc_t _hashKeyFunc, KeyCmpFunc_t _keyComparFunc) : Hashtable2(_hashKeyFunc) {
    keyComparFunc=_keyComparFunc;
}
#endif



template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::free_rows(){
    for(uint32 i=0; i< height; i++)
        delete rows[i];
    delete[] rows;
}

template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::~Hashtable2() { free_rows(); }


template<typename TKey, typename TVal>
TVal* Hashtable2<TKey, TVal>::getptr(TKey key, HT_HASH_T& keyHash,  HT_HEIGHT_T& rowN){
    keyHash=hashKeyFunc(key);
    rowN=keyHash%height;
    KeyValue kv;
#if STORE_HASHES
    kv.hash=keyHash;
    uint32 index=rows[rowN]->search(kv, [](KeyValue kv0, KeyValue kv1) { return kv0.hash==kv1.hash; });
#else
    kv.key=key;
    uint32 index=rows[rowN]->search(kv, [this](KeyValue kv0, KeyValue kv1) { return this->keyComparFunc(kv0.key, kv1.key); });
#endif
    if(index==Autoarr2_NO_REZULT) 
        return NULL;
    return &(rows[rowN]->getptr(index))->value;
}

template<typename TKey, typename TVal>
TVal* Hashtable2<TKey, TVal>::getptr(TKey key){
    HT_HASH_T keyHash;
    HT_HEIGHT_T rowN;
    return getptr(key, keyHash, rowN);
}

template<typename TKey, typename TVal>
TVal Hashtable2<TKey, TVal>::get(TKey key){
    TVal* ptr=getptr(key);
    if(!ptr) 
        throw_id(ERR_KEYNOTFOUND);
    return *ptr;
}

template<typename TKey, typename TVal>
bool Hashtable2<TKey, TVal>::tryGet(TKey key, TVal* output){
    TVal* ptr=getptr(key);
    if(!ptr) 
        return false;
    *output=*ptr;
    return true;
}

template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::expand(){ 
    printf("expand\n"); fflush(stdout);
    if(hein>=_HT_HEIN_MAX) 
        throw_id(ERR_MAXLENGTH);

    uint32 newHeight=HT_HEIGHTS[++hein];
    Autoarr2<KeyValue>** newRows=new Autoarr2<KeyValue>*[newHeight];
    for(HT_HEIGHT_T i=0; i<newHeight; i++)
        newRows[i]=new Autoarr2<KeyValue>(_HT_ARR_BL);

    for(HT_HEIGHT_T oldRowN=0; oldRowN<height; oldRowN++)
        for(uint32 k=0; k < rows[oldRowN]->length; k++){
            KeyValue kv=rows[oldRowN]->get(k);
#if STORE_HASHES
            HT_HEIGHT_T newRowN=kv.hash%newHeight;
#else 
            HT_HEIGHT_T newRowN=hashKeyFunc(kv.key)%newHeight;
#endif
            newRows[newRowN]->add(kv);
        }

    free_rows();
    height=newHeight;
    rows=newRows;
}

template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::add(TKey& key, TVal& value, HT_HASH_T keyHash, HT_HEIGHT_T rowN){ 
    printf("add\n"); fflush(stdout);
    Autoarr2<KeyValue>* row=rows[rowN];
    if(row->length == _HT_ARR_BC*_HT_ARR_BL)
        expand();
    KeyValue kv;
    kv.key=key;
    kv.value=value;
#if STORE_HASHES
    kv.hash=keyHash;
#endif
    row->add(kv);
}

template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::add(TKey key, TVal value){
    HT_HASH_T keyHash=hashKeyFunc(key);
    HT_HEIGHT_T rowN=keyHash%height;
    add(key, value, keyHash, rowN);
}

template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::addOrSet(TKey key, TVal value){
    HT_HASH_T keyHash;
    HT_HEIGHT_T rowN;
    TVal* valptr=getptr(key, keyHash, rowN);
    if(valptr) *valptr=value;
    else add(key, value, keyHash, rowN);
}


template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::remove(TKey key){
    throw_id(ERR_NOTIMPLEMENTED);
}
