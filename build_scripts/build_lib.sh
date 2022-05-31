#!/bin/bash

source build_scripts/init.sh

print "${CYAN}=============[build_lib]==============\n"
clear_dir bin
clear_dir obj
compile_c "-O2 -fpic -shared" "$SRC_C tests/test_marshalling.c"
compile_cpp "-flto -Wl,-soname,$LIB_FILE" "$SRC_CPP"
link " " $LIB_FILE
rm -rf $OBJDIR
