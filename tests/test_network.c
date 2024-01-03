#include "tests.h"
#include "../src/Network/network.h"
#include <pthread.h>

static void __test_knIPV4Address_fromStr(char* addrStr, u8 a, u8 b, u8 c, u8 d){
    tryLast(knIPV4Address_fromStr(addrStr), maybeAddr, ;)
    knIPV4Address addr;
    addr.UintBigEndian=(u32)maybeAddr.value.UInt64;
    kprintf("\e[92mknIPV4Address_fromStr(\e[96m%s\e[92m) -> ", addrStr);
    if(maybeAddr.value.UInt64!=knIPV4Address_fromBytes(a,b,c,d).UintBigEndian){
        kprintf("\e[91m%u.%u.%u.%u\n", 
            (u8)addr.bytes[0], (u8)addr.bytes[1], (u8)addr.bytes[2], (u8)addr.bytes[3]);
        throw("knIPV4Address_fromStr returned wrong value");
    }
    else {
        kprintf("\e[94m%u.%u.%u.%u\n",
            (u8)addr.bytes[0], (u8)addr.bytes[1], (u8)addr.bytes[2], (u8)addr.bytes[3]);
    }
    
}
#define test_knIPV4Address_fromStr(a,b,c,d) __test_knIPV4Address_fromStr(#a"."#b"."#c"."#d, a,b,c,d)

static void test_network_types(){
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
    fflush(stdout);
}

static pthread_mutex_t stdout_mutex = {0};

// thread-safe print
#define kprintf_safe(ARGS...) pthread_mutex_lock(&stdout_mutex); kprintf(ARGS); fflush(stdout); pthread_mutex_unlock(&stdout_mutex);

typedef struct {
    knSocketTCP* socket_client;
    knIPV4Endpoint serverEnd;
} tcp_client_connect_async_data;

void* tcp_client_connect_async(void* _data){
    tcp_client_connect_async_data* data = _data;
    tryLast(knSocketTCP_connect(data->socket_client, data->serverEnd), _m8531,;);
    
    kprintf_safe("\e[92mclient socket connected to server\n");
    free(data);
    return NULL;
}

static void test_tcp(){
    kprintf("\e[96m----------[test_network/tcp]----------\n");
    knIPV4Endpoint serverEnd = knIPV4Endpoint_create(knIPV4Address_LOOPBACK, 4444);
    knSocketTCP *socket_server, *clientConnection, *socket_client;
    // server
    {
        tryLast(knSocketTCP_open(true), m_socketS, ;);
        socket_server=m_socketS.value.VoidPtr;
        kprintf("\e[92mTCP server socket created\n");    
        
        tryLast(knSocketTCP_bindAndListen(socket_server, serverEnd), _m81775, ;)
        kprintf("\e[92mserver socket is listening\n");
    }
    // client
    {
        tryLast(knSocketTCP_open(false), m_socketC, ;);
        socket_client=m_socketC.value.VoidPtr;
        kprintf("\e[92mTCP client socket created\n");
        
        tcp_client_connect_async_data* client_connection_data = malloc(sizeof(tcp_client_connect_async_data));
        client_connection_data->serverEnd = serverEnd;
        client_connection_data->socket_client = socket_client;
        pthread_t client_connection_thread;
        fflush(stdout);
        if(pthread_create(&client_connection_thread, NULL, tcp_client_connect_async, client_connection_data) != 0)
            throw("can't create client connection thread");
        if(pthread_detach(client_connection_thread) != 0)
            throw("can't detatch client connection thread");
    }
    // server
    {
        tryLast(knSocketTCP_accept(socket_server), m_connection, ;);
        clientConnection = m_connection.value.VoidPtr;
        kprintf_safe("\e[92mserver accepted client connection\n");
    }
    // client
    {
        const char client_msg[] = "ping";
        tryLast(knSocketTCP_send(socket_client, client_msg, sizeof(client_msg)), _mu75q2, ;);
        kprintf("\e[92mmessage sent to server\n\e[94m");
    }
    // server
    {
        char received_client_msg[32];
        tryLast(knSocketTCP_receive(clientConnection, received_client_msg, sizeof(received_client_msg)), m_recCount, ;);
        u64 recCount = m_recCount.value.UInt64;
        fwrite(received_client_msg, sizeof(char), recCount, stdout);
        fputc('\n', stdout);
        if(!cptr_equals(received_client_msg, "ping"))
            throw("received_client_msg != \"ping\"");
        kprintf("\e[92mmessage received by server\n");

        const char server_msg[] = "pong";
        tryLast(knSocketTCP_send(clientConnection, server_msg, sizeof(server_msg)), _mu75q2, ;);
        kprintf("\e[92mmessage sent to client\n\e[94m");
        fflush(stdout);
    }
    // client
    {
        char received_server_msg[32];
        tryLast(knSocketTCP_receive(socket_client, received_server_msg, sizeof(received_server_msg)), m_recCount, ;);
        u64 recCount = m_recCount.value.UInt64;
        fwrite(received_server_msg, sizeof(char), recCount, stdout);
        fputc('\n', stdout);
        if(!cptr_equals(received_server_msg, "pong"))
            throw("received_server_msg != \"pong\"");
        kprintf("\e[92mmessage received by client\n");
        fflush(stdout);
    }
    // server
    {
        tryLast(knSocketTCP_shutdown(clientConnection, knShutdownType_Both), _m2351, ;);
        tryLast(knSocketTCP_close(clientConnection), _m9776, ;);
        kprintf("\e[92mclient connection closed\n");

        tryLast(knSocketTCP_close(socket_server), _m676, ;);
        kprintf("\e[92mTCP server socket closed\n");
    }
    // client
    {
        tryLast(knSocketTCP_close(socket_client), _m964, ;);
        kprintf("\e[92mTCP client socket closed\n");
    }
    fflush(stdout);
}

