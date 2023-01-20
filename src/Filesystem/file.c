#include "file.h"
#include "../String/StringBuilder.h"

ktid_define(File);

char* FileOpenMode_toStr(FileOpenMode m){
    char* p;
    switch(m){
        case FileOpenMode_Read: p="rb"; break;
        case FileOpenMode_Write: p="wb"; break;
        case FileOpenMode_Append: p="ab"; break;
        case FileOpenMode_ReadWrite: p="wb+"; break;
        case FileOpenMode_ReadAppend: p="ab+"; break;
        default:
            dbg(m);
            throw(ERR_UNEXPECTEDVAL);
    }
    return p;
}

Maybe file_open(FilePath path, FileOpenMode mode){
    File* file=fopen(path, FileOpenMode_toStr(mode));
    if(!file)
        safethrow(cptr_concat("can't open file ", (char*)path),;);
    return SUCCESS(UniHeapPtr(File,file));
}

Maybe file_close(File* file){
    if(!file)
        safethrow(ERR_NULLPTR,;);
    if(fclose(file))
        safethrow(ERR_IO,;);
    return MaybeNull;
}

#define ioWriteCheck()\
    if(rezult==EOF)\
        safethrow(ERR_IO_EOF,;);\
    if(rezult!=0)\
        safethrow(ERR_IO,;);

Maybe file_writeChar(File* file, char byte){
    int rezult=fputc(byte, file);
    ioWriteCheck();
    return MaybeNull;
}

Maybe file_writeBuffer(File* file, char* buffer, uint64 length){
    int rezult=0;
    for(uint64 i=0; i<length && !rezult; i++)
        rezult=fputc(buffer[i], file);
    ioWriteCheck();
    return MaybeNull;
}

Maybe file_writeCptr(File* file, char* cptr){
    int rezult=fputs(cptr, file);
    ioWriteCheck();
    return MaybeNull;
}


Maybe file_readChar(File* file){
    int rezult=fgetc(file);
    if(feof(file)) safethrow(ERR_IO_EOF,;);
    if(ferror(file)) safethrow(ERR_IO,;);
    return SUCCESS(UniUInt64(rezult));
}

Maybe file_readBuffer(File* file, char* buffer, uint64 length){
    int rezult=0;
    uint64 i=0;
    for(; i<length && rezult!=EOF; i++){
        rezult=fgetc(file);
        buffer[i]=(char)rezult;
    }
    if(ferror(file)) safethrow(ERR_IO,;);
    return SUCCESS(UniUInt64(i));
}

Maybe file_readAll(File* file, char** allBytes){
    int rezult=0;
    char buffer[256];
    string bufStr={.ptr=buffer, .length=sizeof(buffer)};
    StringBuilder* sb=StringBuilder_create();
    uint64 i=0;
    while(true){
        rezult=fgetc(file);
        if(rezult==EOF){
            if(ferror(file)) 
                safethrow(ERR_IO,; StringBuilder_free(sb));
            break;
        }
        buffer[i%sizeof(buffer)]=(char)rezult;
        i++;
        if(!(i%sizeof(buffer)))
            StringBuilder_append_string(sb,bufStr);
    }
    bufStr.length=i%sizeof(buffer);
    if(bufStr.length!=0)
        StringBuilder_append_string(sb,bufStr);
    string str=StringBuilder_build(sb);
    *allBytes=str.ptr;
    // i dont know how can it happen, but if it will have, it will be very dangerous
    if(i!=str.length) 
        throw(ERR_UNEXPECTEDVAL);
    return SUCCESS(UniUInt64(i));
}
