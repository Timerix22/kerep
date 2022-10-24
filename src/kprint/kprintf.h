#pragma once

#if __cplusplus
extern "C" {
#endif

// cross-platform kprintf analog
void kprintf(const char* format, ...);

#if __cplusplus
}
#endif