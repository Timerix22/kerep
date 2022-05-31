######################################
######          Config         #######
######################################
OUTDIR:=bin
OBJDIR:=obj
TEST_FILE:=kerep.com
LIB_FILE:=kerep.so
DLL_FILE:=kerep.dll
CMP_C:=gcc
CMP_CPP:=g++
STD_C:=c11
STD_CPP:=c++17
WARN_C:=-Wall -Wno-discarded-qualifiers #-Wextra
WARN_CPP:=-Wall #-Wextra
SRC_C:=    $(wildcard src/*.c   )  $(wildcard src/**/*.c    )
SRC_CPP:=  $(wildcard src/*.cpp )  $(wildcard src/**/*.cpp  )
TESTS_C:=  $(wildcard tests/*c  )  $(wildcard tests/**/*.c  )
TESTS_CPP:=$(wildcard tests/*cpp)  $(wildcard tests/**/*.cpp)


######################################
######       Small tasks       #######
######################################

all: clear_c clear_bin build_test

clear_c:
	clear

clear_bin:
	@echo -e '\e[96m-------------[clear_bin]--------------\e[0m'
	rm -rf $(OUTDIR)
	mkdir  $(OUTDIR)

clear_obj:
	@echo -e '\e[96m-------------[clear_obj]--------------\e[0m'
	rm -rf $(OBJDIR)
	mkdir  $(OBJDIR)


######################################
######       Build tasks       #######
######################################

# set it in build targets
SOURCES_C:=
SOURCES_CPP:=
CMPARGS:=
LNKARGS:=
OUTFILE:=

compile_c_file=$(CMP_C) -std=$(STD_C) $(WARN_C) $(CMPARGS) -c ../$(SRCFILE)
__compile_c:
	@echo -e '\e[96m-------------[compile_c]--------------\e[0m'
	$(eval commands:=cd $(OBJDIR) $(foreach SRCFILE, $(SOURCES_C), ; $(compile_c_file)))
	$(commands)

compile_cpp_file=$(CMP_CPP) -std=$(STD_CPP) $(WARN_CPP) $(CMPARGS) -c ../$(SRCFILE)
__compile_cpp:
	@echo -e '\e[96m------------[compile_cpp]-------------\e[0m'
	$(eval commands:=cd $(OBJDIR) $(foreach SRCFILE, $(SOURCES_CPP), ; $(compile_cpp_file)))
	$(commands)

__compile: __compile_c #__compile_cpp

__link:
	@echo -e '\e[96m----------------[link]----------------\e[0m'
	$(CMP_C) $(LNKARGS) -o $(OUTDIR)/$(OUTFILE) $(wildcard $(OBJDIR)/*.o)

######       Build test        #######
__build_test_pre:
	@echo -e '\e[96m===========[build_test_dbg]===========\e[0m'
build_test: OUTFILE=$(TEST_FILE)
build_test: SOURCES_C=$(SRC_C) $(TESTS_C)
build_test: SOURCES_CPP=$(SRC_CPP) $(TESTS_CPP)
build_test: CMPARGS=-O0 -g
build_test: LNKARGS=
build_test: clear_c __build_test_pre clear_obj __compile __link

######        Build lib        #######
__build_lib_pre:
	@echo -e '\e[96m=============[build_lib]==============\e[0m'
build_lib: OUTFILE=$(LIB_FILE)
build_lib: SOURCES_C=$(SRC_C) tests/test_marshalling.c
build_lib: SOURCES_CPP=$(SRC_CPP)
build_lib: CMPARGS=-O2 -fpic -shared
build_lib: LNKARGS=-flto -Wl,-soname,$(LIB_FILE)
build_lib: clear_c __build_lib_pre clear_obj __compile __link

######        Build dll        #######
__build_dll_pre:
	@echo -e '\e[96m=============[build_dll]==============\e[0m'
build_dll: OUTFILE=$(DLL_FILE)
build_dll: SOURCES_C=$(SRC_C) tests/test_marshalling.c
build_dll: SOURCES_CPP=$(SRC_CPP)
build_dll: CMPARGS=-O2 -fpic -shared
build_dll: LNKARGS=-static-libgcc -static-libstdc++
build_dll: clear_c __build_dll_pre clear_obj __compile __link


######################################
######      Testing tasks      #######
######################################
test: build_test
	@echo -e '\e[96m================[test]================\e[0m'
	@tabs 4
	cd $(OUTDIR); ./$(TEST_FILE)

valgrind: build_test
	@echo -e '\e[96m==============[valgrind]==============\e[0m'
	@tabs 4
	cd $(OUTDIR); valgrind -s --read-var-info=yes --track-origins=yes --fullpath-after=kerep/ \
	--leak-check=full --show-leak-kinds=all $(TEST_FILE).dbg
