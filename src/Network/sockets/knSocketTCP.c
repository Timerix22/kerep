#include "../network.h"
#include "../stdSocketHeaders.h"
ktid_define(knSocketTCP);

///@return Maybe<knSocketTCP*> new socket
Maybe knSocketTCP_open(){
    knSocketTCP* newSocket=malloc(sizeof(knSocketTCP));
    newSocket->localEndpoint=knIPV4Endpoint_create({.u32=INADDR_NONE},0);
    newSocket->remoteEndpoint=newSocket->localEndpoint;
    newSocket->socketfd=socket(AF_INET, SOCK_STREAM, 0);
    if(newSocket->socketfd==-1)
        safethrow("can't create TCP socket", free(newSocket));
    return SUCCESS(UniHeapPtr(knSocketTCP, newSocket));
}

///@return Maybe<void> error or nothing
Maybe knSocketTCP_close(knSocketTCP* socket){
    int rezult=
#if KN_USE_WINSOCK
    closesocket
#else
    close
#endif
    (socket->socketfd);
    if(rezult==-1) {
        safethrow("can't close socket",;);
    }
    else return MaybeNull;
}

///sets socket local endpoint
///@return Maybe<void> error or nothing
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

///sets socket remote endpoint
///@return Maybe<void> error or nothing
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

///@return Maybe<knSocketTCP*> new socket connected to client
Maybe knSocketTCP_accept(knSocketTCP* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocketTCP_send(knSocketTCP* socket, char* data, u32 dataLength);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<u64> recieved bytes amount
Maybe knSocketTCP_recieve(knSocketTCP* socket, char* buffer, u32 bufferLength);
