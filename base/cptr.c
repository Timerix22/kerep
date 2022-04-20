#include "base.h"

// returns length of char buffer (without \0)
uint32 cptr_length(char* str){
    uint32 len=0;
    while(*(str++)) len++;
    return len;
}

// allocates new char[] and copies src there
char* cptr_copy(char* src){
    uint32 len=cptr_length(src);
    char* dst=malloc(len+1);
    while(len-->0)
        dst[len]=src[len];
    return dst;
}

// compares two char buffers, NullPtr-friendly
bool cptr_compare(char* key0, char* key1){
    if(!key0) return key1 ? false : true;
    if(!key1) return false;
    while(*key0&&*key1)
        if(*key0++ != *key1++) 
            return false;
    return true;
}

// multiplies char n times
char* char_multiply(char c, uint32 n){
    char* rez=malloc(n+1);
    rez[n]=0;
    while(n-->0)
        rez[n]=c;
    return rez;
}
