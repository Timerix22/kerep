#include "tests.h"

void test_type_system(){
    for(ktid id=0; id <= ktid_last; id++){
        ktDescriptor* type=ktDescriptor_get(id);
        kprintf("\e[37m{ id:%u name:%s size:%u destruct:%p toString:%p }\n",
                    type->id, type->name, type->size, type->destruct, type->toString);
    }
}
