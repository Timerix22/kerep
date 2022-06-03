#pragma once

#include "../base/base.h"

#define Autoarr2_NO_REZULT -1

template <typename T>
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
    // returns index of the first <value> inclusion
    uint32 search(T& value);
    uint32 search(T& value, uint32 fromIndex);
    uint32 search(T& value, uint32 fromIndex, uint32 toIndex);
};


#define __AUTOARR2_MAX_BLOCK_LENGTH_DEFAULT 64

template<typename T>
Autoarr2<T>::Autoarr2() {
    values=NULL;
    block_length=0;
    blocks_count=0;
    length=0;
    max_block_length=__AUTOARR2_MAX_BLOCK_LENGTH_DEFAULT;
}

template<typename T>
Autoarr2<T>::Autoarr2(uint16 _max_block_length) : Autoarr2() {
    max_block_length=_max_block_length;
}

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
        //values=(T**)malloc(sizeof(T*));
        values=new T*[1];
        goto create_block;
    }
    else if(block_length==max_block_length){
        block_length=0;
create_block:
        T** new_values=new T*[blocks_count+1];
        for(uint32 i=0;i<blocks_count;i++)
            new_values[i]=values[i];
        delete[] values;
        values=new_values;
        values[blocks_count]=new T[max_block_length];
        blocks_count++;
    }

    values[blocks_count-1][block_length]=value;
    block_length++;
    length++;
}


template<typename T>
uint32 Autoarr2<T>::search(T& value, uint32 fromIndex, uint32 toIndex){
    uint32 index=fromIndex;
    for(; index<toIndex; index++)
        if(value==get(index))
            return index;
    return Autoarr2_NO_REZULT;
}

template<typename T>
uint32 Autoarr2<T>::search(T& value, uint32 fromIndex){
    return search(value, fromIndex, length);
}

template<typename T>
uint32 Autoarr2<T>::search(T& value){
    return search(value, 0, length);
}
