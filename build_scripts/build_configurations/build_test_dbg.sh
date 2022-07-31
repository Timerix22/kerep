#!/bin/bash

source build_scripts/init.sh

print "${CYAN}===========[build_test_dbg]===========\n"
clear_dir "$OUTDIR"
clear_dir "$OBJDIR"
compile_c "$BUILD_TEST_DBG_C_ARGS" "$SRC_C $TESTS_C"
compile_cpp "$BUILD_TEST_DBG_CPP_ARGS" "$SRC_CPP $TESTS_CPP"
link "$BUILD_TEST_DBG_CPP_ARGS $BUILD_TEST_DBG_LINKER_ARGS" $TEST_DBG_FILE
