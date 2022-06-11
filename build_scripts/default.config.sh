#!/bin/bash

OUTDIR=bin
OBJDIR=obj
CMP_C=gcc
CMP_CPP=g++
STD_C=c11
STD_CPP=c++17
WARN_C="-Wall -Wno-discarded-qualifiers" #-Wextra
WARN_CPP="-Wall -Wno-unused-variable -Wno-return-type" #-Wextra
SRC_C="$(    find src -name *.c)"
SRC_CPP="$(  find src -name *.cpp)"
TESTS_C="$(  find tests -name *.c)"
TESTS_CPP="$(find tests -name *.cpp)"
VALGRIND_ARGS="-s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ --leak-check=full --show-leak-kinds=all"

# build_lib
LIB_FILE=kerep.so
BUILD_LIB_C_ARGS="-O2 -fpic -flto -shared"
BUILD_LIB_CPP_ARGS="$BUILD_LIB_C_ARGS"
BUILD_LIB_LINKER_ARGS="-Wl,-soname,$LIB_FILE"

# build_test
TEST_FILE=kerep.com
BUILD_TEST_C_ARGS="-O2"
BUILD_TEST_CPP_ARGS="$BUILD_TEST_C_ARGS"
BUILD_TEST_LINKER_ARGS=""

# build_test_dbg
TEST_DBG_FILE=$TEST_FILE
BUILD_TEST_DBG_C_ARGS="-O0 -g"
BUILD_TEST_DBG_CPP_ARGS="$BUILD_TEST_DBG_C_ARGS"
BUILD_TEST_DBG_LINKER_ARGS=""
