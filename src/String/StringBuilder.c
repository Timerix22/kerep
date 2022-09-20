#include "StringBuilder.h"

Autoarr_define(string)
ktId_define(AutoarrString);
ktId_define(AutoarrStringPtr);

ktId_define(StringBuilder);
ktId_define(StringBuilderPtr);

#define BL_C 32
#define BL_L 1024


void complete_buf(StringBuilder* b){
    if(!b->compl_bufs) 
        b->compl_bufs=Autoarr_create(string,BL_C,BL_L);
    uint32 len=Autoarr_length(b->curr_buf);
    if(!len) return;
    string str={.length=len, .ptr=malloc(len)};
    uint32 i=0;
    Autoarr_foreach(b->curr_buf, c, ({
        str.ptr[i++]=c;
    }));
    Autoarr_add(b->compl_bufs,str);
    Autoarr_free(b->curr_buf, true);
    b->curr_buf=Autoarr_create(int8,BL_C,BL_L);
}

void try_complete_buf(StringBuilder* b){
    if(b->curr_buf->blocks_count==BL_C)
        complete_buf(b);
}


StringBuilder* StringBuilder_create(){
    StringBuilder* b=malloc(sizeof(StringBuilder));
    b->compl_bufs=NULL;
    b->curr_buf=Autoarr_create(int8,BL_C,BL_L);
    return b;
}

void __StringBuilder_free(void* _b){
    StringBuilder* b=_b;
    if(b->compl_bufs) Autoarr_free(b->compl_bufs, true);
    Autoarr_free(b->curr_buf, true);
}
void StringBuilder_free(StringBuilder* b){
    __StringBuilder_free(b);
    free(b);
}

string StringBuilder_build(StringBuilder* b){
    complete_buf(b);
    uint32 len=0;
    Autoarr_foreach(b->compl_bufs, cs, ({
        len+=cs.length;
    }));
    string str= { .length=len, .ptr=malloc(len+1) };
    str.ptr[len]='\0';
    uint32 i=0;
    Autoarr_foreach(b->compl_bufs, cs, ({
        for(uint32 n=0;n<cs.length;n++)
            str.ptr[i++]=cs.ptr[n];
        free(cs.ptr);
    }));
    StringBuilder_free(b);
    return str;
}


void StringBuilder_rmchar(StringBuilder* b){
    if(b->curr_buf->block_length!=0)
        Autoarr_pop(b->curr_buf)
    else {
        if(!b->compl_bufs) throw(ERR_NULLPTR);
        string* lastcb=Autoarr_getptr(b->compl_bufs, (Autoarr_length(b->compl_bufs)-1));
        lastcb->length--;
    }
}


void StringBuilder_append_char(StringBuilder* b, char c){
    try_complete_buf(b);
    Autoarr_add(b->curr_buf,c);
}


void StringBuilder_append_string(StringBuilder* b, string s){
    complete_buf(b);
    Autoarr_add(b->compl_bufs, string_copy(s));
}

void StringBuilder_append_cptr(StringBuilder* b, char* s){
    string str={
        .ptr=s, 
        .length=cptr_length(s)
    };
    StringBuilder_append_string(b,str);
}

void curr_buf_add_string(StringBuilder* b, string s){
    for(uint32 i=0; i<s.length; i++)
        Autoarr_add(b->curr_buf,s.ptr[i]);
}

void StringBuilder_append_int64(StringBuilder* b, int64 a){
    try_complete_buf(b);
    uint8 i=0;
    if(a==0){
        Autoarr_add(b->curr_buf,'0');
        return;
    }
    else if(a<0){
        Autoarr_add(b->curr_buf,'-');
        a=-a;
    }
    char buf[24];
    while(a!=0){
        buf[i++]='0'+a%10;
        a/=10;
    }
    string rev=string_reverse((string){buf,i});
    curr_buf_add_string(b,rev);
    free(rev.ptr);
}

void StringBuilder_append_uint64(StringBuilder* b, uint64 a){
    try_complete_buf(b);
    uint8 i=0;
    if(a==0){
        Autoarr_add(b->curr_buf,'0');
        return;
    }
    char buf[24];
    while(a!=0){
        buf[i++]='0'+a%10;
        a/=10;
    }
    string rev=string_reverse((string){buf,i});
    curr_buf_add_string(b,rev);
    free(rev.ptr);
}

void StringBuilder_append_float64(StringBuilder* b, double a){
    try_complete_buf(b);
    char buf[32];
    IFMSC(
        sprintf_s(buf,32,"%lf",a),
        sprintf(buf,"%lf",a)
    );
    curr_buf_add_string(b, (string){.ptr=buf, .length=cptr_length(buf)});
}
