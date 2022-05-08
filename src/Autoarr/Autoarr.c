#include "Autoarr.h"

define_Autoarr(uint8)
define_Autoarr(int8)
define_Autoarr(uint16)
define_Autoarr(int16)
define_Autoarr(uint32)
define_Autoarr(int32)
define_Autoarr(uint64)
define_Autoarr(int64)
define_Autoarr(float)
define_Autoarr(double)
define_Autoarr(Unitype)

// right func to clear array of unitype values
void Autoarr_free_Unitype(Autoarr(Unitype)* ar){
    Autoarr_foreach(ar, u,Unitype_free(u));
    Autoarr_free(ar);
}
