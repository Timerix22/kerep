#include "Autoarr.h"

Autoarr_define(char)
Autoarr_define(bool)
Autoarr_define(float32)
Autoarr_define(float64)
Autoarr_define(uint8)
Autoarr_define(int8)
Autoarr_define(uint16)
Autoarr_define(int16)
Autoarr_define(uint32)
Autoarr_define(int32)
Autoarr_define(uint64)
Autoarr_define(int64)

Autoarr_define(Unitype)

// right func to clear array of unitype values
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr){
    Autoarr_foreach(ar, u,Unitype_free(u));
    if(freePtr) Autoarr_free(ar, freePtr);
}
void ____Autoarr_free_Unitype_(void* ar) { __Autoarr_free_Unitype_((Autoarr(Unitype)*)ar, false); }