#include "Autoarr.h"

Autoarr_define(Unitype)

u32 free_calls=0;

// right func to clean array of unitype values
void __Autoarr_Unitype_free_fixed(Autoarr(Unitype)* ar, bool freePtr){
    Autoarr_foreach(ar, u,Unitype_free(u));
    __Autoarr_Unitype_free_g(ar, freePtr);
    free_calls++;
    kprintf("free_calls: %u\n", free_calls);
}
void ____Autoarr_Unitype_free_fixed(void* ar) { 
    __Autoarr_Unitype_free_fixed((Autoarr(Unitype)*)ar, false); 
}
