#include "DtsodV24.h"
#include "../String/StringBuilder.h"


typedef struct SerializeSharedData{
    StringBuilder* sh_builder; 
    uint8 sh_tabs;
} SerializeSharedData;
#define b shared->sh_builder
#define tabs shared->sh_tabs

Maybe __serialize(StringBuilder* _b, uint8 _tabs, Hashtable* dtsod);

#define addc(C) StringBuilder_append_char(b,C)


void __AppendTabs(SerializeSharedData* shared) {
    for (uint8 t = 0; t < tabs; t++)
        addc( '\t');
};
#define AppendTabs() __AppendTabs(shared)

Maybe __AppendValue(SerializeSharedData* shared, Unitype u);
#define AppendValue(UNI) __AppendValue(shared, UNI)
Maybe __AppendValue(SerializeSharedData* shared, Unitype u){
    switch(u.type){
        case Int64:
            StringBuilder_append_int64(b,u.Int64);
            break;
        case UInt64:
            StringBuilder_append_uint64(b,u.UInt64);
            addc('u');
            break;
        case Float64:
            StringBuilder_append_float64(b,u.Float64);
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
            safethrow("Null isn't supported in DtsodV24",;);
        case AutoarrUnitypePtr:
            if(Autoarr_length(((Autoarr_Unitype*)(u.VoidPtr)))){
                addc('\n');
                AppendTabs();
                addc('[');
                tabs++;
                Autoarr_foreach(((Autoarr_Unitype*)(u.VoidPtr)), e, ({
                    addc('\n');
                    AppendTabs();
                    try(AppendValue(e),__,;);
                    addc(',');
                }));
                StringBuilder_rmchar(b);
                addc('\n');
                tabs--;
                AppendTabs();
                addc(']');
            }
            else {
                addc('[');
                addc(']');
            }
            break;
        case HashtablePtr:
            // check hashtable is blank
            Hashtable_foreach(((Hashtable*)u.VoidPtr), __, ({
                goto hashtableNotBlank;
                if(__.key); // weird way to disable warning
            }));


            // blank hashtable
            addc('{');
            addc('}');
            break;

            // not blank hashtable
            hashtableNotBlank:
            addc('\n');
            AppendTabs();
            addc('{');
            addc('\n');
            try(__serialize(b,tabs+1,u.VoidPtr),___,;);
            AppendTabs();
            addc('}');
            break;
        default: dbg((u.type)); safethrow(ERR_WRONGTYPE,;);
    }

    return MaybeNull;
};

Maybe __serialize(StringBuilder* _b, uint8 _tabs, Hashtable* dtsod){
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
        try(AppendValue(p.value),__,;);
        addc(';');
        addc('\n');
    }));

    return MaybeNull;
}

Maybe DtsodV24_serialize(Hashtable* dtsod){
    StringBuilder* sb=StringBuilder_create();
    try(__serialize(sb,0,dtsod),__, StringBuilder_free(sb));
    char* str=StringBuilder_build(sb).ptr;
    return SUCCESS(UniPtr(CharPtr, str));
}
