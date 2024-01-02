#include "../network.h"
#include "../stdSocketHeaders.h"

ktid_define(knPackage);
ktid_define(knPackageQueueElem);
ktid_define(knChannel);
ktid_define(knSocketChanneled);

Maybe knSocketChanneled_open(){
    knSocketChanneled* newSocket=malloc(sizeof(knSocketChanneled));
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->remoteEndpoint=newSocket->localEndpoint;
    newSocket->channels=NULL;
    newSocket->channelsAmount=0;
    return SUCCESS(UniHeapPtr(knSocketChanneled, newSocket));
}

Maybe knSocketChanneled_close(knSocketChanneled* socket){
    int result=
#if KN_USE_WINSOCK
    closesocket
#else
    close
#endif
    (socket->socketfd);
    if(result==-1) {
        safethrow("can't close socket",;);
    }
    else return MaybeNull;
}

knChannel* __createChannel(){
    knChannel* ch=malloc(sizeof(knChannel));
    ch->queueStart=NULL;
    return ch;
}

Maybe knSocketChanneled_createChannel(knSocketChanneled* socket){
    if(socket->channelsAmount == 65535) 
        safethrow("max amount of channels",;);
    u16 channelsAmountPrev=socket->channelsAmount;
    socket->channelsAmount++;
    if(channelsAmountPrev==0) 
        socket->channels=malloc(sizeof(knChannel*));
    else 
        socket->channels=realloc(socket->channels, socket->channelsAmount*sizeof(knChannel*));
    socket->channels[channelsAmountPrev]=__createChannel();
    return SUCCESS(UniUInt64(channelsAmountPrev));
}

Maybe knSocketChanneled_listen(knSocketChanneled* socket, knIPV4Endpoint localEndp);

Maybe knSocketChanneled_connect(knSocketChanneled* socket, knIPV4Endpoint remoteEndp);

Maybe knSocketChanneled_accept(knSocketChanneled* socket);

Maybe knSocketChanneled_send(knSocketChanneled* socket, u16 destinationIndex, u8* data, u32 dataLength);

Maybe knSocketChanneled_receive(knSocketChanneled* socket, u16 destinationIndex, u8* buffer, u32 bufferLength);