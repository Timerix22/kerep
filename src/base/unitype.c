#include "unitype.h"

void Unitype_free(Unitype u){
    kerepTypeDescriptor type=typeDescriptor_get(u.typeId);
    if(type.free_members)
        type.free_members(u.VoidPtr);
    if(u.allocatedInHeap)
        free(u.VoidPtr);
}
void __UnitypePtr_free(Unitype* u) { Unitype_free(&u); }