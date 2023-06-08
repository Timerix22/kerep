#include "filesystem.h"

char* __path_concat(allocator_ptr al, u32 n, ...){
    char** parts=(char**)allocator_alloc(al, n*sizeof(char*));
    u32* lengths=allocator_alloc(al, n*sizeof(u32));
    u32 totalLength=0;

    // reading args from va_list
    va_list vl;
    va_start(vl, n);
    for(u16 i=0; i<n; i++){
        char* part=va_arg(vl,char*);
        i16 length=cptr_length(part);
        parts[i]=part;
        lengths[i]=length;
        totalLength+=length;
    }
    va_end(vl);

    // allocating memory for output value
    char* totality=allocator_alloc(al, totalLength+1);
    const char* output=totality;
    totality[totalLength]=0;
    
    // copying content of all strings to rezult
    u16 k=0;
    for(; k<n-1; k++){
        memcpy(totality, parts[k], lengths[k]);
        totality+=lengths[k];
        *totality=path_sep;
        totality++;
    }
    memcpy(totality, parts[k], lengths[k]);

    allocator_free(al, lengths);
    allocator_free(al, parts);
    return output;
}

char* path_fixSeparators(allocator_ptr al, const char* path){
    char* pathCopy=cptr_copy(al, path);
    char c;
    while((c=*pathCopy)){
        if(c==path_notSep)
            *pathCopy=path_sep;
        pathCopy++;
    }
    return pathCopy;
}

Maybe path_throwIfEscapes(const char* path){
    LinearAllocator _al; LinearAllocator_construct(&_al, 128);
    allocator_ptr al=&_al.base;
    if(cptr_contains(path,".."))
        safethrow(cptr_concat(al, "path <",path,"> uses <..>, that's not allowed"),
            LinearAllocator_destruct(&_al));
    LinearAllocator_destruct(&_al);
    return MaybeNull;
}

char* path_parentDir(allocator_ptr al, char* dir){
    char* copy=cptr_copy(al, dir);
    i32 length=cptr_length(copy);
    i32 i=cptr_lastIndexOfChar(copy,path_sep);
    if(i!=-1 && i==length-1){
        copy[length-1]=0;
        i=cptr_lastIndexOfChar(copy,path_sep);
    }
    if(i==-1){
        allocator_free(al, copy);
        copy=allocator_alloc(al, 2);
        copy[0]='.';
        copy[1]=0;
    }
    return copy;
}


char* path_basename(allocator_ptr al, char* path, bool with_extension){
    i32 nameIndex=cptr_lastIndexOfChar(path, path_sep)+1;
    string rezult=string_fromCptr(path+nameIndex);
    if(!with_extension){
        i32 extIndex=cptr_lastIndexOfChar(rezult.ptr, '.');
        if(extIndex!=0 && extIndex!=-1)
            rezult.length=extIndex;
    }
    return string_extract(al, rezult);
}
