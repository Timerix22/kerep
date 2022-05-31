#include "errors.hpp"

void throwcpp(err_t eid){
    throwcpp(errname(eid));
}

void throwcpp(char* emsg){
    __EXIT(emsg);
}