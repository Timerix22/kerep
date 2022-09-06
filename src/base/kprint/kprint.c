#include "../base.h"
#include "../../String/StringBuilder.h"

Maybe __next_toString(uint16 size, va_list args, StringBuilder* strb){
    kprint_format format=va_arg(args, kprint_format);
    if(!format.dataFmtSet)
        safethrow("format is not set", StringBuilder_free(strb));
    // detecting type
    if(!format.typeId) switch(format.dataFmt){
        case kprint_fmtInt:
        case kprint_fmtHex:
        case kprint_fmtBin:
            switch(size){
                case 1: format.typeId=kerepTypeId_Int8; break;
                case 2: format.typeId=kerepTypeId_Int16; break;
                case 4: format.typeId=kerepTypeId_Int32; break;
                case 8: format.typeId=kerepTypeId_Int64; break;
                default: safethrow("typeId is not set, can't autodetect type", StringBuilder_free(strb));
            }
            break;
        case kprint_fmtUInt:
            switch(size){
                case 1: format.typeId=kerepTypeId_UInt8; break;
                case 2: format.typeId=kerepTypeId_UInt16; break;
                case 4: format.typeId=kerepTypeId_UInt32; break;
                case 8: format.typeId=kerepTypeId_UInt64; break;
                default: safethrow("typeId is not set, can't autodetect type", StringBuilder_free(strb));
            }
            break;
        case kprint_fmtFloat:
            switch(size){
                case 4: format.typeId=kerepTypeId_Float32; break;
                case 8: format.typeId=kerepTypeId_Float64; break;
                default: safethrow("typeId is not set, can't autodetect type", StringBuilder_free(strb));
            }
            break;
        case kprint_fmtChar:
            if(size!=1)
                safethrow("typeId is not set, can't autodetect type", StringBuilder_free(strb));
            format.typeId=kerepTypeId_Char;
            break;
        case kprint_fmtString:
            switch(size){
                case sizeof(char*): format.typeId=kerepTypeId_CharPtr; break;
                case sizeof(string): format.typeId=kerepTypeId_string; break;
                default: safethrow("typeId is not set, can't autodetect type", StringBuilder_free(strb));
            }
            break;
        default: 
            safethrow("typeId is not set, can't autodetect type", StringBuilder_free(strb));
    }
    try(kerepTypeDescriptor_get(format.typeId),mtd,StringBuilder_free(strb));
    kerepTypeDescriptor typeDesc=*(kerepTypeDescriptor*)mtd.value.VoidPtr;
    if(size<typeDesc.size)
        safethrow("sizeof(arg) < arg_typeDesc.size",StringBuilder_free(strb));
    if(!typeDesc.toString){
            }
    else {
        void* obj=va_arg(args, size);
        // value is single variable
        if(size==typeDesc.size){
            
        }
        // value is array
        else{
            if(size%typeDesc.size!=0)
                safethrow("array size is not corresponding to type size",StringBuilder_free(strb));
            StringBuilder_append_char(strb, '[');
            uint16 count=size/typeDesc.size;
            for (uint16 e=1; e<count; e++){
                StringBuilder_append_char(strb, ' ');
                try(typeDesc.toString(obj, &format), estr, StringBuilder_free(strb));
                StringBuilder_append_cptr(strb, estr.value.VoidPtr);
                StringBuilder_append_char(strb, ',');
            }
            StringBuilder_rmchar(strb);
            StringBuilder_append_char(strb, ' ');
            StringBuilder_append_char(strb, ']');
        }
    }
}

Maybe __kvsprint(uint8 n, uint16* sizes, va_list args){
    StringBuilder* strb=StringBuilder_create();
    for(uint8 i=0; i<n; i++){
        try(__next_toString(sizes[i], args, strb),_,;);
    }
    char* rezult=StringBuilder_build(strb).ptr;
    return SUCCESS(UniHeap(kerepTypeId_CharPtr, rezult));
}

Maybe __ksprint(uint8 n, uint16 sizes[32], ...){
    va_list args;
    va_start(args, sizes);
    try(__kvsprint(n, sizes, args),rezult,;);
    va_end(args);
    return rezult;
}

Maybe __kfprint(FILE* fd, uint8 n, uint16 sizes[32], ...){
    va_list args;
    va_start(args, sizes);
    try(__kvsprint(n, sizes, args),maybeStr,;);
    if(fputs(maybeStr.value.VoidPtr, fd)==EOF)
        safethrow("can't write string to file",;);
    free(maybeStr.value.VoidPtr);
    va_end(args);
    return MaybeNull;
}

void __kprint(uint8 n, uint16 sizes[32], ...){
}