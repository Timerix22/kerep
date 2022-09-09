######      Build cbuild/default_tasks     #######
build_exec: 
	@cbuild/call_task.sh build_exec
build_exec_dbg: 
	@cbuild/call_task.sh build_exec_dbg

build_shared_lib: 
	@cbuild/call_task.sh build_shared_lib
build_shared_lib_dbg: 
	@cbuild/call_task.sh build_shared_lib_dbg

build_static_lib: 
	@cbuild/call_task.sh build_static_lib
build_static_lib_dbg: 
	@cbuild/call_task.sh build_static_lib_dbg

######      Launch cbuild/default_tasks      #######
exec: build_exec
	@cbuild/call_task.sh exec

valgrind: build_exec_dbg
	@cbuild/call_task.sh valgrind

all: build_exec
