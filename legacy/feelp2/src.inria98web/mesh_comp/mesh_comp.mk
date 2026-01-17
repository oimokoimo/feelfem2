mesh_comp.lib :: dimension.c domain.c extract_inner_edge_list.c get_region_area.c line.c mesh_names.c nodes.c points.c put_region_point.c refine.c region.c showmesh.c subdomain.c
	cl /c dimension.c domain.c extract_inner_edge_list.c get_region_area.c line.c mesh_names.c nodes.c points.c put_region_point.c refine.c region.c showmesh.c subdomain.c
	lib /OUT:mesh_comp.lib dimension.obj domain.obj extract_inner_edge_list.obj get_region_area.obj line.obj mesh_names.obj nodes.obj points.obj put_region_point.obj refine.obj region.obj showmesh.obj subdomain.obj
