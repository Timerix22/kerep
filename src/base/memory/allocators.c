#include "memory.h"

void* allocator_transfer(allocator_ptr src, allocator_ptr dest, void* data, alloc_size_t data_size)
{
    void* transfered=allocator_alloc(dest, data_size); 
    memcpy(transfered, data, data_size);
    allocator_free(src, data);
    return transfered;
}
