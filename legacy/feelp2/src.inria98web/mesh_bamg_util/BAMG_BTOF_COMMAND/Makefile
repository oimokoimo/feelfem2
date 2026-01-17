CFLAGS = -I/usr/X11R6/include 
feel.bamg.exe : bamg_btof.o  make_edge_info.o make_element_ordering.o make_feel_dat_bamg.o make_new_edat.o read_bamg_mesh.o strindex.o bamg_feel_dat_header.o  bamg_feel_dat_region_edat.o bamg_geometric_edge.o bamg_feel_dat_node.o make_feel2bamg_file.o read_bc_info.o make_boundary_nset_bamg.o make_boundary_edat_bamg.o  bamg_feel_dat_ip.o make_plot_nset_bamg.o StrEq.o
	cc -o feel.bamg.exe  bamg_btof.o make_edge_info.o make_element_ordering.o make_feel_dat_bamg.o make_new_edat.o read_bamg_mesh.o bamg_feel_dat_header.o bamg_feel_dat_region_edat.o bamg_geometric_edge.o bamg_feel_dat_node.o make_feel2bamg_file.o read_bc_info.o strindex.o make_boundary_nset_bamg.o make_boundary_edat_bamg.o bamg_feel_dat_ip.o make_plot_nset_bamg.o StrEq.o -lm  

