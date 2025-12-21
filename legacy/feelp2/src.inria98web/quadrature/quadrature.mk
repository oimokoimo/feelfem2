quadrature.lib :: get_quad_nodes_by_name.c quadrature.c
	cl /c get_quad_nodes_by_name.c quadrature.c
	lib /OUT:quadrature.lib get_quad_nodes_by_name.obj quadrature.obj
