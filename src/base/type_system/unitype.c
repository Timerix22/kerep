#include "../base.h"

ktId_define(Unitype);
ktId_define(UnitypePtr);

void Unitype_free(Unitype u){
    tryLast(ktDescriptor_get(u.typeId), mType);
    ktDescriptor type=*(ktDescriptor*)mType.value.VoidPtr;
    if(type.freeMembers)
        type.freeMembers(u.VoidPtr);
    if(u.allocatedInHeap)
        free(u.VoidPtr);
}
void __UnitypePtr_free(void* u) { Unitype_free(*(Unitype*)u); }

#define BUFSIZE 64
char* sprintuni(Unitype v){
    char* buf=malloc(BUFSIZE);
    tryLast(ktDescriptor_get(v.typeId), mType);
    ktDescriptor type=*(ktDescriptor*)mType.value.VoidPtr;
    if(v.typeId==ktId_Null)
        sprintf_s(buf, BUFSIZE, "{Null}");
    else if(v.typeId==ktId_Float64)
        sprintf_s(buf, BUFSIZE, "{%s : %lf}", type.name,v.Float64);
    else if(v.typeId==ktId_Bool || v.typeId==ktId_UInt64)
        sprintf_s(buf, BUFSIZE, "{%s : " IFWIN("%llu", "%lu") "}", type.name,v.UInt64);
    else if(v.typeId==ktId_Int64)
        sprintf_s(buf, BUFSIZE, "{%s : " IFWIN("%lld", "%ld") "}", type.name,v.Int64);
    else if(v.typeId==ktId_CharPtr){
        size_t newBUFSIZE=cptr_length(v.VoidPtr) + BUFSIZE/2;
        buf=realloc(buf, newBUFSIZE);
        sprintf_s(buf, BUFSIZE, "{%s : \"%s\"}", type.name,(char*)v.VoidPtr);
    }
    else sprintf_s(buf, BUFSIZE, "{%s : %p}", type.name,v.VoidPtr);
    return buf;
}

void printuni(Unitype v){
    char* s=sprintuni(v);
    fputs(s, stdout);
    free(s);
}