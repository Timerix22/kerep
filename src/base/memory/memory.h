#include "allocators.h"

// addresses must be aligned to this value
#define memory_align sizeof(void*)
// adds padding if memory_align if N isn't a multiple of memory_aligh
#define add_padding(N) (N + (N%memory_align != 0)*(memory_align - N%memory_align)) 
