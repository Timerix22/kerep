#pragma once

#ifdef __cplusplus
#include "errors.h"

void throwcpp(err_t eid);
void throwcpp(char* emsg);
#endif