#include "tests.h"
#include "../src/Network/network.h"

void __test_knIPV4Address_fromStr(char* addrStr, uint8 a, uint8 b, uint8 c, uint8 d){
    tryLast(knIPV4Address_fromStr(addrStr), maybeAddr){
        knIPV4Address addr;
        addr.address=(uint32)maybeAddr.value.UInt64;
        printf("\e[94mknIPV4Address_fromStr(\e[96m%s\e[94m) -> ", addrStr);
        if(maybeAddr.value.UInt64!=knIPV4Address_fromBytes(a,b,c,d).address){
            printf("\e[91m%u.%u.%u.%u\n", 
                (uint8)addr.bytes[0], (uint8)addr.bytes[1], (uint8)addr.bytes[2], (uint8)addr.bytes[3]);
            throw("knIPV4Address_fromStr returned wrong value");
        }
        else printf("\e[92m%u.%u.%u.%u\n",
                (uint8)addr.bytes[0], (uint8)addr.bytes[1], (uint8)addr.bytes[2], (uint8)addr.bytes[3]);
    }
}
#define test_knIPV4Address_fromStr(a,b,c,d) __test_knIPV4Address_fromStr(#a"."#b"."#c"."#d, a,b,c,d)

void test_network(){
    optime(__func__,1,({
        printf("\e[96m------------[test_network]------------\n");
        
        PRINT_SIZEOF(knIPV4Address);
        PRINT_SIZEOF(knPort);
        PRINT_SIZEOF(knIPV4Endpoint);
        PRINT_SIZEOF(knPackage);
        PRINT_SIZEOF(knChannel);
        PRINT_SIZEOF(knSocket);

        test_knIPV4Address_fromStr(127,0,0,1);
        test_knIPV4Address_fromStr(34,255,45,0);
        test_knIPV4Address_fromStr(3,3,3,128);

        knSocket* s;
        tryLast(knSocket_open(knSocketProtocol_TCP), maybeS)
            s=maybeS.value.VoidPtr;
        printf("\e[92mTCP socket created\n");
        tryLast(knSocket_close(s);,_);
        printf("\e[92mTCP socket closed\n");
    }));
}