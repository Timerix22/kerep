#pragma once

#include "../Hashtable/hash.h"
#include "../Autoarr2/Autoarr2.hpp"

// amount of rows
typedef uint32 HT_HEIGHT_T;
typedef uint32 HT_HASH_T;
#define HT_HASH(K) hashb_sdbm32(K, sizeof(K))

static const HT_HEIGHT_T HT_HEIGHTS[]={17,61,257,1021,4099,16381,65521};
#define _HT_HEIN_MIN 0
#define _HT_HEIN_MAX 6

#define _HT_ARR_BC 2
#define _HT_ARR_BL 8


template <typename TKey, typename TVal>
class Hashtable2{
    Autoarr2<HT_HASH_T>* hashes;
    Autoarr2<TKey>* keys;
    Autoarr2<TVal>* values;
    uint8 hein;

    void expand();

public:
    Hashtable2();
    virtual ~Hashtable2();

    HT_HEIGHT_T height(){ return HT_HEIGHTS[hein]; }
    TVal* getptr(TKey key);
    TVal get(TKey key);
    bool addOrSet(TKey key, TVal);
    bool remove(TKey);
};


template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::Hashtable2(){
    hein=_HT_HEIN_MIN;
    HT_HEIGHT_T h=height();
    hashes=new Autoarr2<HT_HASH_T>[h];
    keys=new Autoarr2<TKey>[h];
    values=new Autoarr2<TVal>[h];
    for(HT_HEIGHT_T i=0; i<h; i++){
        hashes[i]=Autoarr2<HT_HASH_T>(_HT_ARR_BL);
        keys[i]=Autoarr2<TKey>(_HT_ARR_BL);
        values[i]=Autoarr2<TVal>(_HT_ARR_BL);
    }
}

template<typename TKey, typename TVal>
void Hashtable2<TKey, TVal>::expand(){
    if(hein>=_HT_HEIN_MAX) 
        throw_id(ERR_MAXLENGTH);
    if(hashes->length!=keys->length || hashes->length!=values->length)
        throw_id(ERR_DESYNC);

    uint32 oldHeight=height();
    hein++;
    uint32 newHeight=height();
    Autoarr2<HT_HASH_T>* newHashes=new Autoarr2<HT_HASH_T>[newHeight];
    Autoarr2<TKey>* newKeys=new Autoarr2<TKey>[newHeight];
    Autoarr2<TVal>* newValues=new Autoarr2<TVal>[newHeight];
    for(HT_HEIGHT_T i=0; i<newHeight; i++){
        newHashes[i]=Autoarr2<HT_HASH_T>(_HT_ARR_BL);
        newKeys[i]=Autoarr2<TKey>(_HT_ARR_BL);
        newValues[i]=Autoarr2<TVal>(_HT_ARR_BL);
    }

    for(HT_HEIGHT_T rowN=0; rowN<newHeight; rowN++){
        Autoarr2<HT_HASH_T>* oldHashesRow= hashes+rowN;
        Autoarr2<TKey>*      oldKeysRow  = keys  +rowN;
        Autoarr2<TVal>*      oldValuesRow= values+rowN;

        for(uint32 k=0; k < oldHashesRow->length; k++){
            HT_HASH_T currentHash=oldHashesRow->get(k);
            HT_HEIGHT_T newRowN=currentHash%oldHeight;

            Autoarr2<HT_HASH_T>* newHashesRow= newHashes+newRowN;
            Autoarr2<TKey>*      newKeysRow  = newKeys  +newRowN;
            Autoarr2<TVal>*      newValuesRow= newValues+newRowN;

            newHashesRow->add(currentHash);
            newKeysRow->add(oldKeysRow->get(k));
            newValuesRow->add(oldValuesRow->get(k));
        }
        //delete oldHashesRow;
        //delete oldKeysRow;
        //delete oldValuesRow;
    }

    delete[] hashes;
    delete[] keys;
    delete[] values;
    hashes=newHashes;
    keys=newKeys;
    values=newValues;
}

template<typename TKey, typename TVal>
TVal* Hashtable2<TKey, TVal>::getptr(TKey key){
    HT_HASH_T keyHash=HT_HASH(key);
    HT_HEIGHT_T rowHeight=keyHash%height();
    Autoarr2<HT_HASH_T>* hashesRow=hashes+rowHeight;
    uint32 index=hashesRow->search(keyHash);
    if(index==Autoarr2_NO_REZULT) 
        return NULL;
    Autoarr2<TVal>* valuesRow=values+rowHeight;
    return valuesRow->getptr(index);
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

template<typename TKey, typename TVal>
Hashtable2<TKey, TVal>::~Hashtable2(){
    delete[] keys;
    delete[] values;
}
