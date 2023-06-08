#pragma once

#if __cplusplus
extern "C" {
#endif

#define LLNode_declare(TYPE)\
STRUCT(LLNode(TYPE), \
    LLNode(TYPE)* prev; \
    LLNode(TYPE)* next; \
    TYPE value; \
) \
\
LLNode(TYPE)* LLNode_##TYPE##_create(TYPE value); \
void LLNode_##TYPE##_destruct(LLNode(TYPE)* node, bool free_value);


#define LinkedList_declare(TYPE)\
LLNode_declare(TYPE) \
typedef struct LinkedList_##TYPE##_functions_t LinkedList_##TYPE##_functions_t; \
\
STRUCT(LinkedList(TYPE), \
    LinkedList_##TYPE##_functions_t* _functions; \
    LLNode(TYPE)* first_node; \
    LLNode(TYPE)* last_node; \
    u32 count; \
) \
\
typedef struct LinkedList_##TYPE##_functions_t { \
    destruct_t freeMembers; \
    void (*removePrev)(LinkedList(TYPE)* llist, LLNode(TYPE)* nextNode, bool freeRemoved); \
    void (*removeNext)(LinkedList(TYPE)* llist, LLNode(TYPE)* prevNode, bool freeRemoved); \
} LinkedList_##TYPE##_functions_t; \
\
extern LinkedList_##TYPE##_functions_t _LinkedList_##TYPE##_functions; \
\
LinkedList(TYPE)* LinkedList_##TYPE##_create(); \


#if __cplusplus
}
#endif
