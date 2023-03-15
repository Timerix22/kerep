#include "base.h"

// returns length of char buffer (without \0)
u32 cptr_length(char* str){
    u32 len=0;
    while(*(str++)) len++;
    return len;
}

// allocates new char[] and copies src there
char* cptr_copy(char* src){
    u32 len=cptr_length(src)+1;
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
char* char_multiply(char c, u32 n){
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

u32 cptr_indexOf(char* ptr, char* fragment){
    char sc=*ptr;
    for(u32 si=0, fi=0; sc!='\0'; si++){
        sc=ptr[si];
        if(sc==fragment[fi]){
            fi++;
            if(fragment[fi]==0)
                return si-fi+1;
        }
        else fi=0;
    }
    return -1;
}
u32 cptr_indexOfChar(char* ptr, char fragment){
    char sc=*ptr;
    for(u32 si=0; sc!='\0'; si++){
        sc=ptr[si];
        if(sc==fragment){
            return si;
        }
    }
    return -1;
}
u32 cptr_lastIndexOf(char* ptr, char* fragment){
    char sc=*ptr;
    u32 fi_last=cptr_length(fragment)-1;
    for(i32 si=cptr_length(ptr)-1, fi=fi_last; si>=0; si--){
        sc=ptr[si];
        if(sc==fragment[fi]){
            if(fi==0)
                return si;
            fi--;
        }
        else fi=fi_last;
    }
    return -1;
}
u32 cptr_lastIndexOfChar(char* ptr, char fragment){
    char sc=*ptr;
    for(i32 si=cptr_length(ptr)-1; si>=0; si--){
        sc=ptr[si];
        if(sc==fragment){
            return si;
        }
    }
    return -1;
}

void memcopy(void* from, void* to, u32 size){
    if(from==NULL || to==NULL)
        throw(ERR_NULLPTR);
    for(u32 i=0; i<size; i++)
        ((char*)to)[i]=((char*)from)[i];
}

char* __cptr_concat(u32 n, ...){
    char** strs=(char**)malloc(n*sizeof(char*));
    u32* lengths=malloc(n*sizeof(u32));
    u32 totalLength=0;

    // reading args from va_list
    va_list vl;
    va_start(vl, n);
    for(u16 i=0; i<n; i++){
        char* str=va_arg(vl,char*);
        i16 length=cptr_length(str);
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
    for(u16 k=0; k<n; k++){
        memcopy(strs[k], totality, lengths[k]);
        totality+=lengths[k];
    }
    
    free(strs);
    free(lengths);
    return output;
}
