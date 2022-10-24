#include "base_toString.h"
#include "../cptr.h"
#include "../../kprint/kprint_format.h"

char* __toString_char(void* c, uint32 fmt) {
    char* cc=malloc(2); 
    cc[0]=*(char*)c;
    cc[1]=0;
    return cc;
}

char* __toString_charPtr(void* c, uint32 fmt){
    return cptr_copy(*(char**)c);
}

char* __toString_bool(void* c, uint32 fmt) {
    static const char _strbool[4][6]={ "false", "true\0", "False", "True\0" };
    uint8 strind=*(bool*)c==1 + kprint_format_uppercase(fmt)*2;
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
    int64 d=n;
    char str[32];
    uint8 i=sizeof(str);
    str[--i]=0;
    while(d!=0){
        str[--i]='0' + d%10;
        d/=10;
    }
    if(n>>63)
        str[--i]='-';
    return cptr_copy((char*)str+i);
}

char* toString_uint(uint64 n, bool withPostfix, bool uppercase){
    uint64 d=n;
    char str[32];
    uint8 i=sizeof(str);
    str[--i]=0;
    if(withPostfix)
        str[--i]= uppercase ? 'U' : 'u';
    while(d!=0){
        str[--i]='0' + d%10;
        d/=10;
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

char* toString_bin(char* bytes, uint32 size, bool withPrefix){
    char* str=malloc(size*8 + (withPrefix?2:0) +1);
    uint32 cn=0;
    if(withPrefix){
        str[cn++]='0';
        str[cn++]='b';
    }
    for(uint32 bn=0; bn<size; bn++){
        char byte=bytes[bn];
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
            return (uppercase ? 'A'-10 : 'a'-10) + u;
        default: return 219;
    }
}

char* toString_hex(char* bytes, uint32 size, bool withPrefix, bool uppercase){
    char* str=malloc(size*2 + (withPrefix?2:0) + 1);
    uint32 cn=0;
    if(withPrefix){
        str[cn++]='0';
        str[cn++]='x';
    }
    for(uint32 bn=0; bn<size; bn++){
        char byte=bytes[bn];
        str[cn++]=_4bitsHex(byte%16, uppercase);
        str[cn++]=_4bitsHex(byte/16, uppercase);
    }
    str[cn]=0;
    return str;
}


#define __toString_int_def(BITS) char* __toString_int##BITS(void* _n, uint32 f){\
    switch(kprint_format_dataFormat(f)){\
        case kprint_fmtInt: ;\
            int##BITS n=*(int##BITS*)_n;\
            return toString_int(n);\
        case kprint_fmtBin:\
            return toString_bin(_n, BITS/8, kprint_format_withPrefix(f));\
        case kprint_fmtHex:\
            return toString_hex(_n, BITS/8, kprint_format_withPrefix(f), kprint_format_uppercase(f));\
        default:\
            printf("\n%u\n", kprint_format_dataFormat(f));\
            throw(ERR_FORMAT);\
            return NULL;\
    }\
}
__toString_int_def(8)
__toString_int_def(16)
__toString_int_def(32)
__toString_int_def(64)

#define __toString_uint_def(BITS) char* __toString_uint##BITS(void* _n, uint32 f){\
    switch(kprint_format_dataFormat(f)){\
        case kprint_fmtUInt: ;\
            uint##BITS n=*(uint##BITS*)_n;\
            return toString_uint(n, kprint_format_withPostfix(f), kprint_format_uppercase(f));\
        case kprint_fmtBin:\
            return toString_bin(_n, BITS/8, kprint_format_withPrefix(f));\
        case kprint_fmtHex:\
            return toString_hex(_n, BITS/8, kprint_format_withPrefix(f), kprint_format_uppercase(f));\
        default:\
            printf("\n%u\n", kprint_format_dataFormat(f));\
            throw(ERR_FORMAT);\
            return NULL;\
    }\
}
__toString_uint_def(8)
__toString_uint_def(16)
__toString_uint_def(32)
__toString_uint_def(64)

#define __toString_float_def(BITS) char* __toString_float##BITS(void* _n, uint32 f){\
    switch(kprint_format_dataFormat(f)){\
        case kprint_fmtFloat: ;\
            float##BITS n=*(float##BITS*)_n;\
            return toString_float(n, kprint_format_withPostfix(f), kprint_format_uppercase(f));\
        case kprint_fmtBin:\
            return toString_bin(_n, BITS/8, kprint_format_withPrefix(f));\
        case kprint_fmtHex:\
            return toString_hex(_n, BITS/8, kprint_format_withPrefix(f), kprint_format_uppercase(f));\
        default:\
            printf("\n%u\n", kprint_format_dataFormat(f));\
            throw(ERR_FORMAT);\
            return NULL;\
    }\
}

__toString_float_def(32)
__toString_float_def(64)
