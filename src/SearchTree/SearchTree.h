#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "../String/string.h"

STRUCT(STNode,
    struct STNode**** branches; // *STNode[8][8][4]
    Unitype value;
)

STNode* STNode_create();
void STNode_destruct(STNode* node);
void __STNode_destruct(void* node);

void ST_push(STNode* node, char* key, Unitype value);
void ST_pushString(STNode* node, string key, Unitype value);
Unitype ST_pull(STNode* node, char* key);
Unitype ST_pullString(STNode* node, string key);

#if __cplusplus
}
#endif
