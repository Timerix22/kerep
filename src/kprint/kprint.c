#include "../String/StringBuilder.h"
#include "kprint.h"

ktid __typeFromFormat(kp_fmt f){
    ktid typeId=kp_fmt_ktid(f);
    if(typeId)
        return typeId;
    switch(kp_fmt_dataFormat(f)){
        case kp_i:
        case kp_h:
        case kp_b:
            return ktid_name(i64);
        case kp_u:
            return ktid_name(u64);
        case kp_f:
            return ktid_name(f64);
        case kp_c:
            return ktid_name(char);
        case kp_s:
            return ktid_ptrName(char);
        default:
            return ktid_undefined;
    }
}

Maybe __next_toString(allocator_ptr al, kp_fmt f, void* object){
    // detecting type
    ktid typeId=__typeFromFormat(f);
    if(typeId==ktid_undefined)
        safethrow("typeId is undefined, can't autodetect type",;);

    if(typeId==ktid_ptrName(char))
        object=*(char**)object; // dereferencing char** to char*

    ktDescriptor* type=ktDescriptor_get(typeId);
    if(!type->toString)
        safethrow("type descriptor doesnt have toString() func",;);
    return SUCCESS(UniHeapPtr(char, type->toString(al, object, f)));
}

Maybe check_argsN(u8 n){
    if(n%2 != 0) safethrow("kprint recieved non-even number of arguments",;);
    if(n > 32) safethrow("kprint recieved >32 number of arguments",;);
    return MaybeNull;
}

Maybe __ksprint(allocator_ptr al, u8 n, kp_fmt* formats, __kp_value_union* objects){
    try(check_argsN(n), _,;);
    n/=2;
    StringBuilder _sb;
    StringBuilder* sb=&_sb;
    StringBuilder_construct(sb, al);
    for(u8 i=0; i<n; i++){
        try(__next_toString(al, formats[i], &objects[i]),mStr,;);
        StringBuilder_append_cptr(sb, mStr.value.VoidPtr);
        allocator_free(al, mStr.value.VoidPtr);
    }
    char* rezult=StringBuilder_build(sb).ptr;
    return SUCCESS(UniHeapPtr(char, rezult));
}

Maybe __kfprint(FILE* file, u8 n, kp_fmt* formats, __kp_value_union* objects){
    try(check_argsN(n), _,;);
    n/=2;
    LinearAllocator _al;
    LinearAllocator_construct(&_al, 256);
    allocator_ptr al=&_al.base;
    for(u8 i=0; i<n; i++){
        try(__next_toString(al, formats[i], &objects[i]),maybeStr, LinearAllocator_destruct(&_al));
        if(fputs(maybeStr.value.VoidPtr, file)==EOF)
            safethrow("can't write string to file", LinearAllocator_destruct(&_al));
    }
    fflush(file);
    LinearAllocator_destruct(&_al);
    return MaybeNull;
}

void __kprint(u8 n, kp_fmt* formats, __kp_value_union* objects){
    tryLast(check_argsN(n), _,;);
    n/=2;
    LinearAllocator _al;
    LinearAllocator_construct(&_al, 256);
    allocator_ptr al=&_al.base;
    for(u8 i=0; i<n; i++){
        kp_fmt fmt=formats[i];
        kprint_setColor(fmt);
        tryLast(__next_toString(al, fmt, &objects[i]), maybeStr,
            kprint_setColor(kp_bgBlack|kp_fgGray););
        if(fputs(maybeStr.value.VoidPtr, stdout)==EOF)
            throw("can't write string to stdout");
    }
    fflush(stdout);
    LinearAllocator_destruct(&_al);
}

#if defined(_WIN32)|| defined(_WIN64)
#include <windows.h>
#define FOREGROUND_YELLOW FOREGROUND_GREEN | FOREGROUND_RED

