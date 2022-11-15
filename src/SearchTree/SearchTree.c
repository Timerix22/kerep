#include "SearchTree.h"

ktid_define(STNode);

STNode* STNode_create(){
    STNode* node=malloc(sizeof(STNode));
    node->branches=NULL;
    node->value.typeId=ktid_Null;
    node->value.UInt64=0;
    return node;
}

void __STNode_free(void* _node){
    STNode* node=_node;
    if (!node) throw(ERR_NULLPTR);
    if(node->branches){
        for(uint8 n32 = 0;n32<8;n32++){
            STNode*** ptrn32=(STNode***)node->branches[n32];
            if(ptrn32){ 
                for(uint8 n4 = 0;n4<8;n4++){
                    STNode** ptrn4=ptrn32[n4];
                    if (ptrn4){
                        for(uint8 rem=0;rem<4;rem++){
                            STNode* ptrrem=ptrn4[rem];
                            if(ptrrem)
                                STNode_free(ptrrem);
                        }
                        free(ptrn4);
                    }
                }
                free(ptrn32);
            }
        }
        free(node->branches);
    }
    if(node->value.VoidPtr) 
        Unitype_free(node->value);
}
void STNode_free(STNode* node){
    __STNode_free(node);
    free(node);
}

typedef struct {uint8 n32, n4, rem;} indexes3;

indexes3 splitindex(uint8 i){
    return (indexes3){
        .n32=i/32,
        .n4=i%32/4,
        .rem=i%32%4,
    };
}

void ST_push(STNode* node_first, char* key, Unitype value){
    string keyString={key, cptr_length(key)};
    ST_pushString(node_first, keyString, value);
}

void ST_pushString(STNode* node_first, string key, Unitype value){
    if (!node_first) throw(ERR_NULLPTR);
    STNode* node_last=node_first;
    while(key.length--){
        indexes3 i3=splitindex((uint8)*key.ptr);
        if(!node_last->branches){
            node_last->branches=(STNode****)malloc(8*sizeof(STNode***));
            for(uint8 i=0;i<8;i++)
                node_last->branches[i]=(STNode***)NULL;
        }
        if(!node_last->branches[i3.n32]){
            node_last->branches[i3.n32]=(STNode***)malloc(8*sizeof(STNode**));
            for(uint8 i=0;i<8;i++)
                node_last->branches[i3.n32][i]=(STNode**)NULL;
        }
        if(!node_last->branches[i3.n32][i3.n4]){
            node_last->branches[i3.n32][i3.n4]=(STNode**)malloc(4*sizeof(STNode*));
            for(uint8 i=0;i<4;i++)
                node_last->branches[i3.n32][i3.n4][i]=(STNode*)NULL;
        }
        if(!node_last->branches[i3.n32][i3.n4][i3.rem])
            node_last->branches[i3.n32][i3.n4][i3.rem]=STNode_create();
        node_last=node_last->branches[i3.n32][i3.n4][i3.rem];
        key.ptr++;
    }
    node_last->value=value;
}

Unitype ST_pull(STNode* node_first, char* key){
    string keyString={key, cptr_length(key)};
    return ST_pullString(node_first, keyString);
}

Unitype ST_pullString(STNode* node_first, string key){
    if (!node_first) throw(ERR_NULLPTR);
    STNode* node_last=node_first;
    while (key.length--){
        indexes3 i3=splitindex((uint8)*key.ptr);
        if(!node_last->branches) return UniNull;
        STNode*** ptrn32=(STNode***)node_last->branches[i3.n32];
        if(!ptrn32) return UniNull;
        STNode** ptrn4=ptrn32[i3.n4];
        if(!ptrn4) return UniNull;
        node_last=ptrn4[i3.rem];
        if(!node_last) return UniNull;
        key.ptr++;
    }
    return node_last->value;
}
