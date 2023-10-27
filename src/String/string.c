#include "string.h"

kt_define(string, NULL, NULL);
Autoarr_define(string);

// copies str content to new char pointer value (adding '\0' at the end)
char* string_extract(allocator_ptr al, string str){
    if(str.length==0) return NULL;
    char* cptr=allocator_alloc(al, str.length+1);
    memcpy(cptr, str.ptr, str.length);
    cptr[str.length]=0;
    return cptr;
}
    
// copies src.ptr content to new string and adds \0 at the end
string string_copy(allocator_ptr al, string src){
    if(!src.ptr)
        throw(ERR_NULLPTR);
    string nstr;
    nstr.length=src.length;
    nstr.ptr=allocator_alloc(al, nstr.length+1);
    memcpy(nstr.ptr, src.ptr, nstr.length);
    nstr.ptr[nstr.length]='\0';
    return nstr;
}

// compares two strings, NullPtr-friendly
bool string_compare(string str0, string str1){
    if(str0.length!=str1.length)
        return false;
    if(!str0.ptr)
        return str1.ptr ? false : true;
    else if(!str1.ptr) return false;
    while(str0.length-->0)
        if(*str0.ptr++ != *str1.ptr++)
            return false;
    return true;
}

// creates new string which is reversed variant of <s>
string string_reverse(allocator_ptr al, string s){
    if(s.length==0) 
        return s;
    string r;
    r.ptr=allocator_alloc(al, s.length);
    r.length=s.length;
    for(u32 i=0; i<s.length; i++)
        r.ptr[i]=s.ptr[s.length-i-1];
    return r;
}
