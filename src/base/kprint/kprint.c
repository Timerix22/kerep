#include "../base.h"



Maybe __ksprint(uint8 n, uint16 sizes[32], ...){
    for(uint8 i=0; i<n; i++)

}

Maybe __kfprint(FILE* fd, uint8 n, uint16 sizes[32], ...){
    try(__ksprint(n, sizes, ...), str,;);
    if(fputs(str.value.VoidPtr, fd)==EOF)
        safethrow("can't write string to file",;);
    free(str.value.VoidPtr);
}

void __kprint(uint8 n, uint16 sizes[32], ...){
    va_list args;
    va_start(args, sizes);

    va_end(args);
}