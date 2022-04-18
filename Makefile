SRC=$(wildcard [^tests]**/*.c)
TESTS=$(wildcard tests/*c) $(wildcard tests/**/*.c)

OUTDIR=bin
CMP=gcc
OPT_ARGS=-O2 -flto
WARN_ARGS=-Wall -Wno-discarded-qualifiers

all: build_lib

clear_c:
	clear

clear_bin:
	@echo -e '\e[96m--------------[clear_bin]--------------\e[0m'
	rm -rf $(OUTDIR)
	mkdir $(OUTDIR)

clang: CMP=clang
clang: all

TEST_FILE=kerep_test.com
TEST_ARGS=$(WARN_ARGS) $(SRC) $(TESTS) -o $(OUTDIR)/$(TEST_FILE)
build_test: clear_c clear_bin
	@echo -e '\n\e[96m----------------[build_test]----------------\e[0m'
	$(CMP) $(OPT_ARGS) $(TEST_ARGS)

build_test_dbg: clear_c clear_bin
	@echo -e '\n\e[96m--------------[build_test_dbg]--------------\e[0m'
	$(CMP) -g -O0 $(TEST_ARGS).dbg 

test: build_test
	@echo -e '\n\e[96m----------------[test]-----------------\e[0m'
	$(OUTDIR)/$(TEST_FILE)

valgrind: build_test_dbg
	@echo -e '\n\e[96m--------------[valgrind]---------------\e[0m'
	valgrind -s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ \
	--leak-check=full --show-leak-kinds=all $(OUTDIR)/$(TEST_FILE).dbg

LIB_FILE=kerep.so
LIB_ARGS=$(OPT_ARGS) $(WARN_ARGS)\
	-fpic -shared -Wl,-soname,$(LIB_FILE)\
	$(SRC) tests/test_marshalling.c -o $(OUTDIR)/$(LIB_FILE)
build_lib: clear_c clear_bin
	@echo -e '\n\e[96m-------------[build_lib]---------------\e[0m'
	$(CMP) $(LIB_ARGS)
