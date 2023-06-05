#include "memory.h"

void* allocator_transfer(allocator_t* src, allocator_t* dest, void* data, size_t data_size)
{
    void* transfered=allocator_alloc(dest, data_size); 
    memcpy(transfered, data, data_size);
    allocator_free(src, data);
    return transfered;
}
