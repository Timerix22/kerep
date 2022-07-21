#pragma once

#include "../base/base.h"

#define __AUTOARR2_MAX_BLOCK_LENGTH_DEFAULT 64
#define Autoarr2_NO_REZULT (uint32)-1


template<typename T>
class Autoarr2 {
    T** values;
public:
    uint16 blocks_count;
    uint16 block_length;
    uint16 max_block_length;
    uint32 length;

    Autoarr2();
    explicit Autoarr2(uint16 _max_block_length);
    virtual ~Autoarr2();

    T* getptr(uint32 index);
    T get(uint32 index);
    void set(uint32 index, T value);
    void add(T value);
    void remove(uint32 index);

    // returns index of the first <value> inclusion
    // using <cmpf> to compare values
    template<class cmp_func_lambda>
    uint32 search(T& value, cmp_func_lambda cmpf, uint32 fromIndex, uint32 toIndex);
    template<class cmp_func_lambda>
    uint32 search(T& value, cmp_func_lambda cmpf, uint32 fromIndex);
    template<class cmp_func_lambda>
    uint32 search(T& value, cmp_func_lambda cmpf);
};

template<typename T>
Autoarr2<T>::Autoarr2(uint16 _max_block_length)  {
    values = NULL;
    block_length = 0;
    blocks_count = 0;
    length = 0;
    max_block_length=_max_block_length;
}

template<typename T>
Autoarr2<T>::Autoarr2() : Autoarr2(__AUTOARR2_MAX_BLOCK_LENGTH_DEFAULT) {}

template<typename T>
Autoarr2<T>::~Autoarr2() {
    for (uint16 i=0;i<blocks_count;i++)
         delete[] values[i];
    delete[] values;
}


template<typename T>
T *Autoarr2<T>::getptr(uint32 index) {
    if(index>=length) throw_id(ERR_WRONGINDEX);
    return values[index/max_block_length]+index%max_block_length;
}

template<typename T>
T Autoarr2<T>::get(uint32 index) {
    return *getptr(index);
}

template<typename T>
void Autoarr2<T>::set(uint32 index, T value) {
    *getptr(index)=value;
}

template<typename T>
void Autoarr2<T>::add(T value) {
    if(!values){
        values=new T*[1];
        goto create_block;
    }
    else if(block_length==max_block_length){
        block_length=0;
create_block:
        T** new_values=new T*[blocks_count+1];
        for(uint32 i=0;i<blocks_count;i++)
            new_values[i]=values[i];
        new_values[blocks_count]=new T[max_block_length];
        delete[] values;
        values=new_values;
        blocks_count++;
    }

    values[blocks_count-1][block_length]=value;
    block_length++;
    length++;
}

template<typename T>
template<class cmp_func_lambda>
uint32 Autoarr2<T>::search(T& value, cmp_func_lambda cmpf, uint32 fromIndex, uint32 toIndex){
    uint32 index=fromIndex;
    for(; index<toIndex; index++)
        if(cmpf(value,get(index)))
            return index;
    return Autoarr2_NO_REZULT;
}

template<typename T>
template<class cmp_func_lambda>
uint32 Autoarr2<T>::search(T& value, cmp_func_lambda cmpf, uint32 fromIndex){
    return search(value, cmpf, fromIndex, length);
}

template<typename T>
template<class cmp_func_lambda>
uint32 Autoarr2<T>::search(T& value, cmp_func_lambda cmpf){
    return search(value, cmpf, 0, length);
}

template<typename T>
void Autoarr2<T>::remove(uint32 index){
    throw_id(ERR_NOTIMPLEMENTED);
}