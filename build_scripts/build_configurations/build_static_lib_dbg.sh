#!/bin/bash

source build_scripts/init.sh

print "${CYAN}==========[build_static_lib_dbg]==========\n"
clear_dir "$OUTDIR"
clear_dir "$OBJDIR"
compile_c "$BUILD_STATIC_LIB_DBG_C_ARGS" "$SRC_C tests/test_marshalling.c"
compile_cpp "$BUILD_STATIC_LIB_DBG_CPP_ARGS" "$SRC_CPP"
pack_static_lib "$STATIC_LIB_DBG_FILE" 
