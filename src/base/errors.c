#include "std.h"
#include "errors.h"
#include "cptr.h"

char* errname(ErrorId err){
    switch(err){
        case SUCCESS: return "SUCCESS";
        case ERR_MAXLENGTH: return "ERR_MAXLENGTH";
        case ERR_WRONGTYPE: return "ERR_WRONGTYPE";
        case ERR_WRONGINDEX: return "ERR_WRONGINDEX";
        case ERR_NOTIMPLEMENTED: return "ERR_NOTIMPLEMENTED";
        case ERR_NULLPTR: return "ERR_NULLPTR";
        case ERR_ENDOFSTR: return "ERR_ENDOFSTR";
        case ERR_KEYNOTFOUND: return "ERR_KEYNOTFOUND";
        case ERR_FORMAT: return "ERR_FORMAT";
        default: return "UNKNOWN_ERROR";
    }
}

#define ERRMSG_MAXLENGTH 1024

char* __genErrMsg(const char* errmsg, const char* srcfile, int line, const char* funcname){
    size_t bufsize=ERRMSG_MAXLENGTH;
    char* rezult=malloc(bufsize);
    IFMSC(
        sprintf_s(rezult,bufsize,"[%s:%d] %s() throwed error: %s",srcfile,line,funcname,errmsg),
        sprintf(rezult,"[%s:%d] %s() throwed error: %s",srcfile,line,funcname,errmsg)
    );
    return rezult;
}

char* __extendErrMsg(const char* errmsg, const char* srcfile, int line, const char* funcname){
    size_t bufsize=cptr_length(errmsg)+ERRMSG_MAXLENGTH;
    char* rezult=malloc(bufsize);
    IFMSC(
        sprintf_s(rezult,bufsize,"%s\n \\___[%s:%d] %s()",errmsg,srcfile,line,funcname),
        sprintf(rezult,"%s\n \\___[%s:%d] %s()",errmsg,srcfile,line,funcname)
    );
    free(errmsg);
    return rezult;
}

void Maybe_free(Maybe e){
    free(e.errmsg);
    Unitype_free(e.value);
}

void printMaybe(Maybe e){
    if(e.errmsg) printf("%s\n",e.errmsg);
    else printuni(e.value);
}

char* __doNothing(char* a) {return a;}

char* __unknownErr() {return "UNKNOWN ERROR";}
