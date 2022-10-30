#include "filesystem.h"

char* __path_concat(uint16 n, char* prev_part, ...){
    char** parts=(char**)malloc(n*sizeof(char*));
    uint32* lengths=malloc(n*sizeof(uint32));
    uint32 totalLength=0;

    // reading args from va_list
    va_list vl;
    va_start(vl, prev_part);
    for(uint16 i=0; i<n; i++){
        char* part=va_arg(vl,char*);
        int16 length=cptr_length(part);
        parts[i]=part;
        lengths[i]=length;
        totalLength+=length;
    }
    va_end(vl);

    // allocating memory for output value
    char* totality=malloc(totalLength+1);
    const char* output=totality;
    totality[totalLength]=0;
    
    // copying content of all strings to rezult
    uint16 k=0;
    for(; k<n-1; k++){
        memcopy(parts[k], totality, lengths[k]);
        totality+=lengths[k];
        *totality=path_sep;
        totality++;
    }
    memcopy(parts[k], totality, lengths[k]);

    free(parts);
    free(lengths);
    return output;
}
