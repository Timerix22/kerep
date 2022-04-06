#include "DtsodV24.h"
#include "../Autoarr/StringBuilder.h"

#define ARR_BC 8
#define ARR_BL 16
#define STRB_BC 64
#define STRB_BL 1024

Maybe ERROR_WRONGCHAR(char c, char* text){
    char errBuf[]="unexpected <c> at:\n  \""
        "00000000000000000000000000000000\"";
    errBuf[12]=c;
    for(uint8 i=22; i<32; i++)
        errBuf[i]=*(text - 16 + i);
    safethrow(cptr_copy(errBuf));
}
#define safethrow_wrongchar(C) return ERROR_WRONGCHAR(C, text)


typedef struct DeserializeSharedData{
    char* sh_text;
    bool sh_partOfDollarList;
    bool sh_readingList;
    bool sh_calledRecursively;
} DeserializeSharedData;
#define text shared->sh_text
#define partOfDollarList shared->sh_partOfDollarList
#define readingList shared->sh_readingList
#define calledRecursively shared->sh_calledRecursively

Maybe __SkipComment(DeserializeSharedData* shared) {
    char c;
    while ((c=*++text) != '\n')
        if (!c) safethrow(ERR_ENDOFSTR);
    return MaybeNull;
}
#define SkipComment() __SkipComment(shared)

Maybe __ReadName(DeserializeSharedData* shared){
    char c;
    string nameStr={text,0};
    text--;
    while ((c=*++text)) switch (c){
        case ' ':  case '\t':
        case '\r': case '\n':
            if(nameStr.length!=0)
                safethrow_wrongchar(c);
            nameStr.ptr++;
            break;
        case '=':  case ';':
        case '\'': case '"':
        case '[':  case ']':
        case '{':
            safethrow_wrongchar(c);
            break;
        case '#':
            try(SkipComment(),_);
            if(nameStr.length!=0)
                safethrow_wrongchar(c);
            nameStr.ptr=text+1; //skips '\n'
            break;
        case '}':
            if(!calledRecursively) safethrow_wrongchar(c);
            if((*++text)!=';')
                safethrow_wrongchar(c);
        case ':':
            return SUCCESS(UniPtr(CharPtr,string_cpToCptr(nameStr)));
        case '$':
            if(nameStr.length!=0)
                safethrow_wrongchar(c);
            nameStr.ptr++;
            partOfDollarList=true;
            break;
        default:
            nameStr.length++;
            break;
    }

    if(nameStr.length>0) safethrow(ERR_ENDOFSTR);
    return SUCCESS(UniPtr(CharPtr,NULL));
}
#define ReadName() __ReadName(shared)

Maybe __deserialize(char** _text, bool _calledRecursively);
Maybe __ReadValue(DeserializeSharedData* shared);
#define ReadValue() __ReadValue(shared)

//returns part of <text> without quotes
Maybe __ReadString(DeserializeSharedData* shared){
    char c;
    bool prevIsBackslash=false;
    StringBuilder _b=StringBuilder_create(STRB_BC,STRB_BL);
    StringBuilder* b=&_b;
    while ((c=*++text)){
        if(c=='"') {
            if(prevIsBackslash) {
                //replacing <\"> with <">
                Autoarr_remove(b); 
                StringBuilder_append_char(b,c);
            }
            else {
                char* str=StringBuilder_build(b);
                Autoarr_clear(b);
                return SUCCESS(UniPtr(CharPtr,str));
            }
        } 
        else {
            prevIsBackslash= c=='\\' && !prevIsBackslash;
            StringBuilder_append_char(b,c);
        }
    }
    safethrow(ERR_ENDOFSTR);
}
#define ReadString() __ReadString(shared)

Maybe __ReadList(DeserializeSharedData* shared){
    Autoarr(Unitype)* list=malloc(sizeof(Autoarr(Unitype)));
    *list=Autoarr_create(Unitype,ARR_BC,ARR_BL);
    readingList=true;
    while (true){
        try(ReadValue(), val)
            Autoarr_add(list,val.value);
        if (!readingList) break;
    }
    return SUCCESS(UniPtr(AutoarrUnitypePtr,list));
};
#define ReadList() __ReadList(shared)

