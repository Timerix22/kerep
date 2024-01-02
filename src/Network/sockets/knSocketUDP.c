#include "../network.h"
#include "../socket_impl_includes.h"
ktid_define(knSocketUDP);

Maybe knSocketUDP_open(){
    knSocketUDP* newSocket=malloc(sizeof(knSocketUDP));
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->socketfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(newSocket->socketfd==-1)
        safethrow("can't create UDP socket", free(newSocket));

    return SUCCESS(UniHeapPtr(knSocketUDP, newSocket));
}

Maybe knSocketUDP_shutdown(knSocketUDP* socket, knShutdownType direction){
    try(__kn_StdSocket_shutdown(socket->socketfd, direction), _m875, ;);
    return MaybeNull;
}

Maybe knSocketUDP_close(knSocketUDP* socket){
    try(__kn_StdSocket_close(socket->socketfd), _m875, ;);
    socket->socketfd = 0;
    socket->localEndpoint = knIPV4Endpoint_create(IPV4_NONE, -1);
    return MaybeNull;
}

Maybe knSocketUDP_listen(knSocketUDP* socket, knIPV4Endpoint localEndp);

Maybe knSocketUDP_accept(knSocketUDP* socket);

Maybe knSocketUDP_sendto(knSocketUDP* socket, char* data, u32 dataLength, knIPV4Endpoint destination);

Maybe knSocketUDP_receive(knSocketUDP* socket, char* buffer, u32 bufferLength);
