parallel.lib :: para_block_data.c
	cl /c para_block_data.c
	lib /OUT:parallel.lib para_block_data.obj
