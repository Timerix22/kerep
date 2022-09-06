/* #include "../base.h"
#include "../../String/StringBuilder.h"

Maybe __next_toString(kprint_format format, void* object){
    // detecting type
    if(!format.typeId) switch((kprint_dataFormat)((uint32)0 | format.dataFmt)){
        case kprint_fmtInt:
        case kprint_fmtHex:
        case kprint_fmtBin: 
            format.typeId=kerepTypeId_Int64; break;
        case kprint_fmtUInt:
            format.typeId=kerepTypeId_UInt64; break;
        case kprint_fmtFloat:
            format.typeId=kerepTypeId_Float64; break;
        case kprint_fmtChar:
            format.typeId=kerepTypeId_Char; break;
        case kprint_fmtString:
            format.typeId=kerepTypeId_CharPtr; break;
        default: 
            safethrow("typeId is not set, can't autodetect type",;);
    }
    try(kerepTypeDescriptor_get(format.typeId),mtd,;);
    kerepTypeDescriptor typeDesc=*(kerepTypeDescriptor*)mtd.value.VoidPtr;
    if(!typeDesc.toString)
        safethrow("type descriptor doesnt have toString() func",;);
    try(typeDesc.toString(object, &format), mStr,;);
    return SUCCESS(mStr.value);
}

Maybe __ksprint(uint8 n, kprint_format* formats, void** objects){
    StringBuilder* strb=StringBuilder_create();
    for(uint8 i=0; i<n; i++){
        try(__next_toString(formats[i], objects[i]),mStr,;);
        StringBuilder_append_cptr(strb, mStr.value.VoidPtr);
    }
    char* rezult=StringBuilder_build(strb).ptr;
    return SUCCESS(UniHeap(kerepTypeId_CharPtr, rezult));
}

Maybe __kfprint(FILE* file, uint8 n, kprint_format* formats, void** objects){
    for(uint8 i=0; i<n; i++){
        try(__next_toString(formats[i], objects[i]),maybeStr,;);
        if(fputs(maybeStr.value.VoidPtr, file)==EOF)
            safethrow("can't write string to file", Unitype_free(maybeStr.value));
        Unitype_free(maybeStr.value);
    }
    return MaybeNull;
}

void __kprint(uint8 n, kprint_format* formats, void** objects){
    for(uint8 i=0; i<n; i++){
        kprint_format fmt=formats[i];
        kprint_setColor(fmt);
         tryLast(__next_toString(fmt, objects[i]),maybeStr);
        if(fputs(maybeStr.value.VoidPtr, stdout)==EOF)\
            throw("can't write string to stdout");
            //, Unitype_free(maybeStr.value)
        Unitype_free(maybeStr.value);
    }
}


void kprint_setColor(kprint_format f){
    if(!f.bgColorChanged | !f.fgColorChanged)
        return;
}




Maybe ksprint_ar(uint32 count, kprint_format format, kerepTypeId typeId, void* array){
    try(kerepTypeDescriptor_get(format.typeId),mtd,;);
    kerepTypeDescriptor typeDesc=*(kerepTypeDescriptor*)mtd.value.VoidPtr;
    if(!typeDesc.toString)
        safethrow("type descriptor doesnt have toString() func",;);
    StringBuilder* strb=StringBuilder_create();
    StringBuilder_append_char(strb, '[');
    for (uint16 e=1; e<count; e++){
        StringBuilder_append_char(strb, ' ');
        try(typeDesc.toString(array+typeDesc.size*e, &format), estr, StringBuilder_free(strb));
        StringBuilder_append_cptr(strb, estr.value.VoidPtr);
        StringBuilder_append_char(strb, ',');
    }
    StringBuilder_rmchar(strb);
    StringBuilder_append_char(strb, ' ');
    StringBuilder_append_char(strb, ']');
} */