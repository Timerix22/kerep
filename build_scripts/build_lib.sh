#!/bin/bash

source build_scripts/init.sh

print "${CYAN}=============[build_lib]==============\n"
clear_dir bin
clear_dir obj
compile_c "$BUILD_LIB_C_ARGS" "$SRC_C tests/test_marshalling.c"
compile_cpp "$BUILD_LIB_C_ARGS" "$SRC_CPP"
link "$BUILD_LIB_CPP_ARGS $BUILD_LIB_LINKER_ARGS" "$LIB_FILE"
