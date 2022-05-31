#include "errors.hpp"

void throwcpp_id(ErrorId eid){
    throwcpp_msg(errname(eid));
}

void throwcpp_msg(char* emsg){
    __EXIT(emsg);
}