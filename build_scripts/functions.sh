#!/bin/bash

function print {
    printf "$1$GRAY"
}

function clear_dir {
	print "${BLUE}clearing $1\n"
    rm -rf $1
	mkdir $1
}

function compile {
    local cmp=$1
    print "${BLUE}compiler: ${GRAY}$cmp\n"
    local std=$2
    print "${BLUE}standard: ${GRAY}$std\n"
    local warn=$3
    print "${BLUE}warnings: ${GRAY}$warn\n"
    local args=$4
    print "${BLUE}args: ${GRAY}$args\n"
    local sources=$5
    print "${BLUE}sources: ${GRAY}$sources\n"
	for SRCFILE in $sources
    do
        $cmp -std=$std $warn $args -c -o "$OBJDIR/$(basename $SRCFILE).o" $SRCFILE
    done
}

# (args, sources)
function compile_c {
	print "${CYAN}-------------[compile_c]--------------\n"
    compile $CMP_C $STD_C "$WARN_C " "$1" "$2"
}

# (args, sources)
function compile_cpp {
	print "${CYAN}------------[compile_cpp]-------------\n"
    compile $CMP_CPP $STD_CPP "$WARN_CPP" "$1" "$2"
}

# (args, outfile)
function link {
	print "${CYAN}----------------[link]----------------\n"
    local args=$1
    print "${BLUE}args: ${GRAY}$args\n"
    local outfile=$OUTDIR/$2
    print "${BLUE}outfile: ${GRAY}$outfile\n"
    local objects="$(find $OBJDIR -name *.o)"
    print "${BLUE}objects: ${GRAY}$objects\n"
    $CMP_C $args -o $outfile $(echo $objects | tr '\n' ' ')
    print "${GREEN}file $CYAN$outfile ${GREEN}created\n"
}
