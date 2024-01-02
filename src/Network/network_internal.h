#pragma once

#if __cplusplus
extern "C" {
#endif

#include "network.h"
#include "socket_impl_includes.h"

/// shutdown TCP/UDP/other std socket
Maybe __kn_StdSocket_shutdown(i64 socketfd, knShutdownType direction);

/// close TCP/UDP/other std socket
Maybe __kn_StdSocket_close(i64 socketfd);

static inline struct sockaddr_in knIPV4Endpoint_toSockaddr(knIPV4Endpoint end){
    struct sockaddr_in saddr = {0};
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = end.address.UintBigEndian;
    saddr.sin_port = htons(end.port); /* transforms port number to big endian (network order) */
    return saddr;
}

static inline knIPV4Endpoint knIPV4Endpoint_fromSockaddr(struct sockaddr_in saddr_ptr){
    knIPV4Address ipv4 = knIPV4Address_fromU32(saddr_ptr.sin_addr.s_addr);
    u16 port = ntohs(saddr_ptr.sin_port); /* transforms port number to little endian (normal order) */
    return knIPV4Endpoint_create(ipv4, port);
}

#if __cplusplus
}
#endif
