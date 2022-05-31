#!/bin/bash

source build_scripts/init.sh

print "${CYAN}=============[build_lib]==============\n"
clear_dir bin
clear_dir obj
compile_c "-O2 -fpic -shared" "$SRC_C tests/test_marshalling.c"
compile_cpp "-O2 -fpic -shared" "$SRC_CPP"
link "-shared -O2 -fpic -flto -Wl,-soname,$LIB_FILE" "$LIB_FILE"
