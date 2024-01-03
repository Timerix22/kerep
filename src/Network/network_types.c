#include "network_types.h"

ktid_define(knIPV4Address);
ktid_define(knIPV4Endpoint);

Maybe knIPV4Address_fromStr(char* addrStr){
    char* addrStr_src=addrStr;
    char* errmsg_extra="wrong char";
    u8 c;
    knIPV4Address addr;
    addr.UintBigEndian=0;
    u16 n=0;
    for(u8 i=0; i<4; ){
        c=*addrStr++;
        switch (c){
            case '\0':
                if(i<3){
                    errmsg_extra="end of string";
                    goto default_case;
                }
                
                addr.bytes[i++]=n;
                n=0;
                break;
            case '.':
                addr.bytes[i++]=n;
                n=0;
                break;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                n=n*10+c-'0';
                if(n>255) {
                    errmsg_extra="one part of address > 255";
                    goto default_case;
                }
                break;
            default_case:
            default:
                u32 errmsgL=cptr_length(addrStr) + 80;
                char* errmsg=malloc(errmsgL);
                IFMSC(sprintf_s(errmsg, errmsgL, "wrong ip address string: %s\n   %s", addrStr_src, errmsg_extra), 
                      sprintf(  errmsg,          "wrong ip address string: %s\n   %s", addrStr_src, errmsg_extra));
                safethrow(errmsg,;);
                break;
        }
    }
    //TODO UniStack for generic structs
    return SUCCESS(UniUInt64(addr.UintBigEndian));
}

char* knIPV4Address_toString(knIPV4Address* address) {
    char* a = toString_u64(address->bytes[0], 0, 0);
    char* b = toString_u64(address->bytes[1], 0, 0);
    char* c = toString_u64(address->bytes[2], 0, 0);
    char* d = toString_u64(address->bytes[3], 0, 0);
    char* s = cptr_concat(a,".",b,".",c,".",d);
    free(a);
    free(b);
    free(c);
    free(d);
    return s;
}

char* knIPV4Endpoint_toString(knIPV4Endpoint* end) {
    char* a = knIPV4Address_toString(&end->address);
    char* p = toString_u64(end->port, 0, 0);
    char* s = cptr_concat(a,":",p);
    free(a);
    free(p);
    return s;
}
