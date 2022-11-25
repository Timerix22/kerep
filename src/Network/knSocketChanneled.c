#include "network.h"
#include "stdSocketHeaders.h"

ktid_define(knPacVersion);
ktid_define(knPackage);
ktid_define(knPackageQueueElem);
ktid_define(knChannel);
ktid_define(knSocketChanneled);

Maybe knSocketChanneled_open(knSocketProtocol sockType){
    knSocketChanneled* newSocket=malloc(sizeof(knSocketChanneled));
    newSocket->type=sockType;
    newSocket->channels=NULL;
    newSocket->channelsAmount=0;
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->remoteEndpoint=newSocket->localEndpoint;
    switch(sockType){
        default:
            safethrow("unknown socket type", free(newSocket));
            break;
        case knSocketProtocol_TCP:
            newSocket->socketfd=socket(AF_INET, SOCK_STREAM, 0);
            if(newSocket->socketfd==-1)
                safethrow("can't create TCP socket", free(newSocket));
            break;
        case knSocketProtocol_UDP:
            newSocket->socketfd=socket(AF_INET, SOCK_DGRAM, 0);
            if(newSocket->socketfd==-1)
                safethrow("can't create UDP socket", free(newSocket));
            break;
    }
    return SUCCESS(UniHeapPtr(knSocketChanneled, newSocket));
}

Maybe knSocketChanneled_close(knSocketChanneled* knsocket){
    int rezult=
#if KN_USE_WINSOCK
    closesocket
#else
    close
#endif
    (knsocket->socketfd);
    if(rezult==-1) {
        safethrow("can't close socket",;);
    }
    else return MaybeNull;
}

knChannel* __createChannel(){
    knChannel* ch=malloc(sizeof(knChannel));
    ch->queueStart=NULL;
    return ch;
}

Maybe knSocketChanneled_createChannel(knSocketChanneled* sock){
    if(sock->channelsAmount == 65535) 
        safethrow("max amount of channels",;);
    uint16 channelsAmountPrev=sock->channelsAmount;
    sock->channelsAmount++;
    if(channelsAmountPrev==0) 
        sock->channels=malloc(sizeof(knChannel*));
    else 
        sock->channels=realloc(sock->channels, sock->channelsAmount*sizeof(knChannel*));
    sock->channels[channelsAmountPrev]=__createChannel();
    return SUCCESS(UniUInt64(channelsAmountPrev));
}

/*Maybe knSocketChanneled_bind(knSocketChanneled* sock, knIPV4Endpoint localEndp){
    if(sock->localEndpoint.address.address!=0)
        safethrow("socket is bound already",;);
    struct sockaddr_in addr;
    addr.sin_family=
    bind(sock->socketfd);
    sock->localEndpoint=localEndp;
    return MaybeNull;
}

Maybe knSocketChanneled_connect(knSocketChanneled* sock, knIPV4Endpoint remoteEndp){
    if(sock->remoteEndpoint.address.address!=0)
        safethrow("socket is connected already",;);
    
    sock->remoteEndpoint=remoteEndp;
    return MaybeNull;
}

Maybe knSocketChanneled_accept(knSocketChanneled* sock){

}

Maybe knSocketChanneled_send(knSocketChanneled* sock, uint16 destinationIndex, uint8* data, uint32 dataLength){

}

Maybe knSocketChanneled_recieve(knSocketChanneled* sock, uint16 destinationIndex, uint8* buffer, uint32 bufferLength){

}*/
