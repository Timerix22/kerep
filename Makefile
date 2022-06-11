######      Building tasks     #######
build_test: 
	@build_scripts/build_test.sh

build_test_dbg: 
	@build_scripts/build_test_dbg.sh

build_lib: 
	@build_scripts/build_lib.sh

######      Testing tasks      #######
test: 
	@build_scripts/test.sh

test_valgrind: 
	@build_scripts/test_valgrind.sh

all: build_test
