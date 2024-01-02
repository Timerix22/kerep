#include "network_internal.h"

Maybe kn_tryInit(){
#if _WIN32
    // Initialize Winsock
    WSADATA wsaData = {0};
    int startupResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (startupResult != 0) {
        char* errcode = toString_hex(&startupResult, sizeof(int), 0 , 1, 1);
        safethrow(cptr_concat("WSAStartup failed with error: ", errcode), ;);
    }
#endif
    return SUCCESS(UniNull);
}

Maybe kt_tryDispose(){
#if _WIN32
    // Deinitialize Winsock
    int cleanupResult = WSACleanup();
    if (cleanupResult != 0) {
        char* errcode = toString_hex(&cleanupResult, sizeof(int), 0, 1, 1);
        safethrow(cptr_concat("WSAStartup failed with error: ", errcode), ;);
    }
#endif
    return SUCCESS(UniNull);
}


Maybe __kn_StdSocket_shutdown(i64 socketfd, knShutdownType direction){
    if(shutdown(socketfd, (int)direction) == -1)
        safethrow("can't shutdown socket", ;);
    return MaybeNull;
}

Maybe __kn_StdSocket_close(i64 socketfd){
#if KN_USE_WINSOCK
    if(closesocket(socketfd) == -1)
#else
    if(close(socketfd) == -1)
#endif
        safethrow("can't close socket", ;);

    return MaybeNull;
}
