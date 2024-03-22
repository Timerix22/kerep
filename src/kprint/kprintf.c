#include "kprintf.h"
#include "../base/base.h"

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>

WORD unixColorToWin(u8 c){
    switch(c){
        //foreground
        case 30: return 0;
        case 31: return FOREGROUND_RED;
        case 32: return FOREGROUND_GREEN;
        case 33: return FOREGROUND_GREEN | FOREGROUND_RED;
        case 34: return FOREGROUND_BLUE;
        case 35: return FOREGROUND_RED | FOREGROUND_BLUE;
        case 36: return FOREGROUND_BLUE | FOREGROUND_GREEN;
        case 37: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
        case 90: return FOREGROUND_INTENSITY;
        case 91: return FOREGROUND_RED | FOREGROUND_INTENSITY;
        case 92: return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case 93: return FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case 94: return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case 95: return FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
        case 96: return FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case 97: return FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        //background
        case 40: return 0;
        case 41: return BACKGROUND_RED;
        case 42: return BACKGROUND_GREEN;
        case 43: return BACKGROUND_GREEN | BACKGROUND_RED;
        case 44: return BACKGROUND_BLUE;
        case 45: return BACKGROUND_RED | BACKGROUND_BLUE;
        case 46: return BACKGROUND_BLUE | BACKGROUND_GREEN;
        case 47: return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        case 100: return BACKGROUND_INTENSITY;
        case 101: return BACKGROUND_RED | BACKGROUND_INTENSITY;
        case 102: return BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case 103: return BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case 104: return BACKGROUND_BLUE | BACKGROUND_INTENSITY;
        case 105: return BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
        case 106: return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        case 107: return BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
        default: return 0;
    }
}
#endif

i32 _kprintf(const char* format, const i32 args_count, ...){
    va_list vl;
    va_start(vl, args_count);
    i32 i = 0;
    i32 args_left = args_count;
    for(char c = format[i++]; c != 0; c = format[i++]){
        // value format specifiers
        if(c == '%'){
            if(args_left-- == 0)
                return kprintf_NOT_ENOUGH_ARGUMENTS;
                    
            char* argstr = NULL;
            bool l = false;
            c = format[i++];
            format_escape_seq:
            switch (c) {
                case 'u':
                    argstr = toString_u64(
                        l ? va_arg(vl, u64) : va_arg(vl, u32)
                        ,0,0);
                    break;
                case 'i': case 'd':
                    argstr = toString_i64(
                        l ? va_arg(vl, i64) : va_arg(vl, i32)
                        );
                    break;
                case 'f':
                    // f32 is promoted to f64 when passed through '...'
                    argstr = toString_f64(va_arg(vl, f64), toString_float_default_precision,0,0);
                    break;
               case 'l':
                    l = true;
                    if((c = format[i++]))
                        goto format_escape_seq;
                    break;
                case 'p': ;
                    void* phex = va_arg(vl, void*);
                    argstr = toString_hex(&phex,getEndian() == LittleEndian,sizeof(phex),1,0);
                    break;
                case 'x': ;
                    if(l){
                        u64 xhex = va_arg(vl, u64);
                        argstr = toString_hex(&xhex,getEndian() == LittleEndian,sizeof(xhex),0,1);
                    }
                    else {
                        u32 xhex = va_arg(vl, u32);
                        argstr = toString_hex(&xhex,getEndian() == LittleEndian,sizeof(xhex),0,1);
                    }
                    break;
                case 's': ;
                    char* cptr = va_arg(vl,char*);
                    if(!cptr)
                        cptr = "<nullstr>";
                    if(*cptr)
                        fputs(cptr, stdout);
                    break;
                case 'c':
                    putc((char)va_arg(vl,int), stdout);
                    break;
                default:
                    fputs("<INCORRECT FORMAT STRING>", stdout);
                    return kprintf_INVALID_FORMAT;
            }
            if(argstr){
                fputs(argstr, stdout);
                free(argstr);
            }
        }
        
        // escape sequences 
        else if(c == '\e'){
            //////////////////// WINDOWS ////////////////////
            #if defined(_WIN64) || defined(_WIN32)
                if((c = format[i++]) == '['){
                    u8 colorUnix = 0;
                    for(i8 n = 0; n<6 && c != 0; n++){
                        c = format[i++];
                        switch (c){
                            case '0': case '1': case '2': case '3': case '4':
                            case '5': case '6': case '7': case '8': case '9':
                                colorUnix = colorUnix*10+c-'0';
                                break;
                            case 'm': ;
                                WORD colorWin = unixColorToWin(colorUnix);
                                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                SetConsoleTextAttribute(hConsole, colorWin);
                                goto end_iteration;
                            default:
                                goto end_iteration;
                        }
                    }
                }
            ////////////////////// UNIX //////////////////////
            #else
                putc(c,stdout);
            #endif
        }
        
        // common characters 
        else {
            putc(c,stdout);
        }
        #if defined(_WIN64) || defined(_WIN32)
            end_iteration:;
        #endif
    }
    va_end(vl);
    return i;
}


