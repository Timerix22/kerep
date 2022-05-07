#include "hash.h"

uint32 hash32(char *str){
    uint32 hash=5381;
    for (char c=*str;c;c=*(++str))
        hash=((hash<<5)+hash)+c;
    return hash;
}

uint64 hash64(char* str){
    uint64 hash = 0;
    for (char c=*str;c;c=*(++str))
        hash=c+(hash<<6)+(hash<<16)-hash;
    return hash;
}
