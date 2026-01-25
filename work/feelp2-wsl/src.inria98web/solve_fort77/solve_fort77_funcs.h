/*
 *  solve_fort77_funcs.h
 *
 *   modernize 2026/01/25
 *
 *
 *
 */


void ctrl77_subdomain(FILE *fp,int elemg,Solve *solve_ptr,ElementFORT77 **elem77_ptrptr);
void make_collec_sol(int solve_no,SolveElement *solve_element_ptr);
void make_ecal_analytic(FILE *fp,int solve_no,int elem_no,int quad_no,SolveElement *solve_element_ptr);
void make_ecal_numerical(FILE *fp,int solve_no,int elem_no,int quad_no,SolveElement *solve_element_ptr);
void make_ecal_numerical_nonlinear(FILE *fp,int solve_no,int elem_no,int quad_no,SolveElement *solve_element_ptr);
void make_ecal_elem_div(char *buf,FILE *fp);
void make_elem_lisp( FILE *fp , Solve *solve_ptr , SolveElement *solve_element_ptr);
void make_test_funcs_vect( FILE *fp , char *funcs[] , int freedom[] ,int equations);
void make_coff_vect( FILE *fp, int n);
void make_unknown_eval_var(FILE *fp , char *name ,int start ,char *element_name,int freedom);
void make_known_eval_var(FILE *fp  ,char *name , char *domain_name );
void make_fem_funcs_bound(FILE *fp , char *element_name );
void make_weak_eq_WEQ(int solve_no ,int elem_no,int no ,char *quad_method,SolveElement *solve_element_ptr,FILE *fp);
void MakeEdgeBasis_IEDPIENP(char *name ,EdgeBasis * eb_ptr ,SolveElement *solve_element_ptr );
void ncond_element_parameter(FILE * fp, SolveElement *solve_element_ptr);
void make_fem_funcs_co_bound(FILE *fp , char *element_name ,int n);
void make_elem_commons();


