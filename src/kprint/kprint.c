#include "../String/StringBuilder.h"
#include "kprint.h"
#include "../base/type_system/base_toString.h"

ktId __typeFromFormat(kprint_format f){
    ktId typeId=kprint_format_ktId(f);
    if(typeId) 
        return typeId;
    switch(kprint_format_dataFormat(f)){
        case kprint_fmtInt:
        case kprint_fmtHex:
        case kprint_fmtBin: 
            return ktId_Int64;
        case kprint_fmtUInt:
            return ktId_UInt64; 
        case kprint_fmtFloat:
            return ktId_Float64; 
        case kprint_fmtChar:
            return ktId_Char; 
        case kprint_fmtString:
            return ktId_CharPtr; 
        default: 
            return -1;
    }
}

Maybe __next_toString(kprint_format f, __kprint_value_union* object){
    // detecting type
    ktId typeId=__typeFromFormat(f);
    if(typeId==-1)
        safethrow("typeId is not set, can't autodetect type",;);
    ktDescriptor typeDesc=ktDescriptor_get(typeId);
    if(!typeDesc.toString)
        safethrow("type descriptor doesnt have toString() func",;);
    return SUCCESS(UniHeap(ktId_CharPtr, typeDesc.toString(object, f)));
}

Maybe __ksprint(uint8 n, kprint_format* formats, __kprint_value_union* objects){
    n/=2;
    StringBuilder* strb=StringBuilder_create();
    for(uint8 i=0; i<n; i++){
        try(__next_toString(formats[i], &objects[i]),mStr,;);
        StringBuilder_append_cptr(strb, mStr.value.VoidPtr);
        Unitype_free(mStr.value);
    }
    char* rezult=StringBuilder_build(strb).ptr;
    return SUCCESS(UniHeap(ktId_CharPtr, rezult));
}

Maybe __kfprint(FILE* file, uint8 n, kprint_format* formats, __kprint_value_union* objects){
    n/=2;
    for(uint8 i=0; i<n; i++){
        try(__next_toString(formats[i], &objects[i]),maybeStr,;);
        if(fputs(maybeStr.value.VoidPtr, file)==EOF)
            safethrow("can't write string to file", Unitype_free(maybeStr.value));
        Unitype_free(maybeStr.value);
    }
    fflush(file);
    return MaybeNull;
}

void __kprint(uint8 n, kprint_format* formats, __kprint_value_union* objects){
    n/=2;
    for(uint8 i=0; i<n; i++){
        kprint_format fmt=formats[i];
        kprint_setColor(fmt);
        tryLast(__next_toString(fmt, &objects[i]),maybeStr);
        if(fputs(maybeStr.value.VoidPtr, stdout)==EOF)\
            throw("can't write string to stdout");
            //, Unitype_free(maybeStr.value)
        Unitype_free(maybeStr.value);
    }
    fflush(stdout);
}

#if defined(_WIN32)|| defined(_WIN64)
#include <windows.h>
#define FOREGROUND_YELLOW FOREGROUND_GREEN | FOREGROUND_RED

DWORD kprint_fgColor_toWin(kprint_fgColor f){ 
    //printf("fg: %x\n", f);
    switch(f){
        case kprint_fgBlack: return 0;
        case kprint_fgDarkRed: return FOREGROUND_RED;
        case kprint_fgDarkGreen: return FOREGROUND_GREEN;
        case kprint_fgDarkYellow: return FOREGROUND_GREEN | FOREGROUND_RED;
        case kprint_fgDarkBlue: return FOREGROUND_BLUE;
        case kprint_fgDarkMagneta: return FOREGROUND_RED | FOREGROUND_BLUE;
        case kprint_fgDarkCyan: return FOREGROUND_BLUE | FOREGROUND_GREEN;
        case kprint_fgGray: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        case kprint_fgDarkGray: return FOREGROUND_INTENSITY;
        case kprint_fgRed: return FOREGROUND_RED | FOREGROUND_INTENSITY;
        case kprint_fgGreen: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case kprint_fgYellow: return FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case kprint_fgBlue: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case kprint_fgMagneta: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case kprint_fgCyan: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case kprint_fgWhite: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        default: throw(ERR_FORMAT);
    }
}

