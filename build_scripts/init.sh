#!/bin/bash

reset
tabs 4

source build_scripts/colors.sh
source build_scripts/functions.sh

if [ ! -f ".config" ]; then
    print "${YELLOW}./.config doesn't exists\n"
    cp build_scripts/default.config.sh .config
    print "${YELLOW}default config created\n"
    while true; do
        print "${WHITE}continue? (y/n) "
        read answ
        case $answ in
            [Yy] ) break;;
            [Nn] ) exit;;
            * ) print "${RED}incorrect answer\n";;
        esac
    done
fi
source .config