Maybe __ParseValue(DeserializeSharedData* shared, string str){
    //printf("\e[94m<\e[96m%s\e[94m>\n",string_cpToCptr(str));
    const string nullStr={"null",4};
    const string trueStr={"true",4};
    const string falseStr={"false",5};
    switch(*str.ptr){
        case 'n':
            if(string_compare(str,nullStr))
                return SUCCESS(UniNull);
            else safethrow_wrongchar(*str.ptr);
            break;
        case 't':
            if(string_compare(str,trueStr))
                return SUCCESS(UniTrue);
            else safethrow_wrongchar(*str.ptr);
            break;
        case 'f':
            if(string_compare(str,falseStr))
                return SUCCESS(UniFalse);
            else safethrow_wrongchar(*str.ptr);
            break;
        default: 
            switch(str.ptr[str.length-1]){
                case 'f': {
                        char* _c=string_cpToCptr(str);
                        Unitype rez=Uni(Float64,strtod(_c,NULL));
                        free(_c);
                        return SUCCESS(rez);
                    }
                case 'u': {
                        uint64 lu=0;
                        char* _c=string_cpToCptr(str);
                        sscanf(_c,"%lu",&lu);
                        free(_c);
                        return SUCCESS(Uni(UInt64,lu));
                    }
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9': {
                        int64 li=0;
                        char* _c=string_cpToCptr(str);
                        if(sscanf(_c,"%li",&li)!=1){
                            char err[64];
                            IFWIN(
                                sprintf_s(err,64,"can't parse to int: <%s>",_c),
                                sprintf(err,"can't parse to int: <%s>",_c)
                            );
                            safethrow(err);
                        }
                        free(_c);
                        return SUCCESS(Uni(Int64,li));
                    }
                default:
                    safethrow_wrongchar(str.ptr[str.length-1]);
            }
    }
    safethrow(ERR_ENDOFSTR);
};
#define ParseValue(str) __ParseValue(shared, str)

Maybe __ReadValue(DeserializeSharedData* shared){
    char c;
    string valueStr={text+1,0};
    Unitype value;
    while ((c=*++text)) switch (c){
        case ' ':  case '\t':
        case '\r': case '\n':
            if(valueStr.length!=0)
                safethrow_wrongchar(c);
            valueStr.ptr++;
            break;
        case '=': case ':': 
        case '}': case '$':
            safethrow_wrongchar(c);
            break;
        case '#':;
            char _c=c;
            try(SkipComment(),_);
            if(valueStr.length!=0)
                safethrow_wrongchar(_c);
            valueStr.ptr=text+1; //skips '\n'
            break;
        case '"':
            if(valueStr.length!=0) safethrow_wrongchar(c);
            try(ReadString(),maybeString)
                value=maybeString.value;
            break;
        case '\'':
            if(valueStr.length!=0) safethrow_wrongchar(c);
            char valueChar=*++text;
            if (*++text != '\'') safethrow("after <'> should be char");
            value=Uni(Char,valueChar);
            break;
        case '[':
            if(valueStr.length!=0) safethrow_wrongchar(c);
            try(ReadList(),maybeList)
                value=maybeList.value;
        case ']':
            readingList=false;
            break;
        case '{':
            if(valueStr.length!=0) safethrow_wrongchar(c);
            ++text; //skips '{' 
            try(__deserialize(&text,true), val)
                return SUCCESS(val.value);
        case ';':
        case ',':
            if(valueStr.length!=0){
                try(ParseValue(valueStr),maybeParsed)
                    value=maybeParsed.value;
            }
            return SUCCESS(value);
        default:
            valueStr.length++;
            break;
    }

    safethrow(ERR_ENDOFSTR);
}


Maybe __deserialize(char** _text, bool _calledRecursively) {
    DeserializeSharedData _shared={
        .sh_text=*_text,
        .sh_partOfDollarList=false,
        .sh_readingList=false,
        .sh_calledRecursively=_calledRecursively
    };
    DeserializeSharedData* shared=&_shared;
    Hashtable* dict=Hashtable_create();
    char c;
    
    text--;
    while((c=*++text)){
        try(ReadName(), maybeName)
        if(!maybeName.value.VoidPtr) //end of file or '}' in recursive call 
            goto END;
        char* nameCPtr=maybeName.value.VoidPtr;
        try(ReadValue(), val)
            if(partOfDollarList){
                Autoarr(Unitype)* list;
                Unitype lu;
                if(Hashtable_try_get(dict,nameCPtr, &lu)){
                    list=(Autoarr(Unitype)*)lu.VoidPtr;
                }
                else{
                    list=malloc(sizeof(Autoarr(Unitype)));
                    *list=Autoarr_create(Unitype,ARR_BC,ARR_BL);
                    Hashtable_add(dict,nameCPtr,UniPtr(AutoarrUnitypePtr,list));
                }
                Autoarr_add(list,val.value);
            }
        else Hashtable_add(dict,nameCPtr,val.value);
    }
    END:
    *_text=text;
    return SUCCESS(UniPtr(HashtablePtr,dict));
}

Maybe DtsodV24_deserialize(char* _text) {
    return __deserialize(&_text, false);
}
