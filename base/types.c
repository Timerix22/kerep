#include "types.h"
#include "errors.h"
#include "../Autoarr/Autoarr.h"
#include "../Hashtable/Hashtable.h"
#include "../SearchTree/SearchTree.h"

const char* my_type_name(my_type t){
    switch (t) {
        case Null: return "Null";
        case Float64: return "Float64";
        case Float32: return "Float32";
        case Bool: return "Bool";
        case Char: return "Char";
        case Int8: return "Int8";
        case UInt8: return "UInt8";
        case Int16: return "Int16";
        case UInt16: return "UInt16";
        case Int32: return "Int32";
        case UInt32: return "UInt32";
        case Int64: return "Int64";
        case UInt64: return "UInt64";
        case Int8Ptr: return "Int8Ptr";
        case UInt8Ptr: return "UInt8Ptr";
        case Int16Ptr: return "Int16Ptr";
        case UInt16Ptr: return "UInt16Ptr";
        case Int32Ptr: return "Int32Ptr";
        case UInt32Ptr: return "UInt32Ptr";
        case Int64Ptr: return "Int64Ptr";
        case UInt64Ptr: return "UInt64Ptr";
        case CharPtr: return "CharPtr";
        case STNodePtr: return "STNodePtr";
        case HashtablePtr: return "HashtablePtr";
        case UniversalType: return "Unitype";
        case AutoarrInt8Ptr: return "AutoarrInt8Ptr";
        case AutoarrUInt8Ptr: return "AutoarrUInt8Ptr";
        case AutoarrInt16Ptr: return "AutoarrInt16Ptr";
        case AutoarrUInt16Ptr: return "AutoarrUInt16Ptr";
        case AutoarrInt32Ptr: return "AutoarrInt32Ptr";
        case AutoarrUInt32Ptr: return "AutoarrUInt32Ptr";
        case AutoarrInt64Ptr: return "AutoarrInt64Ptr";
        case AutoarrUInt64Ptr: return "AutoarrUInt64Ptr";
        case AutoarrUnitypePtr: return "AutoarrUnitypePtr";
        case AutoarrKVPairPtr: return "AutoarrKVPairPtr";
        default: throw(ERR_WRONGTYPE); return "ERROR";
    }
}

//frees VoidPtr value or does nothing if type isn't pointer
void Unitype_free(Unitype u){
    switch (u.type) {
        case Null: 
        case Float32:
        case Float64: 
        case Char: 
        case Bool: 
        case Int8: 
        case UInt8: 
        case Int16: 
        case UInt16:
        case Int32: 
        case UInt32: 
        case Int64:
        case UInt64: 
            break;
        case Int8Ptr: 
        case UInt8Ptr:
        case Int16Ptr: 
        case UInt16Ptr: 
        case Int32Ptr: 
        case UInt32Ptr: 
        case Int64Ptr: 
        case UInt64Ptr: 
        case CharPtr: 
            free(u.VoidPtr);
            break;
        case HashtablePtr: 
            Hashtable_free(u.VoidPtr);
            break;
        case STNodePtr: 
            STNode_free(u.VoidPtr);
            break;
        case AutoarrInt8Ptr: 
            Autoarr_clear(((Autoarr(int8)*)u.VoidPtr));
            break;
        case AutoarrUInt8Ptr:
            Autoarr_clear(((Autoarr(uint8)*)u.VoidPtr));
            break;
        case AutoarrInt16Ptr: 
            Autoarr_clear(((Autoarr(int16)*)u.VoidPtr));
            break;
        case AutoarrUInt16Ptr: 
            Autoarr_clear(((Autoarr(uint16)*)u.VoidPtr));
            break;
        case AutoarrInt32Ptr: 
            Autoarr_clear(((Autoarr(int32)*)u.VoidPtr));
            break;
        case AutoarrUInt32Ptr: 
            Autoarr_clear(((Autoarr(uint32)*)u.VoidPtr));
            break;
        case AutoarrInt64Ptr: 
            Autoarr_clear(((Autoarr(int64)*)u.VoidPtr));
            break;
        case AutoarrUInt64Ptr: 
            Autoarr_clear(((Autoarr(uint64)*)u.VoidPtr));
            break;
        case AutoarrUnitypePtr:
            Autoarr_Unitype_clear(u.VoidPtr);
            free((Autoarr(Unitype)*)u.VoidPtr);
            break;
        case AutoarrKVPairPtr: 
            Autoarr_KeyValuePair_clear(u.VoidPtr);
            free((Autoarr(KeyValuePair)*)u.VoidPtr);
            break;
        default: throw(ERR_WRONGTYPE);
    }
}

#define SPRINT_BUFSIZE 64
void sprintuni(char* buf,Unitype v){
    IFWIN(
        switch (v.type) {
            case Null: sprintf_s(buf, SPRINT_BUFSIZE, "{Null}");break;
            case Float64: sprintf_s(buf, SPRINT_BUFSIZE, "{%s : %lf}", my_type_name(v.type),v.Float64);break;
            case Bool:
            case UInt64: sprintf_s(buf, SPRINT_BUFSIZE, "{%s : %lu}", my_type_name(v.type),v.UInt64);break;
            case Int64: sprintf_s(buf, SPRINT_BUFSIZE, "{%s : %ld}", my_type_name(v.type),v.Int64);break;
            case CharPtr: sprintf_s(buf, SPRINT_BUFSIZE, "{%s : \"%s\"}", my_type_name(v.type),(char*)v.VoidPtr);break;
            default: sprintf_s(buf, SPRINT_BUFSIZE, "{%s : %p}", my_type_name(v.type),v.VoidPtr);break;
        },
        switch (v.type) {
            case Null: sprintf(buf, "{Null}");break;
            case Float64: sprintf(buf, "{%s : %lf}", my_type_name(v.type),v.Float64);break;
            case Bool:
            case UInt64: sprintf(buf, "{%s : %lu}", my_type_name(v.type),v.UInt64);break;
            case Int64: sprintf(buf, "{%s : %ld}", my_type_name(v.type),v.Int64);break;
            case CharPtr: sprintf(buf, "{%s : \"%s\"}", my_type_name(v.type),(char*)v.VoidPtr);break;
            default: sprintf(buf, "{%s : %p}", my_type_name(v.type),v.VoidPtr);break;
        }
    );
}

void printuni(Unitype v){
    char* s=malloc(SPRINT_BUFSIZE);
    sprintuni(s,v);
    fputs(s, stdout);
    free(s);
}