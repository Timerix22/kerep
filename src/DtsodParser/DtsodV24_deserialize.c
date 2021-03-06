#include "DtsodV24.h"
#include "../String/StringBuilder.h"

#define ARR_BC 64
#define ARR_BL 1024


typedef struct DeserializeSharedData{
    const char* sh_text_first;
    char* sh_text;
    bool sh_partOfDollarList;
    bool sh_calledRecursively;
} DeserializeSharedData;

#define text shared->sh_text
#define partOfDollarList shared->sh_partOfDollarList
#define calledRecursively shared->sh_calledRecursively


// special func for throwing error messages about wrong characters in deserializing text
Maybe ERROR_WRONGCHAR(const char c, char* _text, char* text_first, const char* srcfile, int line, const char* funcname){
    char errBuf[68];
    for(uint8 n=0; n<sizeof(errBuf);n++)
        errBuf[n]='\0';
    char* errText=_text-32;
    uint8 cplace=32;
    if(errText<text_first) {
        cplace=_text-text_first;
        errText=text_first;
    }
    uint8 i=0;
    for(; i<cplace; i++){
        // writes 32 chars before the wrongchar
        errBuf[i]=errText[i];
    }
    //prints wrongchar in braces
    errBuf[i++]='<';
    errBuf[i++]=c;
    errBuf[i++]='>';
    for(; i<cplace+3+32; i++){
        // writes 32 chars after the wrongchar
        char _c=errText[i-2];
        errBuf[i]=_c;
        if(!_c) break;
    }
    char errmsg[1024];
    IFMSC(
        sprintf_s(errmsg,1024, "unexpected <%c> at:\n"
                        "  \"%s\"\n"
                        "\\___[%s:%d] %s()", 
                        c,errBuf, srcfile,line,funcname),
        sprintf(errmsg, "unexpected <%c> at:\n"
                        "  \"%s\"\n"
                        " \\___[%s:%d] %s()", 
                        c,errBuf, srcfile,line,funcname)
    );
    safethrow(errmsg,;);
}
#define safethrow_wrongchar(C, freeMem) { freeMem; return ERROR_WRONGCHAR(C, text, shared->sh_text_first, __FILE__,__LINE__,__func__); }


Maybe __SkipComment(DeserializeSharedData* shared) {
    char c;

    while ((c=*++text) != '\n')
        if (!c) safethrow(ERR_ENDOFSTR,;);

    return MaybeNull;
}
#define SkipComment() __SkipComment(shared)

Maybe __ReadName(DeserializeSharedData* shared){
    char c;
    string nameStr={text+1,0};

    while ((c=*++text)) switch (c){
        case ' ':  case '\t':
        case '\r': case '\n':
            if(nameStr.length!=0)
                safethrow_wrongchar(c,;);
            nameStr.ptr++;
            break;
        case '=':  case ';':
        case '\'': case '"':
        case '[':  case ']':
        case '{':
            safethrow_wrongchar(c,;);
        case '#': ;
            char _c=c;
            char* _text=text;
            try(SkipComment(),_,;);
            if(nameStr.length!=0){
                text=_text;
                safethrow_wrongchar(_c,;);
            }
            nameStr.ptr=text+1; // skips '\n'
            break;
        case '}':
            if(!calledRecursively || nameStr.length!=0) 
                safethrow_wrongchar(c,;);
            return SUCCESS(UniPtr(CharPtr,NULL));
        case ':':
            return SUCCESS(UniPtr(CharPtr,string_extract(nameStr)));
        case '$':
            if(nameStr.length!=0)
                safethrow_wrongchar(c,;);
            nameStr.ptr++;
            partOfDollarList=true;
            break;
        default:
            nameStr.length++;
            break;
    }

    if(nameStr.length>0) safethrow(ERR_ENDOFSTR,;);
    return SUCCESS(UniPtr(CharPtr,NULL));
}
#define ReadName() __ReadName(shared)

Maybe __deserialize(char** _text, bool _calledRecursively);
Maybe __ReadValue(DeserializeSharedData* shared, bool* readingList);
#define ReadValue(rL) __ReadValue(shared, rL)

// returns part of <text> without quotes
Maybe __ReadString(DeserializeSharedData* shared){
    char c;
    bool prevIsBackslash=false;
    StringBuilder* b=StringBuilder_create();

    while ((c=*++text)){
        if(c=='"') {
            if(prevIsBackslash) {
                // replacing <\"> with <">
                StringBuilder_rmchar(b); 
                StringBuilder_append_char(b,c);
                prevIsBackslash=false;
            }
            else {
                char* str=StringBuilder_build(b).ptr;
                return SUCCESS(UniPtr(CharPtr,str));
            }
        } 
        else {
            prevIsBackslash= c=='\\' && !prevIsBackslash;
            StringBuilder_append_char(b,c);
        }
    }

    safethrow(ERR_ENDOFSTR, StringBuilder_free(b));
}
#define ReadString() __ReadString(shared)

Maybe __ReadList(DeserializeSharedData* shared){
    Autoarr(Unitype)* list=Autoarr_create(Unitype,ARR_BC,ARR_BL);
    bool readingList=true;
    while (true){
        try(ReadValue((&readingList)), val, Autoarr_free_Unitype(list))
            Autoarr_add(list,val.value); 
        if (!readingList){
            if(val.value.type==Null)
                Autoarr_pop(list);
            break;
        }
    }

    return SUCCESS(UniPtr(AutoarrUnitypePtr,list));
};
#define ReadList() __ReadList(shared)

