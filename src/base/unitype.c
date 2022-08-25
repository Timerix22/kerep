#include "base.h"

kerepTypeId_define(kerepTypeId_Unitype);
kerepTypeId_define(kerepTypeId_UnitypePtr);

void Unitype_free(Unitype u){
    kerepTypeDescriptor type=kerepTypeDescriptor_get(u.typeId);
    if(type.free_members)
        type.free_members(u.VoidPtr);
    if(u.allocatedInHeap)
        free(u.VoidPtr);
}
void __UnitypePtr_free(void* u) { Unitype_free(*(Unitype*)u); }

#define BUFSIZE 64
char* sprintuni(Unitype v){
    char* buf=malloc(BUFSIZE);
    kerepTypeDescriptor type=kerepTypeDescriptor_get(v.typeId);
    if(v.typeId==kerepTypeId_Null)
        sprintf_s(buf, BUFSIZE, "{Null}");
    else if(v.typeId==kerepTypeId_Float64)
        sprintf_s(buf, BUFSIZE, "{%s ) %lf}", type.name,v.Float64);
    else if(v.typeId==kerepTypeId_Bool || v.typeId==kerepTypeId_UInt64)
        sprintf_s(buf, BUFSIZE, "{%s ) " IFWIN("%llu", "%lu") "}", type.name,v.UInt64);
    else if(v.typeId==kerepTypeId_Int64)
        sprintf_s(buf, BUFSIZE, "{%s ) " IFWIN("%lld", "%ld") "}", type.name,v.Int64);
    else if(v.typeId==kerepTypeId_CharPtr){
        size_t newBUFSIZE=cptr_length(v.VoidPtr) + BUFSIZE/2;
        buf=realloc(buf, newBUFSIZE);
        sprintf_s(buf, BUFSIZE, "{%s ) \"%s\"}", type.name,(char*)v.VoidPtr);
    }
    else sprintf_s(buf, BUFSIZE, "{%s ) %p}", type.name,v.VoidPtr);
    return buf;
}

void printuni(Unitype v){
    char* s=sprintuni(v);
    fputs(s, stdout);
    free(s);
}