i32 _ksprintf(char* buffer, i32 buffer_size, const char* format, const i32 args_count, ...){
    if(buffer ==  NULL)
        return kprintf_BUFFER_IS_NULL;

    va_list vl;
    va_start(vl, args_count);
    i32 i = 0;
    i32 written = 0;
    i32 args_left = args_count;
    for(char c = format[i++]; c != 0; c = format[i++]){
        // value format specifiers
        if(c == '%'){
            if(args_left-- == 0)
                return kprintf_NOT_ENOUGH_ARGUMENTS;
            
            char* argstr = NULL;
            bool l = false;
            c = format[i++];
            format_escape_seq:
            switch (c) {
                case 'u':
                    argstr = toString_u64(
                        l ? va_arg(vl, u64) : va_arg(vl, u32)
                        ,0,0);
                    break;
                case 'i': case 'd':
                    argstr = toString_i64(
                        l ? va_arg(vl, i64) : va_arg(vl, i32)
                        );
                    break;
                case 'f':
                    // f32 is promoted to f64 when passed through '...'
                    argstr = toString_f64(va_arg(vl, f64), toString_float_default_precision,0,0);
                    break;
               case 'l':
                    l = true;
                    if((c = format[i++]))
                        goto format_escape_seq;
                    break;
                case 'p': ;
                    void* phex = va_arg(vl, void*);
                    argstr = toString_hex(&phex,getEndian() == LittleEndian,sizeof(phex),1,0);
                    break;
                case 'x': ;
                    if(l){
                        u64 xhex = va_arg(vl, u64);
                        argstr = toString_hex(&xhex,getEndian() == LittleEndian,sizeof(xhex),0,1);
                    }
                    else {
                        u32 xhex = va_arg(vl, u32);
                        argstr = toString_hex(&xhex,getEndian() == LittleEndian,sizeof(xhex),0,1);
                    }
                    break;
                case 's': ;
                    char* cptr = va_arg(vl,char*);
                    if(!cptr)
                        cptr = "<nullstr>";
                    if(*cptr){
                        i32 str_length = cptr_length(cptr);
                        if(written + str_length > buffer_size)
                            return kprintf_BUFFER_IS_TOO_SMALL;
                        
                        memcpy(buffer + written, cptr, str_length);
                        written += str_length;
                    }
                    break;
                case 'c': ;
                    char ch = (char)va_arg(vl,int);
                    if(written > buffer_size)
                        return kprintf_BUFFER_IS_TOO_SMALL;
                    
                    buffer[written++] = ch;
                    break;
                default:
                    const char errformat_str[] = "<INCORRECT FORMAT STRING>";
                    if(written + (i32)sizeof(errformat_str) <= buffer_size)
                        memcpy(buffer + written, errformat_str, sizeof(errformat_str));
                    return kprintf_INVALID_FORMAT;
            }
            if(argstr){
                i32 str_length = cptr_length(argstr);
                if(written + str_length > buffer_size)
                    return kprintf_BUFFER_IS_TOO_SMALL;
                
                memcpy(buffer + written, argstr, str_length);
                written += str_length;
                free(argstr);
            }
        }
        
        // common characters 
        else {
            if(written > buffer_size)
                return kprintf_BUFFER_IS_TOO_SMALL;
            
            buffer[written++] = c;
        }
    }
    
    va_end(vl);
    if(written > buffer_size)
        return kprintf_BUFFER_IS_TOO_SMALL;
    buffer[written] = '\0';
    return i;
}
