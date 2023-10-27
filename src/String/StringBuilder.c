#include "StringBuilder.h"

kt_define(StringBuilder, (destruct_t)StringBuilder_destruct, NULL);

#define BL_C 32
#define BL_L 1024

#define createBuffer() (MemoryChunk){.data = allocator_alloc(InternalAllocator_getPtr(b), 512), .size=512, .occupied_size=0}


void complete_buf(StringBuilder* b){
    if(b->curr_buf.occupied_size == 0)
        return;
    string str={ .length=b->curr_buf.occupied_size, .ptr= b->curr_buf.data };
    Autoarr_add(&b->compl_bufs,str);
    b->curr_buf = createBuffer();
}


void StringBuilder_construct(StringBuilder* b, allocator_ptr external_al){
    InternalAllocator_setExternalOrConstruct(b, external_al, LinearAllocator, 1024);
    Autoarr_construct(&b->compl_bufs, string, 0, InternalAllocator_getPtr(b));
    b->curr_buf = createBuffer();
    b->total_length = 0;
}

void StringBuilder_destruct(StringBuilder* b){
    Autoarr_destruct(&b->compl_bufs);
    allocator_free(InternalAllocator_getPtr(b), b->curr_buf.data);
    InternalAllocator_destructIfInternal(LinearAllocator, b);
}

string StringBuilder_build(StringBuilder* b){
    complete_buf(b);
    string str= { 
        .length = b->total_length,
        .ptr = allocator_alloc(InternalAllocator_getPtr(b), b->total_length+1)
    };
    str.ptr[b->total_length]='\0';
    char* free_space_ptr = str.ptr;
    Autoarr_foreach(&b->compl_bufs, buf,
        memcpy(free_space_ptr, buf.ptr, buf.length);
        free_space_ptr += buf.length;
    );
    StringBuilder_destruct(b);
    return str;
}

void StringBuilder_rmchar(StringBuilder* b){
    if(b->curr_buf.occupied_size != 0)
        b->curr_buf.occupied_size--;
    else {
        for(u32 buf_i = Autoarr_length(&b->compl_bufs) - 1; buf_i != (u32)-1; buf_i--){
            string* lastcb = Autoarr_getPtr(&b->compl_bufs, buf_i);
            if(lastcb->length != 0){
                lastcb->length--;
                break;
            }
        }
    }
}


void StringBuilder_append_char(StringBuilder* b, char c){
    if(b->curr_buf.occupied_size==b->curr_buf.size)
        complete_buf(b);
    ((char*)b->curr_buf.data)[b->curr_buf.occupied_size] = c;
}

void StringBuilder_append_string(StringBuilder* b, string s){
    complete_buf(b);
    Autoarr_add(&b->compl_bufs, s);
}

void StringBuilder_append_cptr(StringBuilder* b, char* s){
    string str={ .ptr=s, .length=cptr_length(s) };
    StringBuilder_append_string(b, str);
}

void StringBuilder_append_i64(StringBuilder* b, i64 a){
    StringBuilder_append_cptr(b, toString_i64(InternalAllocator_getPtr(b), a));
}

void StringBuilder_append_u64(StringBuilder* b, u64 a){
    StringBuilder_append_cptr(b, toString_u64(InternalAllocator_getPtr(b), a, 0, 0));
}

void StringBuilder_append_f64(StringBuilder* b, f64 a){
    StringBuilder_append_cptr(b, toString_f64(InternalAllocator_getPtr(b), a, toString_f64_max_precision, 0, 0));
}
