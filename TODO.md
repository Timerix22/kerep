## General refactoring
- replace all malloc() and free() with allocator_alloc() and allocator_free()
- replace allocating constructors with Type_init(var_ptr, ...)
- replace Struct_free functions with Struct_destruct which will not call free() on the struct ptr
- store in resizable structs their buffer allocators and free them with Struct_destruct()
- check allocator_free call order
- replace LinearAllocator with StackingAllocator when possible (in DtsodV24_deserialize)

## Autoarr
- store lenght and max_lenght inside the struct instead of calculating them by macro
- keep Autoarr_length() and Autoarr_maxLength() to old code compatibility

## Hashtable
- store hash in KVPair
- don't use Autoarr in Hashtable
- make Hashtable generic struct

## Unitype
- replace UniPtrHeap with UniPtrStack
- do something with VoidPtr ownership

## String
- add `bool zero_terminated`
- rewrite all code to use `string` instead of `char*`
- rewrite `StringBuilder` 
