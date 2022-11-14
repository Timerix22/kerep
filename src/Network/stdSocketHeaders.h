#pragma once

#if __cplusplus
extern "C" {
#endif

#if KN_USE_WINSOCK
    #include <winsock2.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
#endif

#if __cplusplus
}
#endif