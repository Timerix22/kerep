#include "knAddress.h"

Maybe knIPV4Address_fromStr(char* addrStr){
    char* addrStr_src=addrStr;
    char* errmsg_extra="wrong char";
    uint8 c;
    knIPV4Address addr;
    addr.address=0;
    uint16 n=0;
    for(uint8 i=0; i<4; ){
        c=*addrStr++;
        switch (c){
            case '\0':
                if(i<3) {
                    errmsg_extra="end of string";
                    goto default_case;
                }
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
                uint32 errmsgL=cptr_length(addrStr) + 80;
                char* errmsg=malloc(errmsgL);
                IFMSC(sprintf_s(errmsg, errmsgL, "wrong ip address string: %s\n   %s", addrStr_src, errmsg_extra), 
                      sprintf(  errmsg,          "wrong ip address string: %s\n   %s", addrStr_src, errmsg_extra));
                safethrow(errmsg,;);
                break;
        }
    }
    return SUCCESS(Uni(UInt64, (uint64)addr.address));
}
