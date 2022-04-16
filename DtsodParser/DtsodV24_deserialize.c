#include "DtsodV24.h"
#include "../Autoarr/StringBuilder.h"

#define ARR_BC 8
#define ARR_BL 16
#define STRB_BC 64
#define STRB_BL 1024

void __throw_wrongchar(char* file, int line, char* fname, char _c, char* _text) {
    char errBuf[]="unexpected <c> at:\n  \""
        "00000000000000000000000000000000\"";
    errBuf[12]=_c;
    for (uint8 i=0; i < 32; i++)
        errBuf[i + 22]=*(_text - 16 + i);
    printf("\n\e[91m[%s:%d %s] throwed error: %s\n", file, line, fname, errBuf);
    exit(128);
};
#define throw_wrongchar(C) __throw_wrongchar(__FILE__,__LINE__,__func__,C, text)


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

void __SkipComment(DeserializeSharedData* shared) {
    char c;
    while ((c=*++text) != '\n')
        if (!c) throw(ERR_ENDOFSTR);
};
#define SkipComment() __SkipComment(shared)

string __ReadName(DeserializeSharedData* shared){
    char c;
    string nameStr={text,0};
    text--;
    while ((c=*++text)) switch (c){
        case ' ':  case '\t':
        case '\r': case '\n':
            if(nameStr.length!=0)
                throw_wrongchar(c);
            nameStr.ptr++;
            break;
        case '=':  case ';':
        case '\'': case '"':
        case '[':  case ']':
        case '{':
            throw_wrongchar(c);
            break;
        case '#':
            SkipComment();
            if(nameStr.length!=0)
                throw_wrongchar(c);
            nameStr.ptr=text+1; //skips '\n'
            break;
        case '}':
            if(!calledRecursively) throw_wrongchar(c);
            if((*++text)!=';')
                throw_wrongchar(c);
        case ':':
            return nameStr;
        case '$':
            if(nameStr.length!=0)
                throw_wrongchar(c);
            nameStr.ptr++;
            partOfDollarList=true;
            break;
        default:
            nameStr.length++;
            break;
    }

    if(nameStr.length>0) throw(ERR_ENDOFSTR);
    return nameStr;
};
#define ReadName() __ReadName(shared)

Hashtable* __deserialize(char** _text, bool _calledRecursively);
Unitype __ReadValue(DeserializeSharedData* shared);
#define ReadValue() __ReadValue(shared)

//returns part of <text> without quotes
char* __ReadString(DeserializeSharedData* shared){
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
                return str;
            }
        } 
        else {
            prevIsBackslash= c=='\\' && !prevIsBackslash;
            StringBuilder_append_char(b,c);
        }
    }
    throw(ERR_ENDOFSTR);
    return NULL;
};
#define ReadString() __ReadString(shared)

Autoarr(Unitype)* __ReadList(DeserializeSharedData* shared){
    Autoarr(Unitype)* list=malloc(sizeof(Autoarr(Unitype)));
    *list=Autoarr_create(Unitype,ARR_BC,ARR_BL);
    readingList=true;
    while (true){
        Autoarr_add(list,ReadValue());
        if (!readingList) break;
    }
    return list;
};
#define ReadList() __ReadList(shared)

Unitype __ParseValue(DeserializeSharedData* shared, string str){
    //printf("\e[94m<\e[96m%s\e[94m>\n",string_cpToCptr(str));
    const string nullStr={"null",4};
    const string trueStr={"true",4};
    const string falseStr={"false",5};
    switch(*str.ptr){
        case 'n':
            if(string_compare(str,nullStr))
                return UniNull;
            else throw_wrongchar(*str.ptr);
            break;
        case 't':
            if(string_compare(str,trueStr))
                return UniTrue;
            else throw_wrongchar(*str.ptr);
            break;
        case 'f':
            if(string_compare(str,falseStr))
                return UniFalse;
            else throw_wrongchar(*str.ptr);
            break;
        default: 
            switch(str.ptr[str.length-1]){
                case 'f': {
                        char* _c=string_cpToCptr(str);
                        Unitype rez=Uni(Float64,strtod(_c,NULL));
                        free(_c);
                        return rez;
                    }
                case 'u': {
                        uint64 lu=0;
                        char* _c=string_cpToCptr(str);
                        sscanf(_c,"%lu",&lu);
                        free(_c);
                        return Uni(UInt64,lu);
                    }
                case '0': case '1': case '2': case '3': case '4':
                case '5': case '6': case '7': case '8': case '9': {
                        int64 li=0;
                        char* _c=string_cpToCptr(str);
                        if(sscanf(_c,"%li",&li)!=1){
                            char err[64];
                            sprintf(err,"can't parse to int: <%s>",_c);
                            throw(err);
                        }
                            
                        free(_c);
                        return Uni(Int64,li);
                    }
                default:
                    throw_wrongchar(str.ptr[str.length-1]);
            }
    }
    throw(ERR_ENDOFSTR);
    return UniNull;
};
#define ParseValue(str) __ParseValue(shared, str)

Unitype __ReadValue(DeserializeSharedData* shared){
    char c;
    string valueStr={text+1,0};
    Unitype value;
    while ((c=*++text)) switch (c){
        case ' ':  case '\t':
        case '\r': case '\n':
            if(valueStr.length!=0)
                throw_wrongchar(c);
            valueStr.ptr++;
            break;
        case '=': case ':': 
        case '}': case '$':
            throw_wrongchar(c);
            break;
        case '#':;
            char _c=c;
            SkipComment();
            if(valueStr.length!=0)
                throw_wrongchar(_c);
            valueStr.ptr=text+1; //skips '\n'
            break;
        case '"':
            if(valueStr.length!=0) throw_wrongchar(c);
            value=UniPtr(CharPtr,ReadString());
            break;
        case '\'':
            if(valueStr.length!=0) throw_wrongchar(c);
            char valueChar=*++text;
            if (*++text != '\'') throw("after <'> should be char");
            value=Uni(Char,valueChar);
            break;
        case '[':
            if(valueStr.length!=0) throw_wrongchar(c);
            value=UniPtr(AutoarrUnitypePtr,ReadList());
        case ']':
            readingList=false;
            break;
        case '{':
            if(valueStr.length!=0) throw_wrongchar(c);
            ++text; //skips '{' 
            value=UniPtr(HashtablePtr, __deserialize(&text,true));
            return value;
        case ';':
        case ',':
            if(valueStr.length!=0)
                value=ParseValue(valueStr);
            return value;
        default:
            valueStr.length++;
            break;
    }

    throw(ERR_ENDOFSTR);
    return UniNull;
};


Hashtable* __deserialize(char** _text, bool _calledRecursively) {
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
        string name=ReadName();
        if(name.length==0) //end of file or '}' in recursive call 
            goto END;
        char* nameCPtr=string_cpToCptr(name);
        Unitype value=ReadValue();
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
            Autoarr_add(list,value);
        }
        else Hashtable_add(dict,nameCPtr,value);
    }
    END:
    *_text=text;
    return dict;
}

Hashtable* DtsodV24_deserialize(char* _text) {
    return __deserialize(&_text, false);
}
