#include "../network.h"
#include "../stdSocketHeaders.h"
ktid_define(knSocketUDP);

///@return Maybe<knSocketUDP*> new socket
Maybe knSocketUDP_open(){
    knSocketUDP* newSocket=malloc(sizeof(knSocketUDP));
    newSocket->localEndpoint=knIPV4Endpoint_create(knIPV4Address_fromBytes(0,0,0,0),0);
    newSocket->socketfd=socket(AF_INET, SOCK_DGRAM, 0);
    if(newSocket->socketfd==-1)
        safethrow("can't create UDP socket", free(newSocket));
    return SUCCESS(UniHeapPtr(knSocketUDP, newSocket));
}

///start listening at local endpoint
///@return Maybe<void> error or nothing
Maybe knSocketUDP_listen(knSocketUDP* socket, knIPV4Endpoint localEndp);

///@return Maybe<knSocketUDP*> new socket connected to client
Maybe knSocketUDP_accept(knSocketUDP* socket);

///@param dataLength 0-4294967295
///@return Maybe<void>
Maybe knSocketUDP_sendto(knSocketUDP* socket, char* data, uint32 dataLength, knIPV4Endpoint destination);

///@param buffer buffer for recieving data
///@param bufferLength 0-4294967295
///@return Maybe<uint64> recieved bytes amount
Maybe knSocketUDP_recieve(knSocketUDP* socket, char* buffer, uint32 bufferLength);
