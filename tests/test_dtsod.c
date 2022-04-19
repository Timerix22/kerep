#include "tests.h"
#include "../DtsodParser/DtsodV24.h"

const char text[]=
"message: {\n"
"    bool: false;"
"    int: -2515;"
"    uint:#comment!\n 0u;"
"    double: 965.557f;#another comment!\n"
"    text: \"_$\\\"\\\\'''a ыыы000;2;=:%d;```\";\n"
"    list: [10,20,30,0,0 ];"
"    list_of_lists: [ [\"sss\"]];"
"};";

void print_dtsod(Hashtable* dtsod){
    printf("\e[92m");
    Hashtable_foreach(dtsod, p,({
        printkvp(p);
        if(p.value.type==HashtablePtr){
            printf(": {\n");
            Hashtable* sub=p.value.VoidPtr;
            Hashtable_foreach(sub, _p,({
                printf("    ");
                printkvp(_p);
                printf("\n");
            }));
            printf("}");
        }
        printf("\n");
    }));
}


#include <errno.h>


void test_dtsod(){
    optime(__func__,1,({
        printf("\e[96m-------------[test_dtsod]-------------\n");
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
        Hashtable_free(dtsod);
        printf("\e[92m%s",s);

        optime("reserialize",10,({
            tryLast(DtsodV24_deserialize(s),r) 
                dtsod=r.value.VoidPtr;
            free(s);
            tryLast(DtsodV24_serialize(dtsod),rr)
                s=rr.value.VoidPtr;
            Hashtable_free(dtsod);
        }));

        free(s);

        FILE* f=fopen("messages.dtsod", "r");
        if(f==NULL){
            perror("error ");
            throw("can't open file");
        }
        char fbuf[65535];
        uint32 i=0;
        char cc;
        while((cc=fgetc(f))!=EOF){
            fbuf[i++]=cc;
        }
        fbuf[i]='\0';
        fclose(f);
        printf("read %u chars", i);
        Maybe rrr=DtsodV24_deserialize(fbuf);
        if(rrr.errmsg) {
            throw(rrr.errmsg);
        }
        else dtsod=rrr.value.VoidPtr;
        Hashtable_free(dtsod);
    }));
}