#include "tests.h"
#include "../src/DtsodParser/DtsodV24.h"

const char text[]=
"list_of_lists: [ [\"sss\"]];"
"blank_list: [];"
"message: {\n"
"    bool: false;"
"    int: -2515;"
"    uint:#comment!\n 0u;"
"    double: 965.557f;#another comment!\n"
"    text: \"_$\\\"\\\\'''a ыыы000;2;=:%d;```\";\n"
"    list: [10,20,30,0,0 ];"
"};"
"h: { };";

void print_dtsod(Hashtable* dtsod){
    kprintf("\e[92m");
    Hashtable_foreach(dtsod, p,({
        printkvp(p);
        if(p.value.typeId==ktid_ptrName(Hashtable)){
            kprintf(": {\n");
            Hashtable* sub=p.value.VoidPtr;
            Hashtable_foreach(sub, _p,({
                kprintf("    ");
                printkvp(_p);
                kprintf("\n");
            }));
            kprintf("}");
        }
        kprintf("\n");
    }));
}

void test_dtsod(){
    optime(__func__,1,({
        kprintf("\e[96m-------------[test_dtsod]-------------\n");
        Hashtable* dtsod;
        char* s;

        optime("deserialize",1,({
            tryLast(DtsodV24_deserialize(text),r) 
                dtsod=r.value.VoidPtr;
        }));
        print_dtsod(dtsod);

        optime("serialize",1,({
            tryLast(DtsodV24_serialize(dtsod),r)
                s=r.value.VoidPtr;
        }));
        DtsodV24_free(dtsod);
        kprintf("\e[92m%s",s);

        optime("reserialize",10,({
            tryLast(DtsodV24_deserialize(s),r) 
                dtsod=r.value.VoidPtr;
            free(s);
            tryLast(DtsodV24_serialize(dtsod),rr)
                s=rr.value.VoidPtr;
            DtsodV24_free(dtsod);
        }));

        free(s);
    }));
}