DWORD kprint_bgColor_toWin(kprint_bgColor f){ 
    //printf("bg: %x\n", f);
    switch(f){
        case kprint_bgBlack: return 0;
        case kprint_bgDarkRed: return BACKGROUND_RED;
        case kprint_bgDarkGreen: return BACKGROUND_GREEN;
        case kprint_bgDarkYellow: return BACKGROUND_GREEN | BACKGROUND_RED;
        case kprint_bgDarkBlue: return BACKGROUND_BLUE;
        case kprint_bgDarkMagneta: return BACKGROUND_RED | BACKGROUND_BLUE;
        case kprint_bgDarkCyan: return BACKGROUND_BLUE | BACKGROUND_GREEN;
        case kprint_bgGray: return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        case kprint_bgDarkGray: return BACKGROUND_INTENSITY;
        case kprint_bgRed: return BACKGROUND_RED | BACKGROUND_INTENSITY;
        case kprint_bgGreen: return BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case kprint_bgYellow: return BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case kprint_bgBlue: return BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        case kprint_bgMagneta: return BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case kprint_bgCyan: return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case kprint_bgWhite: return BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        default: throw(ERR_FORMAT);
    }
}

void kprint_setColor(kprint_format f){
    DWORD color=0;
    if(!kprint_format_fgColorChanged(f) & !kprint_format_bgColorChanged(f))
        return;
    if(kprint_format_fgColorChanged(f))
        color+=kprint_fgColor_toWin(kprint_format_fgColor(f));
    if(kprint_format_bgColorChanged(f))
        color+=kprint_bgColor_toWin(kprint_format_bgColor(f));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
void kprint_setColor(kprint_format f){
    if(kprint_format_fgColorChanged(f)){
        uint8 fg=(f&0x0f000000)>>24;
        if(fg<8) fg+=30;
        else fg+=90-8;
        printf("\e[%um", fg);
    }
    if(kprint_format_bgColorChanged(f)){
        uint8 bg=(f&0x00f00000)>>20;
        if(bg<8) bg+=40;
        else bg+=100-8;
        printf("\e[%um", bg);
    }
}
#endif

/* Maybe ksprint_ar(uint32 count, kprint_format format, ktId typeId, void* array){
    ktDescriptor typeDesc=ktDescriptor_get(format.typeId);
    if(!typeDesc.toString)
        safethrow("type descriptor doesnt have toString() func",;);
    StringBuilder* strb=StringBuilder_create();
    StringBuilder_append_char(strb, '[');
    for (uint16 e=1; e<count; e++){
        StringBuilder_append_char(strb, ' ');
        char* elStr=typeDesc.toString(array+typeDesc.size*e, &format);
        StringBuilder_append_cptr(strb, elStr);
        StringBuilder_append_char(strb, ',');
    }
    StringBuilder_rmchar(strb);
    StringBuilder_append_char(strb, ' ');
    StringBuilder_append_char(strb, ']');
} */

void kprintf(char* format, ...){
    va_list vl;
    va_start(vl, format);
    char c;
    while((c=*format++)){
        if(c=='%'){
            c=*format++;
            switch (c) {
                case 'u':
                    toString_uint(va_arg(vl, uint64),0,0);
                    break;
                case 'i':
                    toString_int(va_arg(vl, uint64));
                    break;
                case 'f':
                    toString_float(va_arg(vl, float64),0,0);
                    break;
               /*  case 'l':
                    c=*format++;
                    switch (c) {
                        case 'u':
                            toString_uint(va_arg(vl, uint64),0,0);
                            break;
                        case 'i':
                            toString_int(va_arg(vl, uint64));
                            break;
                        case 'f':
                            toString_float(va_arg(vl, float64),0,0);
                            break;
                        default:
                            throw(ERR_FORMAT);
                    }
                    break; */
                case 'p':
                case 'x':
                    uint64 px=va_arg(vl, uint64);
                    toString_hex(&px,sizeof(px),1,0);
                    break;

                default:
                    throw(ERR_FORMAT);
            }
        } else if(c=='\e'){
            IFWIN(
                ({

                }),
                putc(c,stdout);
            )
        } else {
            putc(c,stdout);
        }
    }
    va_end(vl);
}
