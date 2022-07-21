#!/bin/bash

source build_scripts/init.sh

print "${CYAN}================[test]================\n"
cd $OUTDIR
./$TEST_FILE
cd ..
