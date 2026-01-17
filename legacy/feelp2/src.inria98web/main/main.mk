main.lib :: data_number.c debug.c feel_exec_main.c feel_terminate.c make_parallel_data.c
	cl /c data_number.c debug.c feel_exec_main.c feel_terminate.c make_parallel_data.c
	lib /OUT:main.lib data_number.obj debug.obj feel_exec_main.obj feel_terminate.obj make_parallel_data.obj
