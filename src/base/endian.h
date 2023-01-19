#include "std.h"

PACK_ENUM(Endian,
    UnknownEndian=0,
    LittleEndian=1,
    BigEndian=2
);

Endian getEndian();
