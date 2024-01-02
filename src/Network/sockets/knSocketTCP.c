#include "../network.h"
#include "../socket_impl_includes.h"
ktid_define(knSocketTCP);

Maybe knSocketTCP_open(bool allowReuse){
    knSocketTCP* newSocket=malloc(sizeof(knSocketTCP));
    newSocket->localEndpoint=knIPV4Endpoint_create(IPV4_NONE,0);
    newSocket->remoteEndpoint=knIPV4Endpoint_create(IPV4_NONE,0);
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

Maybe knSocketTCP_listen(knSocketTCP* socket, knIPV4Endpoint localEndp){
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = localEndp.address.UintBigEndian;
    servaddr.sin_port = htons(localEndp.port);
    int r = bind(socket->socketfd,(struct sockaddr*)&servaddr, sizeof(servaddr));
    if(r != 0)
        safethrow("socket bind failed",;);
    socket->localEndpoint=localEndp;

    r = listen(socket->socketfd, 1024);
    if(r != 0)
        safethrow("socket listen failed",;);
    return MaybeNull;
}

Maybe knSocketTCP_connect(knSocketTCP* socket, knIPV4Endpoint remoteEndp){
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = remoteEndp.address.UintBigEndian;
    servaddr.sin_port = htons(remoteEndp.port);
    if(connect(socket->socketfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) !=0)
        safethrow("socket connect failed",;);
    socket->remoteEndpoint=remoteEndp;
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
    clientSocket->remoteEndpoint = knIPV4Endpoint_create(
        knIPV4Address_fromU32(remoteAddr.sin_addr.s_addr), 
        remoteAddr.sin_port);
    return SUCCESS(UniHeapPtr(knSocketTCP, clientSocket));
}

Maybe knSocketTCP_send(knSocketTCP* socket, char* data, u32 dataLength){
    u32 sentTotal = 0;
    while(sentTotal < dataLength){
        int sentCount = send(socket->socketfd, data+sentTotal, dataLength-sentTotal, 0);
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
