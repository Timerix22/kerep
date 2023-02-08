#include "filesystem.h"

char* __path_concat(uint16 n, ...){
    char** parts=(char**)malloc(n*sizeof(char*));
    uint32* lengths=malloc(n*sizeof(uint32));
    uint32 totalLength=0;

    // reading args from va_list
    va_list vl;
    va_start(vl, n);
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

char* path_fixSeparators(char* path){
    char* pathCopy=cptr_copy(path);
    char c;
    while((c=*pathCopy)){
        if(c==path_notSep)
            *pathCopy=path_sep;
        pathCopy++;
    }
    return pathCopy;
}

Maybe path_throwIfEscapes(char* path){
    if(cptr_contains(path,".."))
        safethrow(cptr_concat("path <",path,"> uses <..>, that's not allowed"),);
    return MaybeNull;
}

char* path_parentDir(char* dir){
    throw(ERR_NOTIMPLEMENTED);
    char* copy=cptr_copy(dir);
    uint32 length=cptr_length(copy);
    int i=cptr_lastIndexOfChar(copy,path_sep);
    if(i==length-1){
        copy[length-1]=0;
        i=cptr_lastIndexOfChar(copy,path_sep);
    }
    if(i==-1){
        free(copy);
        copy=malloc(3);
        copy[0]='.';
        copy[1]=path_sep;
        copy[2]=0;
    }
    return copy;
}
