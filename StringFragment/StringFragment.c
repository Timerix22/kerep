#include "StringFragment.h"

// copies <length> characters from <ptr+offset> to new StringFragment (adding '\0' at the end)
StringFragment StringFragment_extract(StringFragment str){
    if(str.length==0) return stringNull;
    StringFragment extr={
        .offset=0,
        .length=str.length,
        .ptr=malloc(str.length+1)
    };
    str.ptr+=str.offset;
    for(uint32 i=0; i<str.length; i++)
        extr.ptr[i]=str.ptr[i];
    extr.ptr[str.length]='\0';
    return extr;
}

// compares two strings, NullPtr-friendly
bool StringFragment_compare(StringFragment str0, StringFragment str1){
    if(str0.length!=str1.length) return false;
    if(!str0.ptr) return str1.ptr ? false : true;
    else if(!str1.ptr) return false;
    str0.ptr+=str0.offset;
    str1.ptr+=str1.offset;
    while(str0.length-->0)
        if(*str0.ptr++ != *str1.ptr++) 
            return false;
    return true;
}

// creates new StringFragment which is reversed variant of <s>
StringFragment StringFragment_reverse(StringFragment s){
    if(s.length==0) return s;
    StringFragment r={
        .offset=0,
        .length=s.length,
        .ptr=malloc(s.length)
    };
    for(uint32 i=0; i<s.length; i++)
        r.ptr[i+s.offset]=s.ptr[s.length-i-1];
    return r;
}
