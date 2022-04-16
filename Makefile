SRC=$(wildcard [^tests]**/*.c)
TESTS=$(wildcard tests/*c) $(wildcard tests/**/*.c)
OUTDIR=bin
CMP=gcc

all: clear_c build_lib

clear_c:
	clear

clear_bin:
	@echo -e '\e[96m--------------[clear_bin]--------------\e[0m'
	rm -rf $(OUTDIR)
	mkdir $(OUTDIR)

clang: CMP=clang
clang: all

TEST_FILE=$(OUTDIR)/kerep_test.com
TEST_ARGS= -Wall -Wno-discarded-qualifiers $(SRC) $(TESTS) -o $(TEST_FILE)
OPT_ARGS= -O1 -flto
build_test: clear_bin
	@echo -e '\n\e[96m----------------[build_test]----------------\e[0m'
	$(CMP) $(OPT_ARGS) $(TEST_ARGS)

build_test_dbg: clear_bin
	@echo -e '\n\e[96m--------------[build_test_dbg]--------------\e[0m'
	$(CMP) -O0 -g $(TEST_ARGS).dbg

test: clear_c build_test
	@echo -e '\n\e[96m----------------[test]-----------------\e[0m'
	$(TEST_FILE)

valgrind: clear_c build_test_dbg
	@echo -e '\n\e[96m--------------[valgrind]---------------\e[0m'
	valgrind -s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ \
	--leak-check=full --show-leak-kinds=all $(TEST_FILE).dbg

LIB_FILE=kerep.so
LIB_ARGS= -Wall -Wno-discarded-qualifiers \
	-O1 -fPIC -shared -Wl,-soname,$(LIB_FILE)  \
	$(SRC) $(TESTS) -o $(OUTDIR)/$(LIB_FILE)
build_lib: clear_bin
	@echo -e '\n\e[96m-------------[build_lib]---------------\e[0m'
	$(CMP) $(OPT_ARGS) $(LIB_ARGS)
