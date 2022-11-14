#include "kprintf.h"
#include "../base/base.h"
#include "../base/type_system/base_toString.h"

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>

WORD unixColorToWin(uint8 c){
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

void kprintf(const char* format, ...){
    va_list vl;
    va_start(vl, format);
    uint32 i=0;
    for(char c=format[i++]; c!=0; c=format[i++]){
        if(c=='%'){
            char* argstr=NULL;
            c=format[i++];
            format_escape_seq:
            switch (c) {
                case 'u':
                    argstr=toString_uint(va_arg(vl, uint64),0,0);
                    break;
                case 'i': case 'd':
                    argstr=toString_int(va_arg(vl, uint64));
                    break;
                case 'f':
                    argstr=toString_float(va_arg(vl, float64),0,0);
                    break;
               case 'l':
                    if((c=format[i++]))
                        goto format_escape_seq;
                    break;
                    // switch (c) {
                    //     case 'u':
                    //         argstr=toString_uint(va_arg(vl, uint64),0,0);
                    //         break;
                    //     case 'i':
                    //         argstr=toString_int(va_arg(vl, uint64));
                    //         break;
                    //     case 'f':
                    //         argstr=toString_float(va_arg(vl, float64),0,0);
                    //         break;
                    //     default:
                    //         throw(ERR_FORMAT);
                    // }
                    // break;
                case 'p':
                case 'x':
                    uint64 px=va_arg(vl, uint64);
                    argstr=toString_hex(&px,sizeof(px),1,0);
                    break;
                case 's':
                    char* cptr=va_arg(vl,char*);
                    if(!cptr)
                        cptr="<nullstr>";
                    if(*cptr)
                        fputs(cptr, stdout);
                    break;
                case 'c':
                    argstr=malloc(2);
                    argstr[0]=(char)va_arg(vl,int);
                    argstr[1]=0;
                    break;
                default:
                    putc('\n',stdout);
                    putc('<',stdout);
                    putc(c,stdout);
                    putc('>',stdout);
                    throw(ERR_FORMAT);
            }
            if(argstr){
                fputs(argstr, stdout);
                free(argstr);
            }
        } else if(c=='\e'){
            IFWIN(
                ({
                    if((c=format[i++])=='['){
                        uint8 colorUnix=0;
                        for(int8 n=0; n<6 && c!=0; n++){
                            c=format[i++];
                            switch (c){
                                case '0': case '1': case '2': case '3': case '4':
                                case '5': case '6': case '7': case '8': case '9':
                                    colorUnix=colorUnix*10+c-'0';
                                    break;
                                case 'm':
                                    WORD colorWin=unixColorToWin(colorUnix);
                                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                    SetConsoleTextAttribute(hConsole, colorWin);
                                    goto end_iteration;
                                default:
                                    goto end_iteration;
                            }
                        }
                    }
                }),
                putc(c,stdout);
            );
        } else {
            putc(c,stdout);
        }
        #if defined(_WIN64) || defined(_WIN32)
        end_iteration:
        #endif
    }
    va_end(vl);
}