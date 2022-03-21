SRC=$(wildcard [^tests]**/*.c)
TESTS=$(wildcard tests/*c) $(wildcard tests/**/*.c)
OUTDIR=.bin
CMP=gcc

all: clear_c clear_bin build_test build_dll

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
build_test:
	@echo -e '\n\e[96m----------------[build_test]----------------\e[0m'
	$(CMP) $(OPT_ARGS) $(TEST_ARGS)

build_test_dbg:
	@echo -e '\n\e[96m--------------[build_test_dbg]--------------\e[0m'
	$(CMP) -O0 -g $(TEST_ARGS).dbg

test:
	@echo -e '\n\e[96m----------------[test]-----------------\e[0m'
	$(TEST_FILE)

valgrind: clear_c build_test_dbg
	@echo -e '\n\e[96m--------------[valgrind]---------------\e[0m'
	valgrind -s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ \
	--leak-check=full --show-leak-kinds=all $(TEST_FILE).dbg

DLL_FILE=$(OUTDIR)/kerep.dll
DLL_ARGS= -Wall -Wno-discarded-qualifiers \
	-fPIC -shared -Wl,-soname,kerep.dll  \
	$(SRC) $(TESTS) -o $(DLL_FILE)
build_dll:
	@echo -e '\n\e[96m-------------[build_dll]---------------\e[0m'
	$(CMP) $(OPT_ARGS) $(DLL_ARGS)