void test_udp(){
    kprintf("\e[96m----------[test_network/udp]----------\n");
    knIPV4Endpoint serverEnd = knIPV4Endpoint_create(knIPV4Address_LOOPBACK, 4444);
    knSocketUDP *socket_server, *socket_client;
    // server
    {
        tryLast(knSocketUDP_open(true), m_socketS, ;);
        socket_server=m_socketS.value.VoidPtr;
        kprintf("\e[92mUDP server socket created\n");    
        
        tryLast(knSocketUDP_bind(socket_server, serverEnd), _m81775, ;)
        kprintf("\e[92mserver socket is bound\n");
    }
    // client
    {
        tryLast(knSocketUDP_open(false), m_socketC, ;);
        socket_client=m_socketC.value.VoidPtr;
        kprintf("\e[92mUDP client socket created\n");
        
        const char client_msg[] = "ping";
        tryLast(knSocketUDP_sendTo(socket_client, client_msg, sizeof(client_msg), serverEnd), _mu75q2, ;);
        kprintf("\e[92mmessage sent to server\n\e[94m");
    }
    // server
    {
        char received_client_msg[32];
        knIPV4Endpoint clientEnd = knIPV4Endpoint_INVALID;
        tryLast(knSocketUDP_receiveAny(socket_server, received_client_msg, sizeof(received_client_msg), &clientEnd), m_recCount, ;);
        u64 recCount = m_recCount.value.UInt64;
        fwrite(received_client_msg, sizeof(char), recCount, stdout);
        fputc('\n', stdout);
        if(!cptr_equals(received_client_msg, "ping"))
            throw("received_client_msg != \"ping\"");
        kprintf("\e[92mmessage received by server\n");

        const char server_msg[] = "pong";
        tryLast(knSocketUDP_sendTo(socket_server, server_msg, sizeof(server_msg), clientEnd), _mu75q2, ;);
        char* adrstr = knIPV4Endpoint_toString(&clientEnd);
        kprintf("\e[92mmessage sent to client (%s)\n\e[94m", adrstr);
        free(adrstr);
        fflush(stdout);
    }
    // client
    {
        char received_server_msg[32];
        knIPV4Endpoint senderEnd = knIPV4Endpoint_INVALID;
        tryLast(knSocketUDP_receiveAny(socket_client, received_server_msg, sizeof(received_server_msg), &senderEnd), m_recCount, ;);
        u64 recCount = m_recCount.value.UInt64;
        fwrite(received_server_msg, sizeof(char), recCount, stdout);
        fputc('\n', stdout);
        if(!cptr_equals(received_server_msg, "pong"))
            throw("received_server_msg != \"pong\"");
        char* adrstr = knIPV4Endpoint_toString(&serverEnd);
        kprintf("\e[92mmessage received by client (%s)\n", adrstr);
        free(adrstr);
        fflush(stdout);
    }
    // server
    {
        tryLast(knSocketUDP_close(socket_server), _m676, ;);
        kprintf("\e[92mUDP server socket closed\n");
    }
    // client
    {
        tryLast(knSocketUDP_close(socket_client), _m964, ;);
        kprintf("\e[92mUDP client socket closed\n");
    }
    fflush(stdout);
}

void test_network(){
    optime(__func__,1,({
        kprintf("\e[96m------------[test_network]------------\n");
        tryLast(kn_tryInit(), _mjj64g, ;);
        kprintf("\e[92mkerepNetwork initialized\n");
        
        if(pthread_mutex_init(&stdout_mutex, NULL) != 0)
            throw("can't init mutex");

        test_network_types();
        test_tcp();
        test_udp();

        if(pthread_mutex_destroy(&stdout_mutex) != 0)
            throw("can't destroy mutex");

        tryLast(kt_tryDispose(), _m88ag, ;);
        kprintf("\e[92mkerepNetwork disposed\n");
    }));
}