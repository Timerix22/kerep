#!/bin/bash
SCRIPTS="$(find build_scripts -name '*.sh')"
for F in $SCRIPTS
do
    echo $F
    chmod +x $F
done
