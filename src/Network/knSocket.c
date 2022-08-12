#include "knSocket.h"
#include "stdSocketHeaders.h"


Maybe knSocket_open(knSockType sockType){
    knSocket* newSocket=malloc(sizeof(knSocket));
    newSocket->type=sockType;
    newSocket->channels=NULL;
    newSocket->channelsAmount=0;
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->remoteEndpoint=newSocket->localEndpoint;
    switch(sockType){
        default:
            safethrow("unknown socket type", free(newSocket));
            break;
        case knSockType_TCP:
            newSocket->socketfd=socket(AF_INET, SOCK_STREAM, 0);
            if(newSocket->socketfd==-1)
                safethrow("can't create TCP socket", free(newSocket));
            break;
        case knSockType_UDP:
            newSocket->socketfd=socket(AF_INET, SOCK_DGRAM, 0);
            if(newSocket->socketfd==-1)
                safethrow("can't create UDP socket", free(newSocket));
            break;
    }
    return SUCCESS(UniPtr(knSocketPtr, newSocket));
}

Maybe knSocket_close(knSocket* knsocket){
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
    else return SUCCESS(UniNull);
}