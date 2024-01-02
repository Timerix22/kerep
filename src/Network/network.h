#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"

#include "network_types.h"
#include "sockets/knSocketTCP.h"
#include "sockets/knSocketUDP.h"
#include "sockets/knSocketChanneled.h"

Maybe kn_tryInit();
Maybe kt_tryDispose();



/*       INTERNAL       */

/// shutdown TCP/UDP/other std socket
Maybe __kn_StdSocket_shutdown(i64 socketfd, knShutdownType direction);
/// close TCP/UDP/other std socket
Maybe __kn_StdSocket_close(i64 socketfd);

#if __cplusplus
}
#endif
