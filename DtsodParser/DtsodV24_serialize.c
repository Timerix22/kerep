#include "DtsodV24.h"
#include "../Autoarr/StringBuilder.h"

// 65536 max length!
#define STRB_BC 64
#define STRB_BL 1024

typedef struct SerializeSharedData{
    StringBuilder* sh_builder; 
    uint8 sh_tabs;
} SerializeSharedData;
#define b shared->sh_builder
#define tabs shared->sh_tabs

void __serialize(StringBuilder* _b, uint8 _tabs, Hashtable* dtsod);

#define addc(C) StringBuilder_append_char(b,C)


void __AppendTabs(SerializeSharedData* shared) {
    for (uint8 t = 0; t < tabs; t++)
        addc( '\t');
};
#define AppendTabs() __AppendTabs(shared)

void __AppendValue(SerializeSharedData* shared, Unitype u);
#define AppendValue(UNI) __AppendValue(shared, UNI)
void __AppendValue(SerializeSharedData* shared, Unitype u){
    switch(u.type){
            case Int64:
                StringBuilder_append_int64(b,u.Int64);
                break;
            case UInt64:
                StringBuilder_append_uint64(b,u.UInt64);
                addc('u');
                break;
            case Float64:
                StringBuilder_append_double(b,u.Float64);
                addc('f');
                break;
            case CharPtr:
                addc('"');
                char c;
                while((c=*(char*)(u.VoidPtr++))){
                    if(c=='\"') addc('\\');
                    addc(c);
                }
                addc('"');
                break;
            case Bool:
                StringBuilder_append_cptr(b, u.Bool ? "true" : "false");
                break;
            case Null:
                throw("Null isn't supported in DtsodV24");
                break;
            case AutoarrUnitypePtr:
                addc('[');
                Autoarr_foreach(((Autoarr_Unitype*)(u.VoidPtr)), e, ({
                    addc(' ');
                    AppendValue(e);
                    addc(',');
                }));
                Autoarr_remove(b);
                addc(' ');
                addc(']');
                break;
            case HashtablePtr:
                addc('{');
                addc('\n');
                __serialize(b,tabs+1,u.VoidPtr);
                AppendTabs();
                addc('}');
                break;
            default: dbg((u.type)); throw(ERR_WRONGTYPE); 
    }
};

void __serialize(StringBuilder* _b, uint8 _tabs, Hashtable* dtsod){
    SerializeSharedData _shared={
        .sh_builder=_b, 
        .sh_tabs=_tabs
    };
    SerializeSharedData* shared=&_shared;

    Hashtable_foreach(dtsod, p, ({
        AppendTabs();
        StringBuilder_append_cptr(b,p.key);
        addc(':');
        addc(' ');
        AppendValue(p.value);
        addc(';');
        addc('\n');
    }));
}

char* DtsodV24_serialize(Hashtable* dtsod){
    StringBuilder sb=StringBuilder_create(STRB_BC,STRB_BL);
    __serialize(&sb,0,dtsod);
    char* str=StringBuilder_build(&sb);
    Autoarr_clear((&sb));
    return str;
}
