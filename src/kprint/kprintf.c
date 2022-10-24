#include "kprintf.h"
#include "../base/base.h"
#include "../base/type_system/base_toString.h"

void kprintf(const char* format, ...){
    va_list vl;
    va_start(vl, format);
    char c;
    while((c=*format++)){
        if(c=='%'){
            char* argstr=NULL;
            c=*format++;
            format_escape_seq:
            switch (c) {
                case 'u':
                    argstr=toString_uint(va_arg(vl, uint64),0,0);
                    break;
                case 'i':
                    argstr=toString_int(va_arg(vl, uint64));
                    break;
                case 'f':
                    argstr=toString_float(va_arg(vl, float64),0,0);
                    break;
               case 'l':
                    c=*format++;
                    goto format_escape_seq;
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
                    fputs(va_arg(vl,char*), stdout);
                    break;
                case 'c':
                    argstr=malloc(2);
                    argstr[0]=va_arg(vl,char);
                    argstr[1]=0;
                    break;
                default:
                    throw(ERR_FORMAT);
            }
            if(argstr){
                fputs(argstr, stdout);
                free(argstr);
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
