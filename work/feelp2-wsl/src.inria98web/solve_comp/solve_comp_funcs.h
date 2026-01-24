/*
 *
 * solve_comp funcs prototype solve_comp_funcs.h
 *
 *
 */

void store_element_node_init( char *name,int etype );

void store_element_node(Frac ra,Frac sa,Frac ta,char *name,int type,int free_flag);

void store_element_node_for_mesh(Frac ra,Frac sa,Frac ta,char *name,int type);

int store_edat( ElemDat *edat_ptr );

void elem_dat_make_main(Solve *solve_ptr,SolveElement *solve_element_ptr, ElementFORT77 *elem77_ptr);


/* mesh_comp */
void store_domain_edatno( char *domain_name, int  edatno );
int get_domain_region_no( char *domain_name , char *region_name );

void store_element_node_init(char *name,int etype );

int get_new_edatno();
