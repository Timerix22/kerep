#include "../network.h"
#include "../stdSocketHeaders.h"
ktid_define(knSocketUDP);

Maybe knSocketUDP_open(){
    knSocketUDP* newSocket=malloc(sizeof(knSocketUDP));
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->socketfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(newSocket->socketfd==-1)
        safethrow("can't create UDP socket", free(newSocket));

    return SUCCESS(UniHeapPtr(knSocketUDP, newSocket));
}

Maybe knSocketUDP_close(knSocketUDP* socket){
    int result=
#if KN_USE_WINSOCK
        closesocket
#else
        close
#endif
        (socket->socketfd);
    if(result==-1)
        safethrow("can't close socket",;);

    socket->socketfd = 0;
    socket->localEndpoint = knIPV4Endpoint_create(0,0);
    return MaybeNull;
}

Maybe knSocketUDP_listen(knSocketUDP* socket, knIPV4Endpoint localEndp);

Maybe knSocketUDP_accept(knSocketUDP* socket);

Maybe knSocketUDP_sendto(knSocketUDP* socket, char* data, u32 dataLength, knIPV4Endpoint destination);

Maybe knSocketUDP_receive(knSocketUDP* socket, char* buffer, u32 bufferLength);
