#pragma once

#if __cplusplus
extern "C" {
#endif

#include "std.h"
#include "types.h"

typedef enum err_t {
    SUCCESS, // not an error 
    ERR_MAXLENGTH, ERR_WRONGTYPE, ERR_WRONGINDEX, ERR_NOTIMPLEMENTED, ERR_NULLPTR, ERR_ENDOFSTR
} err_t;

char* errname(err_t err);

char* __genErrMsg(const char* errmsg, const char* srcfile, int line, const char* funcname);
char* __extendErrMsg(const char* errmsg, const char* srcfile, int line, const char* funcname);

typedef struct Maybe{
    Unitype value;
    char* errmsg;
} Maybe;
static const Maybe MaybeNull={.value.type=Null, .value.VoidPtr=NULL,.errmsg=NULL};

void Maybe_free(Maybe e);
void printMaybe(Maybe e);


#define SUCCESS(REZLT) (Maybe){.errmsg=NULL, .value=REZLT}

#define __RETURN_EXCEPTION(ERRMSG) return (Maybe){.errmsg=ERRMSG, .value=UniNull}

#define __EXIT(ERRMSG) ({ printf("\e[91m%s\e[0m \n", ERRMSG); exit(128); })

char* __doNothing(char* a);
char* __unknownErr( );

#define __stringify_err(E) _Generic(\
    (E),\
    char*: __doNothing,\
    int: errname,\
    default: __unknownErr\
)(E)

#define throw(E) __EXIT(((char*)__genErrMsg((__stringify_err(E)), __FILE__,__LINE__,__func__)))
#define safethrow(E) __RETURN_EXCEPTION(((char*)__genErrMsg((__stringify_err(E)), __FILE__,__LINE__,__func__)))


#define try(_funcCall, _rezult) Maybe _rezult=_funcCall; if(_rezult.errmsg){\
        _rezult.errmsg=__extendErrMsg(_rezult.errmsg, __FILE__,__LINE__,__func__);\
        return _rezult;\
    }else 

#define tryLast(_funcCall, _rezult) Maybe _rezult=_funcCall; if(_rezult.errmsg){\
        _rezult.errmsg=__extendErrMsg(_rezult.errmsg, __FILE__,__LINE__,__func__);\
        __EXIT(_rezult.errmsg);\
    }else 

#if __cplusplus
}
#endif