mesh_exec_1D.lib :: make_feel_data_file_1D.c mesh_exec_1D.c
	cl /c make_feel_data_file_1D.c mesh_exec_1D.c
	lib /OUT:mesh_exec_1D.lib make_feel_data_file_1D.obj mesh_exec_1D.obj
