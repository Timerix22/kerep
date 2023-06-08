#include "LinkedList.h"

LinkedList_define(Pointer, true)

void LinkedList_addToBeginning(void* _llist, void* _new_node) {
    LinkedList(Pointer)* llist=_llist;
    LLNode(Pointer)* new_node=_new_node;
    llist->count++;
    if(llist->last_node==NULL){
        if(llist->first_node!=NULL)
            throw(ERR_NULLPTR); // last_node can't be null if first_node != null
        llist->last_node=new_node;
    }
    else {
        llist->first_node->prev=new_node;
        new_node->next=llist->first_node;
    }
    llist->first_node=new_node;
}

void LinkedList_addToEnd(void* _llist, void* _new_node) {
    LinkedList(Pointer)* llist=_llist;
    LLNode(Pointer)* new_node=_new_node;
    llist->count++;
    if(llist->first_node==NULL) {
        if(llist->last_node!=NULL)
            throw(ERR_NULLPTR); // first_node can't be null if last_node != null
        llist->first_node=new_node;
    }
    else {
        llist->last_node->next=new_node;
        new_node->prev=llist->last_node;
    }
    llist->last_node=new_node;
}

static inline void _insertNode(LinkedList(Pointer)* llist,
    LLNode(Pointer)* prev_node, LLNode(Pointer)* new_node, LLNode(Pointer)* next_node){
    if(prev_node==NULL){
        if(next_node==llist->first_node)
            LinkedList_addToBeginning(llist, new_node);
        else throw(ERR_NULLPTR); // prev_node is null, but it isn't insertion before first_node
    }
    else if(next_node==NULL){
        if(prev_node==llist->last_node)
            LinkedList_addToEnd(llist, new_node);
        else throw(ERR_NULLPTR); // next_node is null, but it isn't insertion after last_node
    }
    else {
        prev_node->next=new_node;
        new_node->prev=prev_node;
        new_node->next=next_node;
        next_node->prev=new_node;
        llist->count++;
    }
}

void LinkedList_insertPrev(void* _llist, void* _new_node, void* _next_node){
    LLNode(Pointer)* next_node=_next_node;
    LLNode(Pointer)* prev_node=next_node->prev;
    _insertNode(_llist, prev_node, _new_node, next_node);
}

void LinkedList_insertNext(void* _llist, void* _new_node, void* _prev_node){
    LLNode(Pointer)* prev_node=_prev_node;
    LLNode(Pointer)* next_node=prev_node->next;
    _insertNode(_llist, prev_node, _new_node, next_node);
}
