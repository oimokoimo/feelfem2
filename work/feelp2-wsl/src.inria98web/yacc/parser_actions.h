/* parser_actions.h */
#ifndef PARSER_ACTIONS_H
#define PARSER_ACTIONS_H

/* from main / runtime */
void feel_exec_main(void);
void debug_terminate(void);
void feel_terminate(void);

/* element */
void element_parse_init(void);
void p_element_shape(void);
void p_element_complete(void);
void p_element_cordinate_2dim(void);
void p_element_cordinate_1dim(void);
void p_basis_type(void);
void p_basis_complete(void);
void p_element_let(void);
void p_element_double(void);
void p_element_double_with_expr(void);
void p_element_const(void);
void p_element_const_with_expr(void);
void p_node_cordinate(int dim);
void p_element_fem_restrains(void);

/* quadrature */
void quadrature_parse_init(void);
void p_quadrature_shape(void);
void p_quadrature_complete(void);
void p_quadrature_coordinate_1dim(void);
void p_quadrature_coordinate_2dim(void);
void p_quadrature_coordinate_3dim(void);
void p_quadrature_component(void);
void p_quadrature_identifier(void);
void p_quadrature_const(void);
void p_quadrature_let_st(void);
void p_quad_double_identifier(void);
void p_quad_double_identifier_with_expr(void);
void p_quad_coordinate_expr(void);
void p_quadrature_fem_var(void);
void p_quadrature_scalar_var(void);
void p_quadrature_interpolate(void);

/* statements */
void dimension_st(void);
void showmesh_st(void);
void domain_st(int n);
void subdomain_st(int n);
void region_with_meshmethod_st(int n);
void nodes_st(void);
void point_2d_st(void);
void refine_st(void);
void line_st(int n);

/* vars */
void var_int_st(int flag);
void var_int_with_value_st(int flag);
void var_double_st(int flag);
void var_double_with_value_st(int flag);
void var_userfunc_st(void);
void var_const_with_value_st(void);
void var_material_st(int n);
void var_fem_st(void);
void var_fem_with_dom_st(void);
void var_fem_with_restrictions_st(int n);
void var_fem_with_restrictions_and_dom_st(int n);
void var_ewise_st(void);
void var_ewise_with_cordinates_st(void);
void var_ewise_with_quadrature_st(void);

/* ewise coord helpers */
void push_ewise_cordinate_r(void);
void push_ewise_cordinate_s(void);
void push_ewise_cordinate_inc(void);
void push_ewise_cordinate_dat(int dim);

/* control / misc */
void Let_st(void);
void Let_at_st(int n);
void Let_in_st(int n);
void Let_on_st(int n);
void Goto_st(void);
void Label_st(void);
void L2_norm(void);
void MAX_norm(void);
void parse_adaptmesh(void);
void parse_adaptmesh_with_option(void);

/* output */
void Showvec_st(int mode);
void Showvec_st_with_setting(int settings);
void Showvec_file_st(int mode);
void Showvec_file_st_with_setting(int settings);
void Contour_st(int mode);
void Contour_st_with_setting(int settings);
void Contour_file_st(void);
void Contour_file_st_with_setting(int settings);
void Perspect_st(void);
void Perspect_st_with_setting(int settings);
void Displacement_st(void);
void Displacement_st_with_setting(int settings);
void Write_parse_init(void);
void Write_st(void);
void File_Write_parse_init(void);
void File_Write_st(void);
void Read_st(int n);
void Xplot_st(int n);
void Xplot_st_with_setting(int n, int settings);
void AVSoutput_st(int n);
void AVSnetwork_st(int n);
void plot_st(int n);
void time_plot_st(int n);

/* if */
void p_if_then(char *lhs, int cond_type);
void p_if_goto(char *lhs, int cond_type);
void p_else(void);
void p_endif(void);

/* write statement parts */
void write_st_expression(void);
void write_st_string(void);

/* solve */
void solve_parse_init(void);
void Make_SolveElement(void);
void p_solve_complete(void);
void p_solve_unknowns(int n);
void p_solve_domain(void);
void p_solve_subdomain(void);
void p_solve_quadrature_method(void);
void p_solve_boundary_quadrature(void);
void p_solve_linear_method(void);
void p_solve_isoparametric(void);
void p_solve_shape(void);
void p_solve_nonlinear(void);
void p_solve_symmetry(void);
void p_solve_initial(void);
void p_solve_eps(void);
void p_solve_newton_factor(void);
void p_solve_newton_times(void);

/* equations */
void p_EQ(void);
void p_WEQ(int x);
void p_EIGEN(void);
void p_FUNC(void);
void p_solve_test_function(void);
void p_solve_expression(void);
void p_solve_expression_with_quad_method(void);
void p_solve_boundary_term(void);
void p_solve_boundary_term_with_quad_method(void);

/* boundary conditions */
void p_ncond_init(void);
void p_ncond_edge(int n);
void p_dcond_var(void);
void p_dcond_expr(void);
void p_dcond_edge(int n);
void p_ncond_arg(void);

/* expression stack */
void exp_atom_push(char *a);
void exp_func_push(char *a);
void exp_array_push(char *a);
void exp_minus_push(void);
void exp_pl_push(void);
void exp_mi_push(void);
void exp_mu_push(void);
void exp_di_push(void);
void push_identifier_and_push(void);
void push_function_and_push(void);

/* from YaccMain.c */
void pop_push_inner_points(int inner_parameters);

#endif

