#pragma once

#if __cplusplus
extern "C" {
#endif

#define LLNode_define(TYPE, TYPE_IS_PTR)\
LLNode(TYPE)* LLNode_##TYPE##_create(){ \
    LLNode(TYPE)* node= (LLNode(TYPE)*)malloc(sizeof(*node)); \
    node->prev=NULL; \
    node->next=NULL; \
    node->value=(TYPE){0}; \
    return node; \
} \
\
LLNode(TYPE)* LLNode_##TYPE##_createFromValue(TYPE value){ \
    LLNode(TYPE)* node= (LLNode(TYPE)*)malloc(sizeof(*node)); \
    node->prev=NULL; \
    node->next=NULL; \
    node->value=value; \
    return node; \
} \
\
void LLNode_##TYPE##_freeMembers(void* _node){ \
    LLNode(TYPE)* node=(LLNode(TYPE)*)_node; \
    void* value_ptr=&node->value; \
    if(TYPE_IS_PTR) value_ptr=*(TYPE**)value_ptr; \
    ktDescriptor_##TYPE.freeMembers(value_ptr); \
    if(node->prev) node->prev->next=NULL; \
    if(node->next) node->next->prev=NULL; \
} \
\
void LLNode_##TYPE##_free(LLNode(TYPE)* node, bool free_value){ \
    if(free_value) LLNode_##TYPE##_freeMembers(node); \
    if(node->prev) node->prev->next=NULL; \
    if(node->next) node->next->prev=NULL; \
    free(node); \
} \
\
kt_define(LLNode_##TYPE, LLNode_##TYPE##_freeMembers, NULL)


#define LinkedList_define(TYPE, VALUE_IS_PTR)\
LLNode_define(TYPE, VALUE_IS_PTR) \
\
LinkedList(TYPE)* LinkedList_##TYPE##_create(){ \
    LinkedList(TYPE)* l=malloc(sizeof(*l)); \
    l->_functions=&_LinkedList_##TYPE##_functions; \
    l->first_node=NULL; \
    l->last_node=NULL; \
    l->count=0; \
    return l; \
} \
\
void LinkedList_##TYPE##_freeMembers(void* _l){ \
    LinkedList(TYPE)* l=(LinkedList(TYPE)*)_l; \
    if(l->first_node!=NULL) \
        LinkedList_foreach(l, node, LLNode_##TYPE##_free(node, true)); \
    l->first_node=NULL; l->last_node=NULL; l->count=0; \
} \
\
void LinkedList_##TYPE##_insertPrev(LinkedList(TYPE)* llist, LLNode(TYPE)* newNode, LLNode(TYPE)* nextNode){ \
    llist->count++; \
    newNode->prev=nextNode->prev; \
    newNode->next=nextNode; \
    nextNode->prev=newNode; \
} \
\
void LinkedList_##TYPE##_insertNext(LinkedList(TYPE)* llist, LLNode(TYPE)* newNode, LLNode(TYPE)* prevNode){ \
    llist->count++; \
    newNode->prev=prevNode; \
    newNode->next=prevNode->next; \
    prevNode->next=newNode; \
} \
\
void LinkedList_##TYPE##_removePrev(LinkedList(TYPE)* llist, LLNode(TYPE)* nextNode, bool freeRemoved){ \
    llist->count--; \
    LLNode(TYPE)* removedNode=nextNode->prev; \
    LLNode(TYPE)* prevNode=removedNode->prev; \
    nextNode->prev=prevNode; \
    prevNode->next=nextNode; \
    if(freeRemoved) \
        LLNode_##TYPE##_free(removedNode, true); \
} \
\
void LinkedList_##TYPE##_removeNext(LinkedList(TYPE)* llist, LLNode(TYPE)* prevNode, bool freeRemoved){ \
    llist->count--; \
    LLNode(TYPE)* removedNode=prevNode->next; \
    LLNode(TYPE)* nextNode=removedNode->next; \
    prevNode->next=nextNode; \
    nextNode->prev=prevNode; \
    if(freeRemoved) \
        LLNode_##TYPE##_free(removedNode, true); \
} \
\
LinkedList_##TYPE##_functions_t _LinkedList_##TYPE##_functions={ \
    .freeMembers=LinkedList_##TYPE##_freeMembers, \
    .insertPrev=LinkedList_##TYPE##_insertPrev, \
    .insertNext=LinkedList_##TYPE##_insertNext, \
    .removePrev=LinkedList_##TYPE##_removePrev, \
    .removeNext=LinkedList_##TYPE##_removeNext \
}; \
\
kt_define(LinkedList_##TYPE, LinkedList_##TYPE##_freeMembers, NULL)


#if __cplusplus
}
#endif
