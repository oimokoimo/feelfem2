var_comp.lib :: ewise_info.c get_elem_name_by_ND.c get_fem_var_freedom_by_ND.c is_number_string.c var_comp.c var_init.c
	cl /c ewise_info.c get_elem_name_by_ND.c get_fem_var_freedom_by_ND.c is_number_string.c var_comp.c var_init.c
	lib /OUT:var_comp.lib ewise_info.obj get_elem_name_by_ND.obj get_fem_var_freedom_by_ND.obj is_number_string.obj var_comp.obj var_init.obj
