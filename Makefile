SRC=$(wildcard [^tests]**/*.c)
TESTS=$(wildcard tests/*c) $(wildcard tests/**/*.c)
OUTDIR=.bin
OUTFILE=$(OUTDIR)/kerep_test.com
CMP=gcc
all: clear_c build test

clear_c:
	clear
clear_bin:
	@echo -e '\e[96m--------------[clear_bin]--------------\e[0m'
	touch $(OUTDIR)/_.com
	rm $(OUTDIR)/*.com

clang: CMP=clang
clang: all

CMPARGS= -Wall -Wno-discarded-qualifiers $(SRC) $(TESTS) -o $(OUTFILE)
build:
	@echo -e '\n\e[96m----------------[build]----------------\e[0m'
	@mkdir -p $(OUTDIR)
	$(CMP) -O1 -flto $(CMPARGS)
build_dbg:
	@echo -e '\n\e[96m--------------[build_dbg]--------------\e[0m'
	@mkdir -p $(OUTDIR)
	$(CMP) -O0 -g $(CMPARGS).dbg
test:
	@echo -e '\n\e[96m----------------[test]-----------------\e[0m'
	$(OUTFILE)
valgrind: clear_c build_dbg
	@echo -e '\n\e[96m--------------[valgrind]---------------\e[0m'
	valgrind -s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ \
	--leak-check=full --show-leak-kinds=all $(OUTFILE).dbg
