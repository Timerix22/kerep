#include "Autoarr.h"

Autoarr_define(Unitype);

// right func to clear array of unitype values
void __Autoarr_free_Unitype_(Autoarr(Unitype)* ar, bool freePtr){
    Autoarr_foreach(ar, u,Unitype_free(u));
    __Autoarr_free_Unitype(ar, freePtr);
}
void ____Autoarr_free_Unitype_(void* ar) { 
    __Autoarr_free_Unitype_((Autoarr(Unitype)*)ar, false); 
}
