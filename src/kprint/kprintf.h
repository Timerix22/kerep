#pragma once

#if __cplusplus
extern "C" {
#endif

// cross-platform printf analog
void kprintf(const char* format, ...);

#if __cplusplus
}
#endif