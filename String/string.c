#include "../String/string.h"

// copies str content to new char pointer value (adding '\0' at the end)
char* string_cpToCptr(string str){
    if(str.length==0) return NULL;
    char* cptr=malloc(str.length*sizeof(char)+1);
    cptr[str.length]=0;
    while(str.length-->0)
        cptr[str.length]=str.ptr[str.length];
    return cptr;
}

// copies cptr content (excluding '\0' at the end) to new string
string string_cpFromCharPtr(char* cptr){
    if(!cptr) return stringNull;
    string str;
    str.length=cptr_length(cptr)-1;
    str.ptr=malloc(str.length);
    for(uint32 i=0;i<str.length;i++)
        str.ptr[i]=cptr[i];
    return str;
}

// compares two strings, NullPtr-friendly
bool string_compare(string str0, string str1){
    if(str0.length!=str1.length) return false;
    if(!str0.ptr) return str1.ptr ? false : true;
    else if(!str1.ptr) return false;
    while(str0.length-->0)
        if(*str0.ptr++ != *str1.ptr++) 
            return false;
    return true;
}

// creates new string which is reversed variant of <s>
string string_reverse(string s){
    if(s.length==0) return s;
    string r={malloc(s.length), s.length};
    for(uint32 i=0; i<s.length; i++)
        r.ptr[i]=s.ptr[s.length-i-1];
    return r;
}
