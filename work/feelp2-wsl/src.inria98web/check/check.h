/*
 * prototype for check routine
 *
 * check routines
 *
 * modoernize 2026/01/24
 *
 */


void region_subdomain_check();    /* subdomain�˴ؤ�������å�*/
void region_domain_check();       /* ��region̾�˥��֥꤬�ʤ����� */
void point_check_order();         /* �����μ��̤���Ͽ */
void refine_check();              /* refine check, This must after point order*/
void fem_var_element_check();     /* femʸ�ǻ��ꤵ��Ƥ���element��̵ͭ�γ�ǧ�� */
void ewise_var_check();        /* ewise�ѿ�θ��� */
void var_fem_ewise_datmake();
void var_register();
void var_reserved_check();
void var_const_pretoinf();
void element_check();
void quad_check();                    /* dbg: CAUTION: ���ߤ�pre_to_inf�Τ� */
void scheme_gotolabel_check();
void scheme_if_check();
void scheme_rw_check();
void scheme_plot_check();
void scheme_contour_check();
void scheme_displacement_check();
void scheme_perspect_check();
void scheme_showvec_check();
void solve_check_main();
void scheme_let_check();
void scheme_norm_check();
void scheme_adaptmesh_check();
void avs_check();

void element_chk_pretoinf();

void var_register(void);

void var_reserved_check(void);

int  is_diff_op(char *name);
int  is_fort77_func(char *name);
int  is_fort77_keyword(char *name);
int  is_feel_system_var(char *name);
int  is_feel_test_var(char *name);

void register_user_func(char *name);
int  is_feel_user_func(char *name);


void  solve_chk_var();
void  solve_chk_initial();
void  solve_chk_bd_var();
void  solve_chk_var_vs_domain();    /* ��solve_element�ǻ��ꤵ��Ƥ���domain */
void  solve_chk_quad_method();  /* ���ꤵ��Ƥ��������ʬˡ���������� */
void  solve_chk_shape_function();   /* ��solve_element�η����Ѵ��ؿ�λ��� */
void  solve_chk_test_function();    /* ��ؿ�˴ؤ��븡����Ԥ� */
void  solve_chk_only_neumann();     /* �Υ��ޥ��ﱦ�դˤΤ߽и�����fem�ѿ�� */
void  solve_chk_boundary();
void  solve_chk_DirichletData();    /* Dirichlet���˴ؤ��륨�顼���� */
void  solve_chk_NeumannData();
void  solve_chk_EigenProblem();

int get_fem_var_no_byname(char *);
int get_ewise_var_no_byname(char *);
int how_many_avsnetworks();
int is_avsnetwork_member( char *name );
int how_many_avsoutputs();
