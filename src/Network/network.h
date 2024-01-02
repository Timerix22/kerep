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

#if __cplusplus
}
#endif
