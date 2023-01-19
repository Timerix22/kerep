#pragma once

#if __cplusplus
extern "C" {
#endif

#if defined(_WIN64) || defined(_WIN32)
    #define KN_USE_WINSOCK 1
#else 
    #define KN_USE_WINSOCK 0
#endif

#if KN_USE_WINSOCK
    #include <winsock2.h>
    // #include <ws2tcpip.h>
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