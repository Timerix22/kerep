#include "base_toString.h"
#include "../base.h"
#include "../../kprint/kprint_format.h"

char* __toString_char(void* c, uint32 fmt) {
    //*c=char
    if(kp_fmt_dataFormat(fmt)==kp_c){
        char* cc=malloc(2); 
        cc[0]=*(char*)c;
        cc[1]=0;
        return cc;
    }
    // *c=cstring
    else if(kp_fmt_dataFormat(fmt)==kp_s){
        return cptr_copy(*(char**)c);
    }
    else throw(ERR_FORMAT);
}

char* __toString_bool(void* c, uint32 fmt) {
    static const char _strbool[4][6]={ "false", "true\0", "False", "True\0" };
    uint8 strind=*(bool*)c==1 + kp_fmt_isUpper(fmt)*2;
    char* rez=malloc(6);
    rez[0]=_strbool[strind][0];
    rez[1]=_strbool[strind][1];
    rez[2]=_strbool[strind][2];
    rez[3]=_strbool[strind][3];
    rez[4]=_strbool[strind][4];
    rez[5]=0;
    return rez;
}

char* toString_int(int64 n){
    int64 d=n<0 ? -1*n : n;
    char str[32];
    uint8 i=sizeof(str);
    str[--i]=0;
    if(d==0)
        str[--i]='0';
    else while(d!=0){
        str[--i]='0' + d%10;
        d/=10;
    }
    if(n<0)
        str[--i]='-';
    return cptr_copy((char*)str+i);
}

char* toString_uint(uint64 n, bool withPostfix, bool uppercase){
    char str[32];
    uint8 i=sizeof(str);
    str[--i]=0;
    if(withPostfix)
        str[--i]= uppercase ? 'U' : 'u';
    if(n==0)
        str[--i]='0';
    else while(n!=0){
        str[--i]='0' + n%10;
        n/=10;
    }
    return cptr_copy((char*)str+i);
}

char* toString_float(float64 n, bool withPostfix, bool uppercase){
    // int64 d=n;
    // float64 r=n-d;
    // char* strint=toString_int(d);
    // char strfract[32];
    // uint8 i=0;
    // strfract[i++]='.';
    // while(r!=0){
    //     r*=10.0;
    //     char fc=r;
    //     strfract[i++]=fc;
    //     r-=fc;
    // }
    // if(withPostfix)
    //     strfract[i++]= uppercase ? 'F' : 'f';
    // strfract[i]=0;
    // char* str==cptr_concat(strint, strfract);
    // free(strint);
    // return str;
    return cptr_copy("<float>");
}

char* toString_bin(void* _bytes, uint32 size, bool withPrefix){
    char* bytes=_bytes;
    char* str=malloc(size*8 + (withPrefix?2:0) +1);
    uint32 cn=0;
    if(withPrefix){
        str[cn++]='0';
        str[cn++]='b';
    }
    for(uint32 bn=0; bn<size; bn++){
        unsigned char byte=bytes[bn];
        for(uint8 i=0; i<8; i++)
            str[cn++]='0' + (byte & (char)128>>i);
    }
    str[cn]=0;
    return str;
}

char _4bitsHex(uint8 u, bool uppercase){
    switch(u){
        case 0: case 1: case 2: case 3: case 4:
        case 5: case 6: case 7: case 8: case 9:
            return '0'+u;
        case 0xA: case 0xB: case 0xC: 
        case 0xD: case 0xE: case 0xF:
            return (uppercase ? 'A' : 'a') + u -10;
        default: 
            dbg(u);
            throw("incorrect number");
            return 219;
    }
}

char* toString_hex(void* _bytes, uint32 size, bool withPrefix, bool uppercase){
    char* bytes=_bytes;
    char* str=malloc(size*2 + (withPrefix?2:0) + 1);
    uint32 cn=0;
    if(withPrefix){
        str[cn++]='0';
        str[cn++]='x';
    }
    for(uint32 bn=0; bn<size; bn++){
        unsigned char byte=bytes[bn];
        str[cn++]=_4bitsHex(byte%16, uppercase);
        str[cn++]=_4bitsHex(byte/16, uppercase);
    }
    str[cn]=0;
    return str;
}


#define __toString_int_def(BITS) char* __toString_int##BITS(void* _n, uint32 f){\
    switch(kp_fmt_dataFormat(f)){\
        case kp_i: ;\
            int##BITS n=*(int##BITS*)_n;\
            return toString_int(n);\
        case kp_b:\
            return toString_bin(_n, BITS/8, kp_fmt_withPrefix(f));\
        case kp_h:\
            return toString_hex(_n, BITS/8, kp_fmt_withPrefix(f), kp_fmt_isUpper(f));\
        default:\
            kprintf("\n%u\n", kp_fmt_dataFormat(f));\
            throw(ERR_FORMAT);\
            return NULL;\
    }\
}
__toString_int_def(8)
__toString_int_def(16)
__toString_int_def(32)
__toString_int_def(64)

#define __toString_uint_def(BITS) char* __toString_uint##BITS(void* _n, uint32 f){\
    switch(kp_fmt_dataFormat(f)){\
        case kp_u: ;\
            uint##BITS n=*(uint##BITS*)_n;\
            return toString_uint(n, kp_fmt_withPostfix(f), kp_fmt_isUpper(f));\
        case kp_b:\
            return toString_bin(_n, BITS/8, kp_fmt_withPrefix(f));\
        case kp_h:\
            return toString_hex(_n, BITS/8, kp_fmt_withPrefix(f), kp_fmt_isUpper(f));\
        default:\
            kprintf("\n%u\n", kp_fmt_dataFormat(f));\
            throw(ERR_FORMAT);\
            return NULL;\
    }\
}
__toString_uint_def(8)
__toString_uint_def(16)
__toString_uint_def(32)
__toString_uint_def(64)

#define __toString_float_def(BITS) char* __toString_float##BITS(void* _n, uint32 f){\
    switch(kp_fmt_dataFormat(f)){\
        case kp_f: ;\
            float##BITS n=*(float##BITS*)_n;\
            return toString_float(n, kp_fmt_withPostfix(f), kp_fmt_isUpper(f));\
        case kp_b:\
            return toString_bin(_n, BITS/8, kp_fmt_withPrefix(f));\
        case kp_h:\
            return toString_hex(_n, BITS/8, kp_fmt_withPrefix(f), kp_fmt_isUpper(f));\
        default:\
            kprintf("\n%u\n", kp_fmt_dataFormat(f));\
            throw(ERR_FORMAT);\
            return NULL;\
    }\
}

__toString_float_def(32)
__toString_float_def(64)
