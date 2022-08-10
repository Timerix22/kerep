#!/bin/bash

source build_scripts/init.sh

print "${CYAN}==========[build_shared_lib]==========\n"
clear_dir "$OUTDIR"
clear_dir "$OBJDIR"
compile_c "$BUILD_SHARED_LIB_C_ARGS" "$SRC_C tests/test_marshalling.c"
compile_cpp "$BUILD_SHARED_LIB_CPP_ARGS" "$SRC_CPP"
link "$BUILD_SHARED_LIB_CPP_ARGS $BUILD_SHARED_LIB_LINKER_ARGS" "$SHARED_LIB_FILE"
