#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "../String/string.h"

typedef struct SearchTreeNode{
    struct SearchTreeNode**** branches; // *STNode[8][8][4]
    Unitype value;
} STNode;
ktId_declare(ktId_STNode);
ktId_declare(ktId_STNodePtr);

STNode* STNode_create();
void STNode_free(STNode* node);
void __STNode_free(void* node);

void ST_push(STNode* node, char* key, Unitype value);
void ST_pushString(STNode* node, string key, Unitype value);
Unitype ST_pull(STNode* node, char* key);
Unitype ST_pullString(STNode* node, string key);

#if __cplusplus
}
#endif