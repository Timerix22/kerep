#!/bin/bash

OUTDIR=bin
OBJDIR=obj
TEST_FILE=kerep.com
LIB_FILE=kerep.so
DLL_FILE=kerep.dll
CMP_C=gcc
CMP_CPP=g++
STD_C=c11
STD_CPP=c++17
WARN_C="-Wall -Wno-discarded-qualifiers" #-Wextra
WARN_CPP="-Wall -Wconversion-null -Wno-unused-variable -Wno-return-type" #-Wextra
SRC_C="$(    find src -name *.c)"
SRC_CPP="$(  find src -name *.cpp)"
TESTS_C="$(  find tests -name *.c)"
TESTS_CPP="$(find tests -name *.cpp)"
VALGRIND_ARGS=-s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ \
	--leak-check=full --show-leak-kinds=all
