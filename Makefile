######      Build cbuild/default_tasks     #######
build_exec: 
	@cbuild/default_tasks/build_exec.sh
build_exec_dbg: 
	@cbuild/default_tasks/build_exec_dbg.sh

build_shared_lib: 
	@cbuild/default_tasks/build_shared_lib.sh
build_shared_lib_dbg: 
	@cbuild/default_tasks/build_shared_lib_dbg.sh

build_static_lib: 
	@cbuild/default_tasks/build_static_lib.sh
build_static_lib_dbg: 
	@cbuild/default_tasks/build_static_lib_dbg.sh

######      Launch cbuild/default_tasks      #######
exec: build_exec
	@cbuild/default_tasks/exec.sh

valgrind: build_exec_dbg
	@cbuild/default_tasks/valgrind.sh

all: build_exec
