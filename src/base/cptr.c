#include "base.h"

// returns length of char buffer (without \0)
uint32 cptr_length(char* str){
    uint32 len=0;
    while(*(str++)) len++;
    return len;
}

// allocates new char[] and copies src there
char* cptr_copy(char* src){
    uint32 len=cptr_length(src)+1;
    char* dst=malloc(len);
    while(len--!=0)
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
    while(n--!=0)
        rez[n]=c;
    return rez;
}

bool cptr_startsWith(char* ptr, char* fragment){
    for(char cs=*ptr, cf=*fragment; cf; cs=*++ptr, cf=*++fragment)
        if(cs!=cf) return false;
    return true;
}

bool cptr_endsWith(char* ptr, char* fragment){
    ptr+=cptr_length(ptr)-cptr_length(fragment);
    for(char cs=*ptr, cf=*fragment; cf; cs=*++ptr, cf=*++fragment)
        if(cs!=cf) return false;
    return true;
}

void memcopy(void* from, void* to, uint32 size){
    if(from==NULL || to==NULL)
        throw(ERR_NULLPTR);
    for(uint32 i=0; i<size; i++)
        ((char*)to)[i]=((char*)from)[i];
}

char* __cptr_concat(uint16 n, ...){
    char** strs=(char**)malloc(n*sizeof(char*));
    uint32* lengths=malloc(n*sizeof(uint32));
    uint32 totalLength=0;

    // reading args from va_list
    va_list vl;
    va_start(vl, n);
    for(uint16 i=0; i<n; i++){
        char* str=va_arg(vl,char*);
        int16 length=cptr_length(str);
        strs[i]=str;
        lengths[i]=length;
        totalLength+=length;
    }
    va_end(vl);

    // allocating memory for output value
    char* totality=malloc(totalLength+1);
    const char* output=totality;
    totality[totalLength]=0;
    
    // copying content of all strings to rezult
    for(uint16 k=0; k<n; k++){
        memcopy(strs[k], totality, lengths[k]);
        totality+=lengths[k];
    }
    
    free(strs);
    free(lengths);
    return output;
}
