#pragma once

#if __cplusplus
extern "C" {
#endif

#include "../base/base.h"
#include "LinkedList_declare.h"
#include "LinkedList_define.h"

// LinkedListNode

#define LLNode(TYPE) LLNode_##TYPE
#define LinkedList(TYPE) LinkedList_##TYPE

#define LLNode_create(TYPE, VALUE) LLNode_##TYPE##_create(VALUE)

#define LinkedList_create(TYPE) LinkedList_##TYPE##_create()
#define LinkedList_free(LLIST)  ({ LLIST->_functions->freeMembers(LLIST); free(LLIST); })


void LinkedList_addToBeginning(void* _llist, void* _new_node);
void LinkedList_addToEnd(void* _llist, void* _new_node);

/// inserts NEW_NODE before NEXT_NODE in LLIST
void LinkedList_insertPrev(void* _llist, void* _new_node, void* _next_node);

/// inserts NEW_NODE after PREV_NODE in LLIST
void LinkedList_insertNext(void* _llist, void* _new_node, void* _prev_node);

/// removes node before NEXT_NODE in LLIST
/// if FREE_REMOVED then frees removed node
#define LinkedList_removePrev(LLIST, NEXT_NODE, FREE_REMOVED) LLIST->_functions->removePrev(LLIST, NEXT_NODE, FREE_REMOVED)

/// removes node after PREV_NODE in LLIST
/// if FREE_REMOVED then frees removed node
#define LinkedList_removeNext(LLIST, PREV_NODE, FREE_REMOVED) LLIST->_functions->removeNext(LLIST, PREV_NODE, FREE_REMOVED)

///@param FIRST_N first node in enumeration
///@param CURR_N name of iteration variable
///@param CODE code todo in every iteration
#define LLNode_foreach(FIRST_N, CURR_N, CODE...) { \
    typeof(FIRST_N) CURR_N=FIRST_N; \
    typeof(FIRST_N) NEXT_N=FIRST_N; \
    while(CURR_N!=NULL) { \
        NEXT_N=CURR_N->next; \
        CODE; \
        CURR_N=NEXT_N; \
    } \
}

///@param FIRST_N first node in enumeration
///@param CURR_N name of iteration variable
///@param CODE code todo in every iteration
#define LLNode_foreachReverse(FIRST_N, CURR_N, CODE...) { \
    typeof(FIRST_N) CURR_N=FIRST_N; \
    typeof(FIRST_N) PREV_N=FIRST_N; \
    while(CURR_N!=NULL) { \
        PREV_N=CURR_N->prev; \
        CODE; \
        CURR_N=PREV_N; \
    } \
}

///@param LLIST LinkedList
///@param CURR_N name of iteration variable
///@param CODE code todo in every iteration
#define LinkedList_foreach(LLIST, CURR_N, CODE...) \
    LLNode_foreach(LLIST->first_node, CURR_N, CODE)

///@param LLIST LinkedList
///@param CURR_N name of iteration variable
///@param CODE code todo in every iteration
#define LinkedList_foreachReverse(LLIST, CURR_N, CODE...) \
    LLNode_foreachReverse(LLIST->last_node, CURR_N, CODE)



LinkedList_declare(Pointer)

#if __cplusplus
}
#endif
