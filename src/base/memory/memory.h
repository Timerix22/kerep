#include "allocators.h"

// addresses must be aligned to this value
#define memory_align sizeof(void*)
// adds padding if memory_align if N isn't a multiple of memory_aligh
#define add_padding(N) (N + (N%memory_align != 0)*(memory_align - N%memory_align)) 


///////////////////////////////////////////
//           NOT AN ALLOCATOR            //
///////////////////////////////////////////
// Macros to embed internal allocator    //
// into some collection struct.          // 
///////////////////////////////////////////

/// call this macro inside struct declaration
#define InternalAllocator_decl(AL_TYPE) \
    AL_TYPE _internal_al; \
    allocator_ptr _internal_al_ptr;

/// get pointer to allocator
#define InternalAllocator_getPtr(STRUCT_PTR) (STRUCT_PTR->_internal_al_ptr)

/// true if allocator is stored inside the struct, otherwise false
#define InternalAllocator_isInternal(STRUCT_PTR) (bool)(STRUCT_PTR->_internal_al_ptr == (allocator_ptr)&STRUCT_PTR->_internal_al)

/// set ptr to external allocator
#define InternalAllocator_setExternal(STRUCT_PTR, EXT_AL_PTR) (STRUCT_PTR->_internal_al_ptr = EXT_AL_PTR);

/// create internal allocator and set ptr to it
#define InternalAllocator_construct(STRUCT_PTR, TYPE, CTOR_ARGS...) ({ \
    TYPE##_construct(&STRUCT_PTR->_internal_al, CTOR_ARGS); \
    STRUCT_PTR->_internal_al_ptr = (allocator_ptr)&STRUCT_PTR->_internal_al; \
})

/// if EXT_AL_PTR isn't null, set external allocator, otherwise create new
#define InternalAllocator_setExternalOrConstruct(STRUCT_PTR, EXT_AL_PTR, TYPE, CTOR_ARGS...) \
    if(EXT_AL_PTR!=NULL) InternalAllocator_setExternal(STRUCT_PTR, EXT_AL_PTR) \
    else InternalAllocator_construct(STRUCT_PTR, TYPE, CTOR_ARGS)
