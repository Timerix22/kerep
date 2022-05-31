//
//
//

#include "Autoarr2.hpp"

#define MAX_BLOCK_LENGTH_DEFAULT 64

template<typename T>
Autoarr2<T>::Autoarr2() {
    values=NULL;
    block_length=0;
    blocks_count=0;
    max_block_length=MAX_BLOCK_LENGTH_DEFAULT;
}

 template<typename T>
Autoarr2<T>::Autoarr2(uint16 _max_block_length) : Autoarr2() {
    max_block_length=_max_block_length;
}

template<typename T>
T *Autoarr2<T>::GetPtr(uint32 index) {
    if(index>=Length) throwcpp_id(ERR_WRONGINDEX);
    return values[index/max_block_length]+index%max_block_length;
}

template<typename T>
T Autoarr2<T>::Get(uint32 index) {
    return *GetPtr(index);
}

template<typename T>
void Autoarr2<T>::Set(uint32 index, T value) {
    *GetPtr(index)=value;
}

template<typename T>
void Autoarr2<T>::Add(T value) {
    if(!values){
        values=malloc(sizeof(T*));
        goto create_block;
    }
    else if(block_length==max_block_length){
        block_length=0;
create_block:
        values=realloc(values,(blocks_count+1)*sizeof(T*));
        values[blocks_count]=malloc(max_block_length*sizeof(T));
        blocks_count++;
    }

    values[blocks_count-1][block_length]=value;
    block_length++;
    Length++;
}

template<typename T>
Autoarr2<T>::~Autoarr2() {
    for (uint16 i=0;i<blocks_count;i++)
        delete[] values[i];
    delete[] values;
}
