#include "tests.h"
#include "../src/SearchTree/SearchTree.h"

void printstnode(STNode* node){
    printf("\e[94mSTNode: "
    IFWIN("%llu", "%lu")
    "\n  address: %p\n  value: ",sizeof(STNode),node);
    printuni(node->value);
    printf("\n");
    // prints pointers to all existing branches
    /* printf("  branches: %p\n", node->branches);
    if(node->branches) for(uint8 i=0;i<8;i++){
        printf("    \e[90m[%u]=%p\n",i,node->branches[i]);
        if(node->branches[i]) 
            for (uint8 ii = 0; ii < 8; ii++){
                printf("       \e[90m[%u]=%p\n",ii,node->branches[i][ii]);
                if(node->branches[i][ii])
                    for (uint8 iii = 0; iii < 4; iii++) 
                        printf("          \e[90m[%u]=%p\n",iii,node->branches[i][ii][iii]);
            }
        
    } */
}

void test_searchtree(){
    optime("test_searchtree",1,({
        printf("\e[96m-----------[test_searchtree]----------\n");
        STNode* node=STNode_create();
        printf("\e[92mnode created\n");
        printf("push:\e[94m\n  ");
        Unitype u=UniInt64(-3);
        printuni(u);
        ST_push(node,"type", u);
        printf(" -> type\n  ");
        u=UniInt64(25);
        printuni(u);
        ST_push(node,"time", u);
        printf(" -> time\n  ");
        u=UniFloat64(-542.00600);
        printuni(u);
        ST_push(node,"author_id", u);
        printf(" -> author_id\n  ");
        u=UniInt64(-31255);
        printuni(u);
        ST_push(node,"channel_id", u);
        printf(" -> channel_id\n  ");
        u=UniHeap(ktId_CharPtr, cptr_copy("32.2004"));
        printuni(u);
        ST_push(node,"message_id", u);
        printf(" -> message_id\n  ");
        u=UniStack(ktId_CharPtr,"some text UwU");
        printuni(u);
        ST_push(node,"text", u);
        printf(" -> text\n");
        printf("\e[92mpull:\e[94m");
        printf("\n  type -> ");
        printuni(ST_pull(node,"type"));
        printf("\n  time -> ");
        printuni(ST_pull(node,"time"));
        printf("\n  author_id -> ");
        printuni(ST_pull(node,"author_id"));
        printf("\n  channel_id -> ");
        printuni(ST_pull(node,"channel_id"));
        printf("\n  message_id -> ");
        printuni(ST_pull(node,"message_id"));
        printf("\n  text -> ");
        printuni(ST_pull(node,"text"));
        printf("\n");
        printf("\e[92mfirst node:  ");
        printstnode(node);
        STNode_free(node);
        printf("\e[92mnode deleted\n");
    }));
}
