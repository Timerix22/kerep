#include "../network.h"
#include "../stdSocketHeaders.h"
ktid_define(knSocketTCP);

Maybe knSocketTCP_open(){
    knSocketTCP* newSocket=malloc(sizeof(knSocketTCP));
    newSocket->localEndpoint=knIPV4Endpoint_create({.u32=INADDR_NONE},0);
    newSocket->remoteEndpoint=newSocket->localEndpoint;
    newSocket->socketfd=socket(AF_INET, SOCK_STREAM, 0);
    if(newSocket->socketfd==-1)
        safethrow("can't create TCP socket", free(newSocket));
        
    return SUCCESS(UniHeapPtr(knSocketTCP, newSocket));
}

Maybe knSocketTCP_close(knSocketTCP* socket){
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
    socket->localEndpoint = knIPV4Endpoint_create(0, 0);
    socket->remoteEndpoint = knIPV4Endpoint_create(0, 0);
    return MaybeNull;
}

Maybe knSocketTCP_listen(knSocketTCP* socket, knIPV4Endpoint localEndp){
    if(socket->localEndpoint.address.u32!=INADDR_NONE)
        safethrow("socket is bound already",;);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(localEndp.address.u32);
    servaddr.sin_port = htons(localEndp.port);
    if(bind(socket->socketfd,(struct sockaddr*)&servaddr, sizeof(servaddr)) !=0)
        safethrow("socket bind failed",;);
    socket->localEndpoint=localEndp;
    if(listen(socket->socketfd, 256) !=0)
        safethrow("socket listen failed",;);
    return MaybeNull;
}

Maybe knSocketTCP_connect(knSocketTCP* socket, knIPV4Endpoint remoteEndp){
    if(socket->remoteEndpoint.address.u32!=0)
        safethrow("socket is connected already",;);
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = htonl(remoteEndp.address.u32);
    servaddr.sin_port = htons(remoteEndp.port);
    if(connect(socket->socketfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) !=0)
        safethrow("socket connect failed",;);
    socket->remoteEndpoint=remoteEndp;
    return MaybeNull;
}

Maybe knSocketTCP_accept(knSocketTCP* socket){
    accept(socket->socketfd, )
}

Maybe knSocketTCP_send(knSocketTCP* socket, char* data, u32 dataLength){

}

Maybe knSocketTCP_receive(knSocketTCP* socket, char* buffer, u32 bufferLength);
