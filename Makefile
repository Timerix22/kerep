######      Building tasks     #######
build_test: 
	@build_scripts/build_configurations/build_test.sh

build_test_dbg: 
	@build_scripts/build_configurations/build_test_dbg.sh

build_lib: 
	@build_scripts/build_configurations/build_lib.sh

######      Testing tasks      #######
test: build_test
	@build_scripts/build_configurations/test.sh

test_valgrind: build_test_dbg
	@build_scripts/build_configurations/test_valgrind.sh

all: build_test
