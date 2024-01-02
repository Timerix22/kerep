#include "../network_internal.h"

ktid_define(knSocketUDP);

Maybe knSocketUDP_open(bool allowReuse){
    knSocketUDP* newSocket=malloc(sizeof(knSocketUDP));
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->socketfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(newSocket->socketfd==-1)
        safethrow("can't create socket", free(newSocket));
    
    // set value of REUSEADDR socket option
    int opt_val = allowReuse;
    if(setsockopt(newSocket->socketfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt_val, sizeof(opt_val)) != 0)
        safethrow("can't set socket options", free(newSocket));
    
    return SUCCESS(UniHeapPtr(knSocketUDP, newSocket));
}

Maybe knSocketUDP_shutdown(knSocketUDP* socket, knShutdownType direction){
    try(__kn_StdSocket_shutdown(socket->socketfd, direction), _m875, ;);
    return MaybeNull;
}

Maybe knSocketUDP_close(knSocketUDP* socket){
    try(__kn_StdSocket_close(socket->socketfd), _m875, ;);
    free(socket);
    return MaybeNull;
}

Maybe knSocketUDP_bind(knSocketUDP* socket, knIPV4Endpoint localEndp){
    struct sockaddr_in servaddr = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = localEndp.address.UintBigEndian,
        .sin_port = htons(localEndp.port) /* transforms port to big endian */
    };
    
    if(bind(socket->socketfd, (void*)&servaddr, sizeof(servaddr)) != 0)
        safethrow("socket bind failed", ;);

    socket->localEndpoint = localEndp;
    return MaybeNull;
}

Maybe knSocketUDP_sendTo(knSocketUDP* socket, char* buffer, u32 dataLength, knIPV4Endpoint destEnd){
    struct sockaddr_in dest_saddr = knIPV4Endpoint_toSockaddr(destEnd);
    u32 sentCount = sendto(
            socket->socketfd,
            buffer,
            dataLength, 
            0, 
            (struct sockaddr*)&dest_saddr,
            sizeof(struct sockaddr_in)
        );
    
    if(sentCount != dataLength) {
        safethrow(
            cptr_concat("can't send ", toString_u64(dataLength-sentCount,0,0),
                " bytes out of ", toString_u64(dataLength,0,0)
            ),
            ;);
    }

    return MaybeNull;
}

Maybe knSocketUDP_receiveAny(knSocketUDP* socket, char* buffer, u32 bufferLength, knIPV4Endpoint* senderEnd){
    struct sockaddr_in remote_saddr = {0};
    u64 remote_saddr_size = sizeof(remote_saddr);
    int receivedCount = recvfrom(
        socket->socketfd,
        buffer,
        bufferLength,
        0,
        (struct sockaddr*)&remote_saddr,
        (void*)&remote_saddr_size
    );

    if(receivedCount == -1 || receivedCount == 0)
        safethrow("can't receive data from socket", ;)

    *senderEnd = knIPV4Endpoint_fromSockaddr(remote_saddr);
    return SUCCESS(UniUInt64(receivedCount));
}
