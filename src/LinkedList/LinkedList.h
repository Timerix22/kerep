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

#define LinkedList_create(TYPE) LinkedList_##TYPE##_create()
#define LinkedList_free(LLIST) ({ LLIST->_functions->freeMembers(LLIST); free(LLIST); })

/// inserts NEW_NODE before NEXT_NODE in LLIST
#define LinkedList_insertPrev(LLIST, NEW_NODE, NEXT_NODE) LLIST->_functions->insertPrev(LLIST, NEW_NODE, NEXT_NODE)

/// inserts NEW_NODE after PREV_NODE in LLIST
#define LinkedList_insertNext(LLIST, NEW_NODE, PREV_NODE) LLIST->_functions->insertNext(LLIST, NEW_NODE, PREV_NODE)

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
    while(CURR_N!=NULL) { \
        CODE; \
        CURR_N=CURR_N->next; \
    } \
}

///@param FIRST_N first node in enumeration
///@param CURR_N name of iteration variable
///@param CODE code todo in every iteration
#define LLNode_foreachReverse(FIRST_N, CURR_N, CODE...) { \
    typeof(FIRST_N) CURR_N=FIRST_N; \
    while(CURR_N!=NULL) { \
        CODE; \
        CURR_N=CURR_N->prev; \
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
