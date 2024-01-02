#include "network.h"
#include "stdSocketHeaders.h"

Maybe kn_tryInit(){
#if _WIN32
    // Initialize Winsock
    WSADATA wsaData = {0};
    int startupResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (startupResult != 0) {
        char* errcode = toString_hex(&startupResult, sizeof(int), 0 , 1, 1);
        safethrow(cptr_concat("WSAStartup failed with error: ", errcode), ;);
    }
    return SUCCESS(UniNull);
#endif
}

Maybe kt_tryDispose(){
#if _WIN32
    // Deinitialize Winsock
    int cleanupResult = WSACleanup();
    if (cleanupResult != 0) {
        char* errcode = toString_hex(&cleanupResult, sizeof(int), 0, 1, 1);
        safethrow(cptr_concat("WSAStartup failed with error: ", errcode), ;);
    }
    return SUCCESS(UniNull);
#endif
}
