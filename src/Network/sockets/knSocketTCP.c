#include "../network_internal.h"

void __knSocketTCP_close(void* p){ knSocketTCP_close(p); }

kt_define(knSocketTCP, __knSocketTCP_close, NULL);

Maybe knSocketTCP_open(bool allowReuse){
    knSocketTCP* newSocket=malloc(sizeof(knSocketTCP));
    newSocket->localEndpoint=knIPV4Endpoint_INVALID;
    newSocket->remoteEndpoint=knIPV4Endpoint_INVALID;
    newSocket->socketfd=socket(AF_INET, SOCK_STREAM, 0);
    if(newSocket->socketfd==-1 || newSocket->socketfd == ~0)
        safethrow("can't create socket", free(newSocket));
    
    // set value of REUSEADDR socket option
    int opt_val = allowReuse;
    if(setsockopt(newSocket->socketfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt_val, sizeof(opt_val)) != 0)
        safethrow("can't set socket options", free(newSocket));
    
    return SUCCESS(UniHeapPtr(knSocketTCP, newSocket));
}

Maybe knSocketTCP_shutdown(knSocketTCP* socket, knShutdownType direction){
    try(__kn_StdSocket_shutdown(socket->socketfd, direction), _m875, ;);
    return MaybeNull;
}

Maybe knSocketTCP_close(knSocketTCP* socket){
    try(__kn_StdSocket_close(socket->socketfd), _m875, ;);
    free(socket);
    return MaybeNull;
}

Maybe knSocketTCP_bindAndListen(knSocketTCP* socket, knIPV4Endpoint localEndp){
    struct sockaddr_in servaddr = knIPV4Endpoint_toSockaddr(localEndp);
    
    if(bind(socket->socketfd, (void*)&servaddr, sizeof(servaddr)) != 0)
        safethrow("socket bind failed", ;);

    if(listen(socket->socketfd, 1024) != 0)
        safethrow("socket listen failed", ;);

    socket->localEndpoint = localEndp;
    return MaybeNull;
}

Maybe knSocketTCP_connect(knSocketTCP* socket, knIPV4Endpoint remoteEnd){
    struct sockaddr_in servaddr = knIPV4Endpoint_toSockaddr(remoteEnd);

    if(connect(socket->socketfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) !=0)
        safethrow("socket connect failed",;);
        
    socket->remoteEndpoint=remoteEnd;
    return MaybeNull;
}

Maybe knSocketTCP_accept(knSocketTCP* socket){
    struct sockaddr_in remoteAddr = {0};
    u64 remoteAddrSize = sizeof(remoteAddr);

    i64 client_fd = accept(socket->socketfd, (struct sockaddr*)&remoteAddr, (void*)&remoteAddrSize);
    if(client_fd == -1 || client_fd == ~0)
        safethrow("can't accept client connection", ;);
    
    // if accept() didn't set remoteAddr for some reason
    if(remoteAddr.sin_addr.s_addr == 0 && remoteAddr.sin_port == 0 && remoteAddr.sin_family == 0){
        if(getpeername(client_fd, (struct sockaddr*)&remoteAddr, (void*)&remoteAddrSize) != 0)
            safethrow("can't get connected client address", ;);
    }

    knSocketTCP* clientSocket = malloc(sizeof(knSocketTCP));
    clientSocket->socketfd = client_fd;
    clientSocket->localEndpoint = socket->localEndpoint;
    clientSocket->remoteEndpoint = knIPV4Endpoint_fromSockaddr(remoteAddr);
    return SUCCESS(UniHeapPtr(knSocketTCP, clientSocket));
}

Maybe knSocketTCP_send(knSocketTCP* socket, char* buffer, u32 dataLength){
    u32 sentTotal = 0;
    while(sentTotal < dataLength){
        int sentCount = send(socket->socketfd, buffer+sentTotal, dataLength-sentTotal, 0);
        if(sentCount == -1){
            safethrow(
                cptr_concat("can't send ", toString_u64(dataLength-sentTotal,0,0),
                    " bytes out of ", toString_u64(dataLength,0,0),
                    " at index ", toString_u64(sentTotal,0,0)
                ),
                ;);
        }
        sentTotal += sentCount;
    }

    return MaybeNull;
}

Maybe knSocketTCP_receive(knSocketTCP* socket, char* buffer, u32 bufferLength){
    int receivedCount = recv(socket->socketfd, buffer, bufferLength, 0);
    if(receivedCount == -1 || receivedCount == 0)
        safethrow("can't receive data from socket", ;)

    return SUCCESS(UniUInt64(receivedCount));
}