DWORD kp_fgColor_toWin(kp_fgColor f){
    //kprintf("fg: %x\n", f);
    switch(f){
        case kp_fgBlack: return 0;
        case kp_fgRedD: return FOREGROUND_RED;
        case kp_fgGreenD: return FOREGROUND_GREEN;
        case kp_fgYellowD: return FOREGROUND_GREEN | FOREGROUND_RED;
        case kp_fgBlueD: return FOREGROUND_BLUE;
        case kp_fgMagentaD: return FOREGROUND_RED | FOREGROUND_BLUE;
        case kp_fgCyanD: return FOREGROUND_BLUE | FOREGROUND_GREEN;
        case kp_fgGray: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        case kp_fgGrayD: return FOREGROUND_INTENSITY;
        case kp_fgRed: return FOREGROUND_RED | FOREGROUND_INTENSITY;
        case kp_fgGreen: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case kp_fgYellow: return FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case kp_fgBlue: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case kp_fgMagenta: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case kp_fgCyan: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case kp_fgWhite: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        default: throw(ERR_FORMAT);
    }
}

DWORD kp_bgColor_toWin(kp_bgColor f){
    //kprintf("bg: %x\n", f);
    switch(f){
        case kp_bgBlack: return 0;
        case kp_bgRedD: return BACKGROUND_RED;
        case kp_bgGreenD: return BACKGROUND_GREEN;
        case kp_bgYellowD: return BACKGROUND_GREEN | BACKGROUND_RED;
        case kp_bgBlueD: return BACKGROUND_BLUE;
        case kp_bgMagentaD: return BACKGROUND_RED | BACKGROUND_BLUE;
        case kp_bgCyanD: return BACKGROUND_BLUE | BACKGROUND_GREEN;
        case kp_bgGray: return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        case kp_bgGrayD: return BACKGROUND_INTENSITY;
        case kp_bgRed: return BACKGROUND_RED | BACKGROUND_INTENSITY;
        case kp_bgGreen: return BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case kp_bgYellow: return BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case kp_bgBlue: return BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        case kp_bgMagenta: return BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case kp_bgCyan: return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case kp_bgWhite: return BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        default: throw(ERR_FORMAT);
    }
}

void kprint_setColor(kp_fmt f){
    DWORD color=0;
    if(!kp_fmt_fgColorSet(f) & !kp_fmt_bgColorSet(f))
        return;
    if(kp_fmt_fgColorSet(f))
        color+=kp_fgColor_toWin(kp_fmt_fgColor(f));
    if(kp_fmt_bgColorSet(f))
        color+=kp_bgColor_toWin(kp_fmt_bgColor(f));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
void kprint_setColor(kp_fmt f){
    if(kp_fmt_fgColorSet(f)){
        u8 fg=(f&0x0f000000)>>24;
        if(fg<8) fg+=30;
        else fg+=90-8;
        printf("\e[%um", fg);
    }
    if(kp_fmt_bgColorSet(f)){
        u8 bg=(f&0x00f00000)>>20;
        if(bg<8) bg+=40;
        else bg+=100-8;
        printf("\e[%um", bg);
    }
}
#endif

/* Maybe ksprint_ar(u32 count, kp_fmt format, ktid typeId, void* array){
    ktDescriptor* type=ktDescriptor_get(format.typeId);
    if(!type->toString)
        safethrow("type descriptor doesnt have toString() func",;);
    StringBuilder _sb;
    StringBuilder* sb=&_sb;
    StringBuilder_construct(sb, al);
    StringBuilder_append_char(sb, '[');
    for (u16 e=1; e<count; e++){
        StringBuilder_append_char(sb, ' ');
        char* elStr=type->toString(array+type->size*e, &format);
        StringBuilder_append_cptr(sb, elStr);
        StringBuilder_append_char(sb, ',');
    }
    StringBuilder_rmchar(sb);
    StringBuilder_append_char(sb, ' ');
    StringBuilder_append_char(sb, ']');
} */

static const char* _kp_colorNames[16]={
    "black",
    "dark_red",
    "dark_green",
    "dark_yellow",
    "dark_blue",
    "dark_magenta",
    "dark_cyan",
    "gray",
    "dark_gray",
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan",
    "white"
};

char* kp_bgColor_toString(allocator_ptr al, kp_bgColor c){
    u32 color_index=(c&0x00f00000)>>20;
    if(color_index>15) throw(ERR_WRONGINDEX);
    return _kp_colorNames[color_index];
}
char* kp_fgColor_toString(allocator_ptr al, kp_fgColor c){
    u32 color_index=(c&0x00f00000)>>24;
    if(color_index>15) throw(ERR_WRONGINDEX);
    return _kp_colorNames[color_index];
}
