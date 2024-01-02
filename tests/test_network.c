#include "tests.h"
#include "../src/Network/network.h"

void __test_knIPV4Address_fromStr(char* addrStr, u8 a, u8 b, u8 c, u8 d){
    tryLast(knIPV4Address_fromStr(addrStr), maybeAddr, ;)
    knIPV4Address addr;
    addr.UintBigEndian=(u32)maybeAddr.value.UInt64;
    kprintf("\e[94mknIPV4Address_fromStr(\e[96m%s\e[94m) -> ", addrStr);
    if(maybeAddr.value.UInt64!=knIPV4Address_fromBytes(a,b,c,d).UintBigEndian){
        kprintf("\e[91m%u.%u.%u.%u\n", 
            (u8)addr.bytes[0], (u8)addr.bytes[1], (u8)addr.bytes[2], (u8)addr.bytes[3]);
        throw("knIPV4Address_fromStr returned wrong value");
    }
    else {
        kprintf("\e[92m%u.%u.%u.%u\n",
            (u8)addr.bytes[0], (u8)addr.bytes[1], (u8)addr.bytes[2], (u8)addr.bytes[3]);
    }
    
}
#define test_knIPV4Address_fromStr(a,b,c,d) __test_knIPV4Address_fromStr(#a"."#b"."#c"."#d, a,b,c,d)

void test_network(){
    optime(__func__,1,({
        kprintf("\e[96m------------[test_network]------------\n");
        tryLast(kn_tryInit(), _mjj64g, ;);
        kprintf("\e[92m\nkerepNetwork initialized");
        
        PRINT_SIZEOF(knIPV4Address);
        PRINT_SIZEOF(knPort);
        PRINT_SIZEOF(knIPV4Endpoint);
        PRINT_SIZEOF(knSocketTCP);
        PRINT_SIZEOF(knSocketUDP);
        PRINT_SIZEOF(knPackage);
        PRINT_SIZEOF(knChannel);

        test_knIPV4Address_fromStr(127,0,0,1);
        test_knIPV4Address_fromStr(34,255,45,0);
        test_knIPV4Address_fromStr(3,3,3,128);
        
        knSocketTCP* socket;
        tryLast(knSocketTCP_open(), m_socket, ;);
        socket=m_socket.value.VoidPtr;
        kprintf("\e[92mTCP socket created\n");

        knIPV4Endpoint localEnd = knIPV4Endpoint_create(IPV4_LOOPBACK, 4444);
        tryLast(knSocketTCP_listen(socket, localEnd), _m81775, ;)
        kprintf("\e[92msocket is listening\n");

        tryLast(knSocketTCP_accept(socket), m_connection, ;);
        knSocketTCP* clientConnection = m_connection.value.VoidPtr;
        kprintf("\e[92mclient connection accepted\n");

        char buf[4096];
        while(true){
            tryLast(knSocketTCP_receive(clientConnection, buf, sizeof(buf)), m_recCount, ;);
            u64 recCount = m_recCount.value.UInt64;
            fwrite(buf, sizeof(char), recCount, stdout);
            // end of received data
            if(recCount != sizeof(buf))
                break;
        }
        kprintf("\e[92mmessage received\n");

        const char msg[] = "pong";
        tryLast(knSocketTCP_send(clientConnection, msg, sizeof(msg)), _mu75q2, ;);
        kprintf("\e[92mmessage sent\n");

        tryLast(knSocketTCP_shutdown(clientConnection, knShutdownType_Both), _m2351, ;);
        tryLast(knSocketTCP_close(clientConnection), _m9776, ;);
        kprintf("\e[92mclient connection closed\n");

        tryLast(knSocketTCP_close(socket), _m676, ;);
        kprintf("\e[92mTCP socket closed\n");

        tryLast(kt_tryDispose(), _m88ag, ;);
        kprintf("\e[92mkerepNetwork disposed\n");
    }));
}