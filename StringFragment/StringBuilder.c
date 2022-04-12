#include "StringBuilder.h"

StringBuilder StringBuilder_create(uint16 max_blocks_count, uint16 max_block_length){
    return Autoarr_create(int8,max_blocks_count,max_block_length);
}

void StringBuilder_append_char(StringBuilder* b, char c){
    Autoarr_add(b,c);
}

void StringBuilder_append_cptr(StringBuilder* b, char* s){
    char c;
    while((c=*s++))
        Autoarr_add(b,c);
}

void StringBuilder_append_string(StringBuilder* b, StringFragment s){
    s.ptr+=s.offset;
    while(s.length-->0)
        Autoarr_add(b,*s.ptr++);
}

void StringBuilder_append_int64(StringBuilder* b, int64 a){
    uint8 i=0;
    if(a==0){
        Autoarr_add(b,'0');
        return;
    }
    else if(a<0){
        Autoarr_add(b,'-');
        a=-a;
    }
    char buf[24];
    while(a!=0){
        buf[i++]='0'+a%10;
        a/=10;
    }
    StringFragment rev=StringFragment_reverse((StringFragment){buf,0,i});
    StringBuilder_append_string(b,rev);
    free(rev.ptr);
}

void StringBuilder_append_uint64(StringBuilder* b, uint64 a){
    uint8 i=0;
    if(a==0){
        Autoarr_add(b,'0');
        return;
    }
    char buf[24];
    while(a!=0){
        buf[i++]='0'+a%10;
        a/=10;
    }
    StringFragment rev=StringFragment_reverse((StringFragment){buf,0,i});
    StringBuilder_append_string(b,rev);
    free(rev.ptr);
}

void StringBuilder_append_double(StringBuilder* b, double a){
    char buf[32];
    IFWIN(
        sprintf_s(buf,32,"%lf",a),
        sprintf(buf,"%lf",a)
    );
    StringBuilder_append_cptr(b,buf);
}

StringFragment StringBuilder_build(StringBuilder* b){
    StringFragment str={
        .offset=0,
        .length=Autoarr_length(b)
    };
    str.ptr=malloc(str.length+1);
    for(uint32 i=0; i<str.length; i++)
        str.ptr[i]=Autoarr_get(b,i);
    str.ptr[str.length]='\0';
    return str;
}
