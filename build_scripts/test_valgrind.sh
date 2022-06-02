#!/bin/bash

source build_scripts/init.sh

print "${CYAN}===========[test_valgrind]============\n"
cd $OUTDIR
valgrind $VALGRIND_ARGS ./$TEST_FILE
cd ..
