#include "Autoarr.h"

Autoarr_define(uint8)
Autoarr_define(int8)
Autoarr_define(uint16)
Autoarr_define(int16)
Autoarr_define(uint32);
Autoarr_define(int32);
Autoarr_define(uint64);
Autoarr_define(int64);
Autoarr_define(float);
Autoarr_define(double);
Autoarr_define(Unitype);

// right func to clear array of unitype values
void Autoarr_free_Unitype(Autoarr(Unitype)* ar){
    Autoarr_foreach(ar, u,Unitype_free(u));
    Autoarr_free(ar);
}
