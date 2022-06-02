#pragma once

#include "Autoarr2.hpp"

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
        values=new[sizeof(T*)];
        goto create_block;
    }
    else if(block_length==max_block_length){
        block_length=0;
create_block:
        values=(T**)realloc(values,(blocks_count+1)*sizeof(T*));
        values[blocks_count]=new[](max_block_length*sizeof(T));
        blocks_count++;
    }

    values[blocks_count-1][block_length]=value;
    block_length++;
    length++;
}

template<typename T>
Autoarr2<T>::~Autoarr2() {
    for (uint16 i=0;i<blocks_count;i++)
        delete[] values[i];
    delete[] values;
}
