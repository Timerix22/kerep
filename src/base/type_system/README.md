# kerep type system

For using some kerep capabilities, such as generic structs, unitype, and kprint, types should be *registered*.

## type id

Every registered type has its own `ktDescriptor` and `ktid` is an index of the descriptor in descriptors array.
Descriptor should be declared in header file.
Following macro declares `typedef struct` and `ktDescriptor`
```c
//someStruct.h
STRUCT(someStruct, 
    i32 i; i32 j; i32 k;
);
```
then you need to define descriptor in a source file
```c
//someStruct.c
kt_define(someStruct);
```
and register it.

## type descriptors

Every registered type should have it's own descriptor (`ktDescriptor`). It's a struct, which contains some information about type and pointers to some specific functions for this type (`toString`, `freeMembers`).

## type registration

To finally register a type, you should call macro `kt_register()` between `ktDescriptors_beginInit()` and `ktDescriptors_endInit()`. Better do it at the start of your program. To register all types from kerep, call `ktDescriptors_initKerepTypes()`.  

You can free internal ktDescriptors storage by calling `ktDescriptors_free()` at exit, if your debugger (valgrind in my case) sees a memory leak.  
Examples:  
+ [ktDescriptors_initKerepTypes()](src/base/type_system/init.c)
+ [kerep types registration](tests/main.cpp)