Maybe __ParseValue(DeserializeSharedData* shared, string str){
    const string trueStr={"true",4};
    const string falseStr={"false",5};

    switch(str.ptr[str.length-1]){
        // Bool
        case 'e':
            if(string_compare(str,trueStr))
                return SUCCESS(UniTrue);
            else if(string_compare(str,falseStr))
                return SUCCESS(UniFalse);
            else safethrow_wrongchar(*str.ptr,;);
        // Float64
        case 'f': {
            char* _c=string_extract(str);
            Unitype rez=Uni(Float64,strtod(_c,NULL));
            free(_c);
            return SUCCESS(rez);
        }
        // UInt64
        case 'u': {
            uint64 lu=0;
            char* _c=string_extract(str);
            if(sscanf(_c, IFWIN("%llu", "%lu"), &lu)!=1){
                char err[64];
                IFMSC(
                    sprintf_s(err,64,"can't parse to int: <%s>",_c),
                    sprintf(err,"can't parse to int: <%s>",_c)
                );
                safethrow(err,free(_c));
            }
            free(_c);
            return SUCCESS(Uni(UInt64,lu));
        }
        // Int64
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            int64 li=0;
            char* _c=string_extract(str);
            if(sscanf(_c, IFWIN("%lli", "%li"), &li)!=1){
                char err[64];
                IFMSC(
                    sprintf_s(err,64,"can't parse to int: <%s>",_c),
                    sprintf(err,"can't parse to int: <%s>",_c)
                );
                safethrow(err,free(_c));
            }
            free(_c);
            return SUCCESS(Uni(Int64,li));
        }
        // wrong type
        default:
            safethrow_wrongchar(str.ptr[str.length-1],;);
    }

    safethrow(ERR_ENDOFSTR,;);
};
#define ParseValue(str) __ParseValue(shared, str)

Maybe __ReadValue(DeserializeSharedData* shared, bool* readingList){
    char c;
    string valueStr={text+1,0};
    Unitype value=UniNull;
    bool spaceAfterVal=false;
    
    while ((c=*++text)) switch (c){
        case ' ':  case '\t':
        case '\r': case '\n':
            if(valueStr.length!=0)
                spaceAfterVal=true;
            else valueStr.ptr++;
            break;
        case '=': case ':': 
        case '}': case '$':
        case '\'':
            safethrow_wrongchar(c,Unitype_free(value));
        case '#':;
            char _c=c;
            char* _text=text;
            try(SkipComment(),_,;);
            if(valueStr.length!=0){
                text=_text;
                safethrow_wrongchar(_c,Unitype_free(value));
            }
            valueStr.ptr=text+1; // skips '\n'
            break;
        case '"':
            if(valueStr.length!=0) safethrow_wrongchar(c,Unitype_free(value));
            try(ReadString(),maybeString,;)
                value=maybeString.value;
            break;
        case '{':
            if(valueStr.length!=0) safethrow_wrongchar(c,Unitype_free(value));
            ++text; // skips '{' 
            try(__deserialize(&text,true), val,Unitype_free(value))
                value=val.value;
            break;
        case '[':
            if(valueStr.length!=0) safethrow_wrongchar(c,Unitype_free(value));
            try(ReadList(),maybeList,Unitype_free(value))
                value=maybeList.value;
            break;
        case ']':
            if(!readingList) safethrow_wrongchar(c,Unitype_free(value));
            *readingList=false;
        case ';':
        case ',':
            if(valueStr.length!=0){
                if(value.type!=Null) 
                    safethrow_wrongchar(c,Unitype_free(value));
                try(ParseValue(valueStr),maybeParsed,;)
                    value=maybeParsed.value;
            }
            return SUCCESS(value);
        default:
            if(spaceAfterVal)
                safethrow_wrongchar(c,Unitype_free(value)); 
            valueStr.length++;
            break;
    }

    safethrow(ERR_ENDOFSTR,;);
}


Maybe __deserialize(char** _text, bool _calledRecursively) {
    DeserializeSharedData _shared={
        .sh_text_first=*_text,
        .sh_text=*_text,
        .sh_partOfDollarList=false,
        .sh_calledRecursively=_calledRecursively
    };
    DeserializeSharedData* shared=&_shared;
    Hashtable* dict=Hashtable_create();
    
    text--;
    while(true){
        try(ReadName(), maybeName, Hashtable_free(dict))
            if(!maybeName.value.VoidPtr) // end of file or '}' in recursive call 
                goto END;
        char* nameCPtr=maybeName.value.VoidPtr;
        try(ReadValue(NULL), val, {
            Hashtable_free(dict);
            free(nameCPtr);
        }) {
            if(partOfDollarList){
                partOfDollarList=false;
                Autoarr(Unitype)* list;
                Unitype lu;
                if(Hashtable_try_get(dict,nameCPtr, &lu)){
                    list=(Autoarr(Unitype)*)lu.VoidPtr;
                }
                else{
                    list=Autoarr_create(Unitype,ARR_BC,ARR_BL);
                    Hashtable_add(dict,nameCPtr,UniPtr(AutoarrUnitypePtr,list));
                }
                Autoarr_add(list,val.value);
            }
            else Hashtable_add(dict,nameCPtr,val.value);
        }
    }

    END:
    *_text=text;
    return SUCCESS(UniPtr(HashtablePtr,dict));
}

Maybe DtsodV24_deserialize(char* _text) {
    return __deserialize(&_text, false);
}
