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
BUILD_LIB_C_ARGS="-O2 -fpic -shared"
BUILD_LIB_CPP_ARGS="$BUILD_LIB_CPP_ARGS"
BUILD_LIB_LINKER_ARGS="-flto -Wl,-soname,$LIB_FILE"

# build_test
TEST_FILE=kerep.com
BUILD_TEST_C_ARGS="-O0 -g"
BUILD_TEST_CPP_ARGS="$BUILD_TEST_CPP_ARGS"
BUILD_TEST_LINKER_ARGS=""
