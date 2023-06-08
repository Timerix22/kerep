#include "StringBuilder.h"

kt_define(StringBuilder, (destruct_t)StringBuilder_destruct, NULL);

#define BL_C 32
#define BL_L 1024


void complete_buf(StringBuilder* b){
    if(!b->compl_bufs)
        b->compl_bufs=Autoarr_create(string,BL_C,BL_L);
    u32 len=Autoarr_length(b->curr_buf);
    if(len==0)
        return;
    string str={.length=len, .ptr=malloc(len)};
    u32 i=0;
    Autoarr_foreach(b->curr_buf, c,
        str.ptr[i++]=c;
    );
    Autoarr_add(b->compl_bufs,str);
    Autoarr_destruct(b->curr_buf, true);
    b->curr_buf=Autoarr_create(i8,BL_C,BL_L);
}


void StringBuilder_construct(StringBuilder* b, allocator_ptr external_al){
    InternalAllocator_setExternalOrConstruct(b, external_al, LinearAllocator, 1024);
    b->compl_bufs=NULL;
    b->curr_buf=Autoarr_create(i8,BL_C,BL_L);
}

void StringBuilder_destruct(StringBuilder* b){
    if(b->compl_bufs)
        Autoarr_destruct(b->compl_bufs, true);
    Autoarr_destruct(b->curr_buf, true);
    if(InternalAllocator_isInternal(b))
        LinearAllocator_destruct((LinearAllocator*)InternalAllocator_getPtr(b));
}

string StringBuilder_build(StringBuilder* b){
    complete_buf(b);
    u32 len=0;
    Autoarr_foreach(b->compl_bufs, cs,
        len+=cs.length;
    );
    string str= { .length=len, .ptr=malloc(len+1) };
    str.ptr[len]='\0';
    u32 l=0;
    Autoarr_foreach(b->compl_bufs, cs,
        memcpy(str.ptr+l, cs.ptr, cs.length);
        l+=cs.length;
    );
    StringBuilder_destruct(b);
    return str;
}


void StringBuilder_rmchar(StringBuilder* b){
    if(b->curr_buf->chunk_length!=0)
        Autoarr_pop(b->curr_buf)
    else {
        if(!b->compl_bufs) throw(ERR_NULLPTR);
        string* lastcb=Autoarr_getPtr(b->compl_bufs, (Autoarr_length(b->compl_bufs)-1));
        lastcb->length--;
    }
}


void StringBuilder_append_char(StringBuilder* b, char c){
    if(b->curr_buf->chunks_count==BL_C)
        complete_buf(b);
    Autoarr_add(b->curr_buf,c);
}

void StringBuilder_append_string(StringBuilder* b, string s){
    complete_buf(b);
    // TODO remove copying
    Autoarr_add(b->compl_bufs, string_copy(InternalAllocator_getPtr(b), s));
}

void StringBuilder_append_cptr(StringBuilder* b, char* s){
    string str={
        .ptr=s,
        .length=cptr_length(s)
    };
    StringBuilder_append_string(b, str);
}

void StringBuilder_append_i64(StringBuilder* b, i64 a){
    u8 i=0;
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
    string rev=string_reverse(InternalAllocator_getPtr(b), (string){buf,i});
    StringBuilder_append_string(b, rev);
}

void StringBuilder_append_u64(StringBuilder* b, u64 a){
    u8 i=0;
    if(a==0){
        Autoarr_add(b->curr_buf,'0');
        return;
    }
    char buf[24];
    while(a!=0){
        buf[i++]='0'+a%10;
        a/=10;
    }
    string rev=string_reverse(InternalAllocator_getPtr(b), (string){buf,i});
    StringBuilder_append_string(b, rev);
}

void StringBuilder_append_f64(StringBuilder* b, f64 a){
    char buf[32];
    sprintf_s(buf, sizeof(buf), "%lf", a);
    StringBuilder_append_string(b, (string){.ptr=buf, .length=cptr_length(buf)});
}
