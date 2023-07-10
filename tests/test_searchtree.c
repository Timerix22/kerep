#include "tests.h"
#include "../src/SearchTree/SearchTree.h"

void printstnode(STNode* node){
    kprintf("\e[94mSTNode: %lu\n"
        "  address: %p\n"
        "  value: ", 
        sizeof(STNode), node);
    printuni(node->value);
    kprintf("\n");
    // prints pointers to all existing branches
    /* kprintf("  branches: %p\n", node->branches);
    if(node->branches) for(u8 i=0;i<8;i++){
        kprintf("    \e[90m[%u]=%p\n",i,node->branches[i]);
        if(node->branches[i]) 
            for (u8 ii = 0; ii < 8; ii++){
                kprintf("       \e[90m[%u]=%p\n",ii,node->branches[i][ii]);
                if(node->branches[i][ii])
                    for (u8 iii = 0; iii < 4; iii++) 
                        kprintf("          \e[90m[%u]=%p\n",iii,node->branches[i][ii][iii]);
            }
        
    } */
}

void test_searchtree(){
    optime("test_searchtree",1,
        kprintf("\e[96m-----------[test_searchtree]----------\n");
        LinearAllocator _al;
        LinearAllocator_construct(&_al, 1024);
        allocator_ptr al=(allocator_ptr)&_al;
        STNode* node=STNode_create();
        kprintf("\e[92mnode created\n");
        kprintf("push:\e[94m\n  ");
        Unitype u=UniInt64(-3);
        printuni(u);
        ST_push(node,"type", u);
        kprintf(" -> type\n  ");
        u=UniInt64(25);
        printuni(u);
        ST_push(node,"time", u);
        kprintf(" -> time\n  ");
        u=UniFloat64(-542.00600);
        printuni(u);
        ST_push(node,"author_id", u);
        kprintf(" -> author_id\n  ");
        u=UniInt64(-31255);
        printuni(u);
        ST_push(node,"channel_id", u);
        kprintf(" -> channel_id\n  ");
        u=UniHeapPtr(char, cptr_copy(al, "32.2004"));
        printuni(u);
        ST_push(node,"message_id", u);
        kprintf(" -> message_id\n  ");
        u=UniStackPtr(char,"some text UwU");
        printuni(u);
        ST_push(node,"text", u);
        kprintf(" -> text\n");
        kprintf("\e[92mpull:\e[94m");
        kprintf("\n  type -> ");
        printuni(ST_pull(node,"type"));
        kprintf("\n  time -> ");
        printuni(ST_pull(node,"time"));
        kprintf("\n  author_id -> ");
        printuni(ST_pull(node,"author_id"));
        kprintf("\n  channel_id -> ");
        printuni(ST_pull(node,"channel_id"));
        kprintf("\n  message_id -> ");
        printuni(ST_pull(node,"message_id"));
        kprintf("\n  text -> ");
        printuni(ST_pull(node,"text"));
        kprintf("\n");
        kprintf("\e[92mfirst node:  ");
        printstnode(node);
        STNode_destruct(node);
        kprintf("\e[92mnode deleted\n");
        LinearAllocator_destruct(&_al);
    );
}
