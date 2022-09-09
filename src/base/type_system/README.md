# kerep type system

For using some kerep capabilities, such as generic structs, unitype, and kprint, types should be *registered*.

## type id

Every registered type has its own id (`ktId`), which should be declared in header file and defined in source file.  
Example: 
```c
//someStruct.h
typedef struct { } someStruct;
ktId_declare(ktId_someStruct);
ktId_declare(ktId_someStructPtr); // pointer to type is another type
```
```c
//someStruct.c
ktId_define(ktId_someStruct);
ktId_define(ktId_someStructPtr);
```

## type descriptors

Every registered type should have it's own descriptor (`ktDescriptor`). It's a struct, which contains some information about type and pointers to some specific functions for this type (`toString`, `freeMembers`).

## type registration

To finally register a type, you should call macro `kt_register()` between `ktDescriptors_beginInit()` and `ktDescriptors_endInit()`. Better do it at the start of your program. To register all types from kerep, call `ktDescriptors_initKerepTypes()`.  
Examples:  
+ [ktDescriptors_initKerepTypes()](src/base/type_system/init.c)
+ [kerep types registration](tests/main.cpp)