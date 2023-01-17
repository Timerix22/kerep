#include "tests.h"

void test_type_system(){
    for(ktid id=0; id<ktid_last; id++){
        ktDescriptor d=ktDescriptor_get(id);
        kprintf("\e[37m{ id:%u name:%s size:%u freeMembers:%p toString:%p }\n",
                    d.id, d.name, d.size, d.freeMembers, d.toString);
    }
}
