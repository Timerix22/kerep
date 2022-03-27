//
// I planned to export functions from DtsodV24.h, 
// but C# P/Invoke can't get returned values for some reason.
// Following functions return values by pointer, which looks in C# like out parameter
//

#if __cplusplus
extern "C" {
#endif

#include "DtsodV24.h"

//parses text to binary values
EXPORT void CALL kerep_DtsodV24_deserialize(char* text, Hashtable** output){
    *output=DtsodV24_deserialize(text);
}

//creates text representation of dtsod
EXPORT void CALL kerep_DtsodV24_serialize(Hashtable* dtsod, char** output){
    *output=DtsodV24_serialize(dtsod);
}

//returns value or UniNull if key not found
EXPORT void CALL kerep_DtsodV24_get(Hashtable* dtsod, char* key, Unitype* output){
    *output=DtsodV24_get(dtsod, key);
}

//adds or sets value
EXPORT void CALL kerep_DtsodV24_addOrSet(Hashtable* dtsod, char* key, Unitype value){
    DtsodV24_addOrSet(dtsod, key, value);
}

//checks for dtsod contains value or dont
EXPORT void CALL kerep_DtsodV24_contains(Hashtable* dtsod, char* key, bool* output){
    *output=DtsodV24_contains(dtsod, key);
}

//replaces value with UniNull if key exists in dtsod
EXPORT void CALL kerep_DtsodV24_remove(Hashtable* dtsod, char* key, bool* output){
    *output=DtsodV24_remove(dtsod, key);
}

#if __cplusplus
}
#endif