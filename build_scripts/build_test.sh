#!/bin/bash

source build_scripts/init.sh

print "${CYAN}=============[build_test]=============\n"
clear_dir bin
clear_dir obj
compile_c "-O0 -g" "$SRC_C $TESTS_C"
compile_cpp "-O0 -g" "$SRC_CPP $TESTS_CPP"
link " " $TEST_FILE
rm -rf $OBJDIR
