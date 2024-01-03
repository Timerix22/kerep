#include "../base.h"
#include "../../Array/Array.h"
#include "../../Autoarr/Autoarr.h"
#include "../../SearchTree/SearchTree.h"
#include "../../Hashtable/Hashtable.h"
#include "../../String/StringBuilder.h"
#include "../../Filesystem/filesystem.h"
#include "../../Network/network.h"
#include "base_toString.h"

void kt_initKerepTypes(){
    // base types
    kt_register(Pointer);
    if(ktid_Pointer!=0) // this can break UnitypeNull
        throw("ktid_Pointer!=0, you must init kerep types before any other types");

    kt_register(char);
    kt_register(bool);
    kt_register(f32);
    kt_register(f64);
    kt_register(i8);
    kt_register(u8);
    kt_register(i16);
    kt_register(u16);
    kt_register(i32);
    kt_register(u32);
    kt_register(i64);
    kt_register(u64);
    
    // ktDescriptor
    kt_register(ktDescriptor);

    // base type arrays
    kt_register(Array_char);
    kt_register(Array_bool);
    kt_register(Array_f32);
    kt_register(Array_f64);
    kt_register(Array_i8);
    kt_register(Array_u8);
    kt_register(Array_i16);
    kt_register(Array_u16);
    kt_register(Array_i32);
    kt_register(Array_u32);
    kt_register(Array_i64);
    kt_register(Array_u64);
    kt_register(Array_Pointer);

    // base type autoarrs
    kt_register(Autoarr_Pointer);
    kt_register(Autoarr_char);
    kt_register(Autoarr_bool);
    kt_register(Autoarr_f32);
    kt_register(Autoarr_f64);
    kt_register(Autoarr_i8);
    kt_register(Autoarr_u8);
    kt_register(Autoarr_i16);
    kt_register(Autoarr_u16);
    kt_register(Autoarr_i32);
    kt_register(Autoarr_u32);
    kt_register(Autoarr_i64);
    kt_register(Autoarr_u64);

    // Unitype
    kt_register(Unitype);
    kt_register(Array_Unitype);
    kt_register(Autoarr_Unitype);

    // STNode
    kt_register(STNode);

    // KeyValuePair
    kt_register(KVPair);
    kt_register(Autoarr_KVPair);

    // Hashtable
    kt_register(Hashtable);

    // string
    kt_register(string);
    kt_register(Array_string);
    kt_register(Autoarr_string);

    // StringBuilder
    kt_register(StringBuilder);

    // File
    kt_register(FileHandle);

    // Network
    kt_register(knIPV4Address);
    kt_register(knIPV4Endpoint);
    kt_register(knSocketTCP);
    kt_register(knSocketUDP);
    kt_register(knSocketChanneled);
}
