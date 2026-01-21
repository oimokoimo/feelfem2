/*
 *  Numerical Simulation Language for Finite Element Method
 *
 *  FILE fem.y   Date          1991/12/24
 *               LastModified  1992/01/24
 *               Version       0.2
 *
 *  For feel p2  version       1993/05/25
 *               AVS version   1998/09/03  add avsint,avsdouble,avsoutput
 */

%code requires {
  int yylex(void);
  void yyerror(const char *);
}


/* declarations */
%{
#include <stdio.h>
#include "parser_actions.h"

    extern int parameters;   /* to count the number of  parameter */
    extern int expressions;  /* to count the items in expression  */
    extern int settings;
    extern int inner_parameters; /* to count the number of inner points */
    extern int condition_type;   /* condition type */

    char *tmp_pop;               /* debug for DEC/Alpha AXP/ OSF/1(941024) */
    extern char *get_expr_structure();
    extern char *if_left_ptr;
    char *pop(void);            /* modernize 2026/01/21 */
    void push(char *s);         /* modernize 2026/01/21 */

/* y.tab.c ¿¿¿¿¿¿¿ ¿¿¿¿¿¿¿ ¿¿¿ */
/* move to %code block modernize */

/* runtime */
void feel_exec_main(void);
void debug_terminate(void);
void feel_terminate(void);

/* ¿¿¿¿¿¿¿ void ¿¿¿¿¿¿¿¿¿¿¿¿¿¿ */
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

void dimension_st(void);
void showmesh_st(void);
void domain_st(int n);
void subdomain_st(int n);
void region_with_meshmethod_st(int n);
void nodes_st(void);
void point_2d_st(void);
void refine_st(void);
void line_st(int n);

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

void push_ewise_cordinate_r(void);
void push_ewise_cordinate_s(void);
void push_ewise_cordinate_inc(void);
void push_ewise_cordinate_dat(int dim);

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

void p_if_then(char *lhs, int cond_type);
void p_if_goto(char *lhs, int cond_type);
void p_else(void);
void p_endif(void);

void write_st_expression(void);
void write_st_string(void);

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

void p_EQ(void);
void p_WEQ(int x);
void p_EIGEN(void);
void p_FUNC(void);
void p_solve_test_function(void);
void p_solve_expression(void);
void p_solve_expression_with_quad_method(void);
void p_solve_boundary_term(void);
void p_solve_boundary_term_with_quad_method(void);

void p_ncond_init(void);
void p_ncond_edge(int n);
void p_dcond_var(void);
void p_dcond_expr(void);
void p_dcond_edge(int n);
void p_ncond_arg(void);

void exp_atom_push(char *a);
void push_identifier_and_push(void);
void push_function_and_push(void);
void exp_func_push(char *a);
void exp_array_push(char *a);
void exp_minus_push(void);
void exp_pl_push(void);
void exp_mi_push(void);
void exp_mu_push(void);
void exp_di_push(void);

void pop_push_inner_points(int inner_parameters);

%}



/*------- BASIC TOKENS -------------------*/
%token  IDENTIFIER       /* variable name */
%token  STRING           /* string        */

/*------- tokens for MESH BLOCK ----------*/
%token  DIMENSION        /* "dimension"   */
%token  MESH             /* "mesh"        */
%token  POINT            /* "point"       */
%token  REFINE           /* "refine"      */
%token  EDGE             /* "edge"        */
%token  CURVE            /* "curve"       */
%token  DOMAIN           /* "domain"      */
%token  REGION           /* "region"      */
%token  RECTANGLE        /* "rectangle"   */
%token  NODES            /* "nodes"       */
%token  SHOWMESH         /* "showmesh"    */
%token  BOUNDARY         /* "boundary"    */
%token  NUMBER           /* "number"      */
%token  SUBDOMAIN        /* "subdomain"   */

/*------- tokens for ELEMENT BLOCK -------*/
%token  ELEMENT          /* "element"     */
%token  QUADRATURE       /* "quadature"  */

/*------- tokens for VAR BLOCK -----------*/
%token  VAR              /* "var"         */
%token  CONST            /* "const"       */
%token  DOUBLE           /* "double"      */
%token  AVSDOUBLE        /* "avsdouble"   */ 
%token  FEM              /* "fem"         */
%token  EWISE            /* "ewise"       */
%token  INT              /* "int"         */
%token  AVSINT           /* "avsint"      */
%token  MATERIAL         /* "material"    */
%token  FUNCTION         /* "function"    */

/*------- tokens for SCHEME BLOCK --------*/
%token  SCHEME           /* "scheme"      */
%token  SOLVE            /* "solve"       */
%token  ISOPARAMETRIC    /* "isoparametric" */
%token  SHAPE            /* "shape"       */
%token  SYMMETRY         /* "symmetry"    */
%token  NONLINEAR        /* "nonlinear"   */
%token  EPS              /* "set-eps"     */
%token  STRATEGY         /* "strategy"    */
%token  INITIAL_VALUE    /* "initial"     */
%token  EQ               /* "eq:"         */
%token  WEQ              /* "weq:"        */
%token  EIGEN            /* "eigen:"      */
%token  FUNC             /* "func:"       */
%token  ATMARK           /* "@"           */
%token  METHOD           /* "method:"     */
%token  LINEAR           /* "linear"      */
%token  DBC              /* "dbc:"        */
%token  NBC              /* "nbc:"        */
%token  AT               /* "at"          */
%token  IN               /* "in"          */
%token  ON               /* "on"          */
%token  GOTO             /* "goto"        */
%token  LET              /* "let"         */
%token  SHOWVEC          /* "showvec"     */
%token  SHOWVEC_FILE     /* "showvec-file"*/
%token  CONTOUR          /* "contour"     */
%token  CONTOUR_FILE     /* "contour-file"*/
%token  XPLOT            /* "xplot"       */
%token  PLOT_FILE        /* "plot-file"   */
%token  PERSPECT         /* "perspect"    */
%token  WRITE            /* "write"       */
%token  READ             /* "read"        */
%token  IF               /* "if"          */
%token  THEN             /* "then"        */
%token  ELSE             /* "else"        */
%token  ENDIF            /* "endif"       */
%token  FILE_WRITE       /* "fwrite"      */
%token  TIME_PLOT_FILE   /* "time-plot-file" */
%token  NEWTON_FACTOR    /* "newton-factor"  */
%token  NEWTON_TIMES     /* "newton-times"   */
%token  DISPLACEMENT     /* "displacement" */
%token  MAXNORM          /* "MAXnorm"     */
%token  L2NORM           /* "L2NORM"      */
%token  ADAPTMESH        /* "adaptmesh"   */
%token  AVSOUTPUT        /* "avsoutput"   */
%token  AVSNETWORK       /* "avsnetwork"  */

/*------- GENERAL symbols ----------------*/
%token  lp               /*  '{'          */
%token  rp               /*  '}'          */

%token  lk               /*  '['          */
%token  rk               /*  ']'          */

%token  lb               /*  '('          */
%token  rb               /*  ')'          */

%token  num              /*  number       */
%token  co               /*  ','          */
%token  sc               /*  ';'          */
%token  cc               /*  ':'          */

%token  eq               /*  '='          */
%token  pl               /*  '+'          */
%token  mi               /*  '-'          */
%token  mu               /*  '*'          */
%token  di               /*  '/'          */

%token  equal            /*  '=='         */
%token  le               /*  '<='         */
%token  lt               /*  '<'          */
%token  ge               /*  '>='         */
%token  gt               /*  '>'          */
%token  ne               /*  '!='         */

/*----- procedence table -----*/
%right eq
%left  pl mi
%left  mu di
%%

program            
  :       /* empty (initialize)?  */
  |   sections  { /* debug_start(); (Ãí°Õ¡ªfeel_exec_main¤ÎÃæ¤Ë°Ü¤·¤Þ¤·¤¿¡£)*/
                  feel_exec_main();
	          debug_terminate();
	          feel_terminate();  }

sections
  : section
  | sections section

section
  : mesh_definition                 /* ·Á¾õÄêµÁ */
  | element_definition              /* Í×ÁÇÄêµÁ */
  | var_definition                  /* ÊÑ¿ôÄêµÁ */
  | quadrature_definition           /* ÀÑÊ¬Ë¡ÄêµÁ */ 
  | scheme_definition               /* ¥¹¥­¡¼¥àÄêµÁ */


/***********************************************/
/*  Í×ÁÇÄêµÁ   elementÊ¸ ¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý*/
/***********************************************/
 /*  element Í×ÁÇÌ¾ [¿Þ·ÁÍ×ÁÇ] {
 *        double  ÊÑ¿ôÌ¾ = É¾²Á¼° ;
 *        const   ÊÑ¿ôÌ¾ = É¾²Á¼° ;
 *        (ºÂÉ¸,ºÂÉ¸,...)     : ´ðÄì´Ø¿ô ;
 *        (ºÂÉ¸,ºÂÉ¸,...)[dn] : ´ðÄì´Ø¿ô ;  ¥¨¥ë¥ß¡¼¥È¥¿¥¤¥×
 *               .....
 *}
 *
 *  element Í×ÁÇÌ¾ (¹´Â«femÊÑ¿ôÌ¾[Í×ÁÇ¥¿¥¤¥×])[¿Þ·ÁÍ×ÁÇ] {
 *        (ºÂÉ¸,ºÂÉ¸,...)     : ´ðÄì´Ø¿ô ;
 *        (ºÂÉ¸,ºÂÉ¸,...)[dn] : ´ðÄì´Ø¿ô ;  ¥¨¥ë¥ß¡¼¥È¥¿¥¤¥×
 *               .....
 *}
 */
element_definition 
  :  ELEMENT IDENTIFIER lk {element_parse_init();} IDENTIFIER {p_element_shape();} rk lp basis_functions rp { p_element_complete(); }
  |  ELEMENT IDENTIFIER lb {element_parse_init();} fem_var_parameters rb lk IDENTIFIER {p_element_shape();}rk lp basis_functions rp { p_element_complete(); }

basis_functions
  : basis_function                   
  | basis_functions basis_function   

basis_function
  : lb cordinate co cordinate rb lk { p_element_cordinate_2dim(); }diff_ops {p_basis_type(); } rk cc expression sc 
    { p_basis_complete(); }
  | lb cordinate co cordinate rb cc { p_element_cordinate_2dim(); }expression sc
    { p_basis_complete(); }
  | lb cordinate rb cc {p_element_cordinate_1dim(); } expression sc
    { p_basis_complete(); }
  | DOUBLE elem_double_identifiers sc 
  | CONST  elem_const_identifiers  sc 
  | IDENTIFIER  eq expression sc { p_element_let(); }

elem_double_identifiers
  : IDENTIFIER                 { p_element_double(); }
  | IDENTIFIER eq expression   { p_element_double_with_expr(); }
  | elem_double_identifiers co IDENTIFIER     { p_element_double(); }
  | elem_double_identifiers co IDENTIFIER eq expression 
                                       {p_element_double_with_expr(); }

elem_const_identifiers
  : IDENTIFIER                 { p_element_const(); }
  | IDENTIFIER eq expression   { p_element_const_with_expr(); }
  | elem_const_identifiers co IDENTIFIER     { p_element_const(); }
  | elem_const_identifiers co IDENTIFIER eq expression 
                                       {p_element_const_with_expr(); }
diff_ops
  : IDENTIFIER
/*  | DN { push("dn");   DN¤Îtoken¤ä¤ó¤Ô */ /* DN¤Ï¥×¥Ã¥·¥å¤µ¤ì¤Ê¤¤°Ù */ 

cordinate
  : num          { p_node_cordinate(1); } 
  | num di num   { p_node_cordinate(2); }

fem_var_parameters
  : fem_var_parameter
  | fem_var_parameters co fem_var_parameter

fem_var_parameter
  : IDENTIFIER lk IDENTIFIER rk { p_element_fem_restrains(); }

/*
 *    ¿ôÃÍÀÑÊ¬Ë¡ quadratureÊ¸
 * 
 *
 *    quadrature ¿ôÃÍÀÑÊ¬Ì¾¾Î[ÎÎ°èÌ¾¾Î] {
 *
 *    quadrature ¿ôÃÍÀÑÊ¬Ì¾¾Î(°ú¤­¿ô¤È¤Ê¤ëÊÑ¿ô¤ÎÀë¸À)[ÎÎ°èÌ¾¾Î] {
 *                                    ¢­
 *                               ÊÑ¿ôÌ¾[Í×ÁÇÌ¾]{,.....}{{,ÊÑ¿ôÌ¾}{,,,,}}
 *                        
 *    const ÊÑ¿ôÌ¾: ¼° ;    ÀÑÊ¬ÅÀ¡¢½Å¤ß¤Î»ØÄê¤ËÍÑ¤¤¤ë
 *                        
 *   (ÀÑÊ¬ÅÀ,ÀÑÊ¬ÅÀ): ¼°;   ½Å¤ß
 *
 *   ÊÑ¿ôÌ¾(ÀÑÊ¬ÅÀ,ÀÑÊ¬ÅÀ): É¾²Á¼°;   °ú¤­¿ô¤Ë»ØÄê¤·¤¿fem,ewise,doubleÊÑ¿ô¤ÎÊä´ÖË¡
 *
 *   }
 *
 */
quadrature_definition
  :  QUADRATURE IDENTIFIER lk {quadrature_parse_init();} IDENTIFIER {p_quadrature_shape();} rk lp quadrature_components rp { p_quadrature_complete(); }
  |  QUADRATURE IDENTIFIER lb {quadrature_parse_init();} quadrature_var_parameters rb lk IDENTIFIER {p_quadrature_shape();}rk lp quadrature_components rp { p_quadrature_complete(); }

quadrature_components
  : quadrature_component
  | quadrature_components  quadrature_component

quadrature_component    /* ¿ôÃÍÀÑÊ¬»ØÄê¤Î³Æ¹àÌÜ */
  : lb quadrature_coordinate rb cc                 /* °ì¼¡¸µÀÑÊ¬ÅÀºÂÉ¸»ØÄê*/
    { p_quadrature_coordinate_1dim(); } expression sc 
    { p_quadrature_component(); }
  | lb quadrature_coordinate co quadrature_coordinate rb cc   /* £²¼¡¸µ */
    { p_quadrature_coordinate_2dim(); } expression sc    
    { p_quadrature_component(); } 
  | lb quadrature_coordinate co quadrature_coordinate co      /* £³¼¡¸µ */
       quadrature_coordinate rb cc 
    { p_quadrature_coordinate_3dim(); } expression sc 
    { p_quadrature_component(); } 
  | IDENTIFIER  lb {p_quadrature_identifier(); }         /* ÊÑ¿ôÆâÁÞË¡ */
    quadrature_interpolate
  | CONST IDENTIFIER eq expression sc       {p_quadrature_const(); } /* Äê¿ô */
  | DOUBLE quadrature_double_identifiers sc  /* ¼Â¿ôÊÑ¿ôÀë¸À   */
  | IDENTIFIER eq expression sc             {p_quadrature_let_st();} /* ÂåÆþ */

quadrature_double_identifiers
  : IDENTIFIER  { p_quad_double_identifier(); }
  | IDENTIFIER eq expression { p_quad_double_identifier_with_expr(); } 
  | quadrature_double_identifiers co IDENTIFIER {p_quad_double_identifier(); }
  | quadrature_double_identifiers co 
           IDENTIFIER eq expression { p_quad_double_identifier_with_expr(); }

quadrature_var_parameters
  : quadrature_var_parameter
  | quadrature_var_parameters co quadrature_var_parameter

quadrature_coordinate
  : expression { p_quad_coordinate_expr(); }

quadrature_var_parameter
  : IDENTIFIER lk IDENTIFIER rk { p_quadrature_fem_var(); }
  | IDENTIFIER                  { p_quadrature_scalar_var(); }

quadrature_interpolate
  : quadrature_coordinate rb cc 
    { p_quadrature_coordinate_1dim(); } expression sc
    { p_quadrature_interpolate(); }
  | quadrature_coordinate co quadrature_coordinate rb cc 
    { p_quadrature_coordinate_2dim(); } expression sc
    { p_quadrature_interpolate(); }
  | quadrature_coordinate co quadrature_coordinate co 
    quadrature_coordinate rb cc 
    { p_quadrature_coordinate_3dim(); } expression sc
    { p_quadrature_interpolate(); }


/*  ·Á¾õÄêµÁ    ¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý*/
/*--------------------------------------------------------------------
 *  meshÀ¸À®´Ø·¸¹½Ê¸²òÀÏ¥Ñ¡Á¥µ¤Î¥×¥í¥°¥é¥àµ¬Ìó
 *
 *  ½ôÄê¿ôÃÍ¤Ï  ../feel_def/feel_def.h  ¤ËÄêµÁ¤¹¤ë
 *  ¹½Â¤ÂÎÅù¤Ï  ³Æ´Ø¿ô¼«ÂÎ¤ÇÀë¸À¤¹¤ë
 *  ´Ø¿ôÌ¾¤Ï    yacc¤ÎÄ¾¸Æ¤Ó¤À¤·´Ø¿ô¤Ï ´Ø¿ôÌ¾¤ÎºÇ¸å¤Ë _st ¤òÉÕ¤±¤ë
 *  ·èÄê        1993/06/03              
 *--------------------------------------------------------------------
 *  dimensionÊ¸ ¼¡¸µ¤ÎÀßÄê(ÄÌ¾ï¤Ï£²)
 *
 *    dimension ¼¡¸µ;
 *--------------------------------------------------------------------
 *  nodesÊ¸     ³ÆÎÎ°è¤ÎÀáÅÀ¿ô¤ò»ØÄê¤¹¤ë
 *
 *    nodes ÎÎ°èÌ¾(ÀáÅÀ¿ô) {,ÎÎ°èÌ¾(ÀáÅÀ¿ô),...};
 *--------------------------------------------------------------------
 *  showmeshÊ¸  À¸À®¤·¤¿¥á¥Ã¥·¥å¤òÉ½¼¨¤¹¤ë
 *
 *    showmesh;
 *--------------------------------------------------------------------
 *  pointÊ¸     ÅÀ¤Î»ØÄê¤¹¤ë
 *
 *    point ÅÀ¤ÎÌ¾Á°(xºÂÉ¸,yºÂÉ¸){,ÅÀ¤ÎÌ¾Á°(xºÂÉ¸,yºÂÉ¸),...};
 *--------------------------------------------------------------------
 *  refine statement
 *
 *    refine a(factor);
 *--------------------------------------------------------------------
 *  lineÊ¸      Àþ¤ò»ØÄê¤¹¤ë
 *
 *    line Àþ¤ÎÌ¾Á°(line¤ò¹½À®¤¹¤ëÅÀ¤Î¥ê¥¹¥È);
 *--------------------------------------------------------------------
 *  domainÊ¸    ·×»»ÎÎ°è¤Î»ØÄê
 *
 *    domain Ì¾Á°(regionÌ¾¤Î¥ê¥¹¥È);
 *--------------------------------------------------------------------
 *  regionÊ¸    ÎÎ°è·Á¾õ¡¢´ðËÜÍ×ÁÇ·Á¾õ¤Î»ØÄê
 *
 *    region Ì¾Á°[tri/rect](ÅÀ¤Î¥ê¥¹¥È,...{,[·êÎÎ°è¤ÎÅÀ¤Î¥ê¥¹¥È],...})
 *--------------------------------------------------------------------
 *  subdomainÊ¸ ÉôÊ¬ÎÎ°è½¸¹ç¤ÎÄêµÁ
 *    
 *    subdomain Ì¾Á°(ÎÎ°è¤Î¥ê¥¹¥È)
 *--------------------------------------------------------------------
 *  numberÊ¸    ÎÎ°è,¶­³¦ÈÖ¹æ¤ÎÄêµÁ 
 *
 *  region number Ì¾¾Î(ÈÖ¹æ);
 *  line number   Ì¾¾Î(ÈÖ¹æ);
 *
 *--------------------------------------------------------------------
 */
mesh_definition 
  :  MESH lp mesh_statements rp     

mesh_statements
  :  mesh_statement
  |  mesh_statements mesh_statement

mesh_statement
  :  /* empty */                      /* ¶õÊ¸ÆÉ¤ßÈô¤Ð¤·       */
  |  DIMENSION num sc { dimension_st(); }
  |  NODES   nodes_definitions sc     /* ³ÆÎÎ°è¤ÎÀáÅÀ¿ô¤ÎÄêµÁ */
  |  SHOWMESH sc                      /* À¸À®¥á¥Ã¥·¥å¤ÎÉ½¼¨   */
               { showmesh_st(); }
  |  POINT   point_definitions sc
  |  REFINE  refine_definitions sc
  |  EDGE    line_definitions sc
  |  DOMAIN  IDENTIFIER lb parameter_list rb sc   /* domainÊ¸ */
               { domain_st(parameters); parameters = 0;}
  |  SUBDOMAIN  IDENTIFIER lb parameter_list rb sc   /* domainÊ¸ */
               { subdomain_st(parameters); parameters = 0;}
  |  REGION  IDENTIFIER lk IDENTIFIER rk lb edge_point_lists rb sc
               { region_with_meshmethod_st(parameters); parameters = 0;}
/*  |  REGION  IDENTIFIER lb edge_point_lists rb sc   region¤Ë¥á¥Ã¥·¥åÀ¸À®
                                                      ÊýË¡»ØÄê¤ÏÉ¬¿Ü(7/16ÊÑ¹¹)
               { region_st(parameters); parameters = 0;} */
/*
  |  CURVE   IDENTIFIER lb parameter_list rb lk IDENTIFIER rk sc
               { curve_st();}
  |  RECTANGLE IDENTIFIER lb IDENTIFIER co IDENTIFIER co IDENTIFIER co IDENTIFIER rb sc
               { rectangle_st();}
*/

nodes_definitions   /* nodes Ê¸¤ÎËÜÂÎ */
  : IDENTIFIER lb num rb                      {nodes_st(); }
  | nodes_definitions co IDENTIFIER lb num rb {nodes_st(); }

point_definitions   /* point Ê¸¤ÎËÜÂÎ */
  : IDENTIFIER lb num co num rb { point_2d_st();}
  | point_definitions co IDENTIFIER lb num co num rb { point_2d_st();}

refine_definitions  /* refine statement */
  : IDENTIFIER lb num rb { refine_st(); }
  | refine_definitions co IDENTIFIER lb num rb { refine_st();}

line_definitions
  : IDENTIFIER lb parameter_list rb { line_st(parameters); parameters = 0;}
  | line_definitions co IDENTIFIER lb parameter_list rb 
               { line_st(parameters); parameters = 0; }

/*  ÊÑ¿ôÄêµÁ    ¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý*/
/*--------------------------------------------------------------------
 *  ÊÑ¿ôÄêµÁ´Ø·¸¹½Ê¸²òÀÏ¥Ñ¡Á¥µ¤Î¥×¥í¥°¥é¥àµ¬Ìó
 *
 *  ·èÄê        1993/06/03              
 *--------------------------------------------------------------------
 *  doubleÊ¸    ÇÜÀºÅÙ·¿ÊÑ¿ô¤ÎÀë¸À
 *              ÇÜÀºÅÙ·¿¤ÎÊÑ¿ô¤Ï¡¢¥á¥¤¥ó¥ë¡¼¥Á¥ó¾å¤ÇÄêµÁ¤µ¤ì¤ë
 *              ¤Þ¤¿¡¢½é´üÃÍ¤ò»ØÄê¤¹¤ë¤³¤È¤â¤Ç¤­¤ë
 *              ½é´üÃÍ¤Ï¡¢¥Ç¡¼¥¿ÆþÎÏ¸å¡¢¥á¥¤¥ó¥ë¡¼¥Á¥ó¾å¤ÇÂåÆþ¤¹¤ë
 *  double  ÊÑ¿ôÌ¾ {{= ½é´üÃÍ }, .... };
 *--------------------------------------------------------------------
 *  intÊ¸       À°¿ô·¿ÊÑ¿ô¤ÎÀë¸À
 *       
 *  int  ÊÑ¿ôÌ¾ {{= ½é´üÃÍ }, .... };
 *--------------------------------------------------------------------
 *  constÊ¸     Äê¿ô·¿ÊÑ¿ô¤ÎÀë¸À
 *              Äê¿ô·¿ÊÑ¿ô¤ÎÀë¸À¤Ï°ÅÌÛ¤Î·¿Àë¸À¤ò¼é¤é¤Ê¤±¤ì¤Ð¤¤¤±¤Ê¤¤
 *  
 *  const ÊÑ¿ôÌ¾ = Äê¿ôÃÍ {, ÊÑ¿ôÌ¾ = Äê¿ôÃÍ, ... };
 *--------------------------------------------------------------------
 *  femÊ¸       femÊÑ¿ô¤ÎÀë¸À femÊÑ¿ô¤Ï¡¢´ðÄì´Ø¿ô¤È¶¦¤Ë»ØÄê¤¹¤ë
 *              femÊÑ¿ô¤Ï´ðËÜÍ×ÁÇ·Á¾õ¤ËÂÐ¤·¤Æ°ì¤Ä¤Î´ðÄì´Ø¿ô¤Î¤ß»ØÄê¤Ç¤­¤ë
 *  
 *  fem ÊÑ¿ôÌ¾[´ðÄì´Ø¿ôÌ¾]{[domainÌ¾]};
 *  
 *  
 *  fem ÊÑ¿ôÌ¾[´ðÄì´Ø¿ôÌ¾(¹´Â«ÊÑ¿ôÌ¾)]{[domainÌ¾]};
 *      
 *      
 *  °ì¤Ä¤ÎfemÊÑ¿ô¤ËÂÐ¤·¤Æ´ðËÜÍ×ÁÇ·Á¾õ¤Þ¤¿¤ÏdomainËè¤Ë´ðÄì´Ø¿ô¤ò»ØÄê¤¹¤ë¾ì¹ç¤Ï
 *  ¤³¤ÎÀë¸À¤ò·«¤êÊÖ¤¹¡£    
 *--------------------------------------------------------------------
 *  ewiseÊ¸     ewiseÊÑ¿ô(Í×ÁÇ»Ø¸þÊÑ¿ô)¤ÎÀë¸À
 *              ÊÑ¿ôÌ¾¤È¶¦¤Ë³ÆÍ×ÁÇ¤Ç¤ÎÃÍ¤òµá¤á¤ëºÂÉ¸¤â»ØÄê¤¹¤ë¡£
 *              ¾ÊÎ¬»þ¤Ïdefault¤Î°ÌÃÖ¤Ç·×»»¤¹¤ë
 *  
 *              ewiseÊÑ¿ô¤Ï¡¢domain¤ËÂÐ¤·¤Æ°ì¤ÄÄê¤Þ¤ë¡£
 *              Ê£¿ô¤Îdomain¤Ë¤Þ¤¿¤¬¤ë¾ì¹ç¡¢
 *  
 *  ewise ÊÑ¿ôÌ¾[domainÌ¾];
 *  ewise ÊÑ¿ôÌ¾[domainÌ¾]:(xºÂÉ¸,yºÂÉ¸){,(xºÂÉ¸,yºÂÉ¸),...};
 *  ewise ÊÑ¿ôÌ¾[domainÌ¾]:¿ôÃÍÀÑÊ¬Ì¾;
 *  
 *  °ì¤Ä¤ÎewiseÊÑ¿ô¤ËÂÐ¤·¤ÆÊ£¿ô¤Î¤³¤ÎÀë¸À¤ò¼Â¹Ô¤·¤Æ¤â¤è¤¤¡Úº£¤ÏÂÌÌÜ¡Û
 *  ¤¿¤À¤·¡¢¤â¤Á¤í¤ó½ÅÊ£¤¬¤¢¤Ã¤Æ¤Ï¤¤¤±¤Ê¤¤
 *--------------------------------------------------------------------
 *  materialÊ¸  materialÊÑ¿ô(Í×ÁÇ¤ÎMATNO¤Ë¤è¤Ã¤ÆÍ×ÁÇËè¤Ë·è¤Þ¤ëÊªÍýÎÌ)
 *              ¤òÉ½¤¹ÊÑ¿ô¤ÎÀë¸À
 *  
 *  matreial ÊÑ¿ôÌ¾[MATNO=1¤Î»þ¤ÎÃÍ,MATNO=2¤Î»þ¤ÎÃÍ,...];
 *  
 *           ¼ÂºÝ¤ÎMATNO¤¬¤³¤³¤Ç»ØÄê¤·¤¿ÃÍ¤è¤êÂç¤­¤Ê¾ì¹ç¤ÏÉÔÅÔ¹ç¤¬À¸¤¸¤ë
 *--------------------------------------------------------------------
 *  functionÊ¸  ¥æ¡¼¥¶ÄêµÁ¤ÎFORTRAN´Ø¿ôÌ¾¤ò»ØÄê¤¹¤ë
 *
 *              ¤³¤ÎÊ¸¤ÎÌÜÅª¤Ï¡¢´Ø¿ôÀë¸ÀÍ­Ìµ¥Á¥§¥Ã¥¯¤ÎºÝ¤Î¥Á¥§¥Ã¥¯²óÈò
 *              ¤ª¤è¤Ó¡¢Makefile¤Ø¤ÎÅÐÏ¿¤Ë¤¢¤ê¤Þ¤¹¡£
 *--------------------------------------------------------------------
 */
var_definition
  :  VAR lp var_statements rp

var_statements
  : var_statement
  | var_statements var_statement

var_statement
  : INT       int_identifiers      sc   /* À°¿ôÊÑ¿ô¤ÎÀë¸À */
  | AVSINT    avsint_identifiers   sc   /* avsint declaration */
  | EWISE     ewise_definitions         /* Í×ÁÇ»Ø¸þÊÑ¿ô¤ÎÀë¸À */
  | CONST     const_identifiers    sc   /* Äê¿ôÊÑ¿ô¤ÎÀë¸À */
  | FEM       fem_definitions      sc   /* fem ÊÑ¿ô¤ÎÀë¸À */
  | MATERIAL  material_definitions sc   /* Êª¼ÁÊÑ¿ô¤ÎÀë¸À */
  | DOUBLE    double_identifiers   sc   /* ÇÜÀºÅÙÊÑ¿ô¤ÎÀë¸À */
  | AVSDOUBLE avsdouble_identifiers   sc   /* avsdouble declaration */
  | FUNCTION  userfunc_identifiers sc   /* ¥æ¡¼¥¶»ØÄê´Ø¿ô¤ÎÀë¸À */

int_identifiers         /* À°¿ô·¿ÊÑ¿ô¤ÎÀë¸À */
  : IDENTIFIER          { var_int_st(0); }
  | IDENTIFIER eq num   { var_int_with_value_st(0); }
  | int_identifiers co IDENTIFIER { var_int_st(0);}
  | int_identifiers co IDENTIFIER eq num { var_int_with_value_st(0); }

avsint_identifiers         /* À°¿ô·¿ÊÑ¿ô¤ÎÀë¸À(AVS) */
  : IDENTIFIER          { var_int_st(1); }
  | IDENTIFIER eq num   { var_int_with_value_st(1); }
  | avsint_identifiers co IDENTIFIER { var_int_st(1);}
  | avsint_identifiers co IDENTIFIER eq num { var_int_with_value_st(1); }

double_identifiers      /* ÇÜÀºÅÙÊÑ¿ô¤ÎÀë¸À */
  : IDENTIFIER          { var_double_st(0); }
  | IDENTIFIER eq num   { var_double_with_value_st(0); }
  | double_identifiers co IDENTIFIER { var_double_st(0);}
  | double_identifiers co IDENTIFIER eq num { var_double_with_value_st(0); }

avsdouble_identifiers      /* ÇÜÀºÅÙÊÑ¿ô¤ÎÀë¸À(AVS) */
  : IDENTIFIER          { var_double_st(1); }
  | IDENTIFIER eq num   { var_double_with_value_st(1); }
  | avsdouble_identifiers co IDENTIFIER { var_double_st(1);}
  | avsdouble_identifiers co IDENTIFIER eq num { var_double_with_value_st(1); }

userfunc_identifiers
  : IDENTIFIER                         {var_userfunc_st(); }
  | userfunc_identifiers co IDENTIFIER {var_userfunc_st(); }

const_identifiers      /* Äê¿ôÊÑ¿ô¤ÎÀë¸À */
  : IDENTIFIER eq expression   { var_const_with_value_st(); }
  | const_identifiers co IDENTIFIER eq expression {var_const_with_value_st(); }

material_definitions
  : IDENTIFIER lk num_parameter_list rk {var_material_st(parameters);
				     parameters = 0;               }

fem_definitions        /* fem ÊÑ¿ô¤ÎÀë¸À */
  : IDENTIFIER lk IDENTIFIER rk                    { var_fem_st(); }
  | IDENTIFIER lb IDENTIFIER rb lk IDENTIFIER rk   { var_fem_with_dom_st(); }
  | IDENTIFIER lk IDENTIFIER lb parameter_list rb rk
               {  var_fem_with_restrictions_st(parameters); parameters = 0; }
  | IDENTIFIER lb IDENTIFIER rb lk IDENTIFIER lb parameter_list rb rk 
    {  var_fem_with_restrictions_and_dom_st(parameters); parameters = 0; }
  | fem_definitions co IDENTIFIER lk IDENTIFIER rk { var_fem_st(); }
  | fem_definitions co IDENTIFIER lb IDENTIFIER rb lk IDENTIFIER rk
                                  { var_fem_with_dom_st(); }
  | fem_definitions co IDENTIFIER lk IDENTIFIER lb parameter_list rb rk
               {  var_fem_with_restrictions_st(parameters); parameters = 0; }
  | fem_definitions co IDENTIFIER lb IDENTIFIER rb lk IDENTIFIER lb parameter_list rb rk 
       {  var_fem_with_restrictions_and_dom_st(parameters); parameters = 0; }

ewise_definitions      /* ewise ÊÑ¿ô¤ÎÀë¸À +*/
/* ¥Ç¥Õ¥©¥ë¥ÈÉ¾²ÁÅÀ°ÌÃÖ¤Î¤ß¤Ç¤ÎewiseÊÑ¿ôÀë¸À */
  : IDENTIFIER lk IDENTIFIER rk sc {var_ewise_st(); parameters = 0;}
/* ÍÛ¤ÊÉ¾²ÁÅÀ¤Îµ­½Ò */
  | IDENTIFIER lk IDENTIFIER rk cc ewise_cordinates sc
                  {var_ewise_with_cordinates_st(); parameters = 0;}
/* ¿ôÃÍÀÑÊ¬Ë¡¤Ë¤è¤ëÉ¾²ÁÅÀ¤Î»ØÄê */
  | IDENTIFIER lk IDENTIFIER rk cc IDENTIFIER sc
                  {var_ewise_with_quadrature_st(); parameters = 0;}
/*
  | ewise_definitions co IDENTIFIER lk IDENTIFIER rk  
                        {var_ewise_st(parameters); parameters = 0;}
  | ewise_definitions co IDENTIFIER lk IDENTIFIER rk cc ewise_cordinates
                  {var_ewise_with_cordinates_st(parameters); parameters = 0;}
  | ewise_definitions co IDENTIFIER lk parameter_list rk cc IDENTIFIER  
                  {var_ewise_with_quadrature_st(parameters); parameters = 0;}
*/
ewise_cordinates       /* ewise ÊÑ¿ô¤ÎºÂÉ¸»ØÄê½èÍý */
  : lb ewise_cordinate {push_ewise_cordinate_r();} co ewise_cordinate rb 
                       {push_ewise_cordinate_s();  push_ewise_cordinate_inc();}
  | ewise_cordinates co lb ewise_cordinate     {push_ewise_cordinate_r();}
                        co ewise_cordinate  rb {push_ewise_cordinate_s();
                                                push_ewise_cordinate_inc(); }
ewise_cordinate
  : num di num  { push_ewise_cordinate_dat(2); }
  | num         { push_ewise_cordinate_dat(1); }

/*  scheme¥Ö¥í¥Ã¥¯ÄêµÁ    ¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý¡Ý*/
/*--------------------------------------------------------------------
 *  scheme´Ø·¸¹½Ê¸²òÀÏ¥Ñ¡Á¥µ¤Î¥×¥í¥°¥é¥àµ¬Ìó
 *
 *  ·èÄê        1993/06/07
 *--------------------------------------------------------------------
 */
scheme_definition
  : SCHEME lp scheme_statements rp  

scheme_statements
  : scheme_statement
  | scheme_statements scheme_statement

scheme_statement
  /* --------------------------------------------------------------
   *  let Ê¸     ÊÑ¿ôÌ¾  = ¼° ; 
   *             ÊÑ¿ôÌ¾  = ¼° , at ÅÀ¤Î¥ê¥¹¥È  ;
   *             ÊÑ¿ôÌ¾  = ¼° , in ÎÎ°èÌ¾¥ê¥¹¥È(domain¤Þ¤¿¤Ïregion);
   *             ÊÑ¿ôÌ¾  = ¼° , on ¶­³¦Ì¾¥ê¥¹¥È;
   *             ÊÑ¿ôÌ¾  = ¼° , where ¾ò·ï;
   * --------------------------------------------------------------*/
  : IDENTIFIER   eq  expression   sc  {Let_st(); }
  | IDENTIFIER   eq  expression co AT parameter_list sc 
                              {Let_at_st(parameters); parameters = 0;}
  | IDENTIFIER   eq  expression co IN parameter_list sc 
                              {Let_in_st(parameters); parameters = 0;}
  | IDENTIFIER   eq  expression co ON parameter_list sc 
                              {Let_on_st(parameters); parameters = 0;}
/*  | IDENTIFIER   eq expression WHERE condition sc     */
  /* --------------------------------------------------------------
   *  goto Ê¸     goto ¥é¥Ù¥ëÌ¾ ;
   * --------------------------------------------------------------*/
  | GOTO  IDENTIFIER sc { Goto_st(); }
  /* --------------------------------------------------------------
   *  label Ê¸    ¥é¥Ù¥ëÌ¾:
   * --------------------------------------------------------------*/
  | IDENTIFIER cc       { Label_st(); }

  /* --------------------------------------------------------------
   *  norm Ê¸¥·¥ê¡¼¥º    
   * --------------------------------------------------------------*/
  | L2NORM  lk IDENTIFIER co expression rk sc { L2_norm();  }
  | MAXNORM lk IDENTIFIER co expression rk sc { MAX_norm(); }

  /* --------------------------------------------------------------
   *  Adaptmesh
   * --------------------------------------------------------------*/
  | ADAPTMESH lk expression rk sc { parse_adaptmesh(); }
  | ADAPTMESH STRING lk expression rk sc { parse_adaptmesh_with_option(); }

  /* --------------------------------------------------------------
   *  showvec Ê¸  showvec[ ÊÑ¿ôÌ¾ , ÊÑ¿ôÌ¾];
   *
   *  ÊÑ¿ô¤ÏÆ±¤¸¼ïÎà¤ÎfemÊÑ¿ô¡¢¤Þ¤¿¤ÏewiseÊÑ¿ô¤Ç¤Ê¤±¤ì¤Ð¤Ê¤é¤Ê¤¤¡£
   * --------------------------------------------------------------*/
  | SHOWVEC lk IDENTIFIER co IDENTIFIER rk sc { Showvec_st(0);}
  | SHOWVEC lk IDENTIFIER co IDENTIFIER rk lb setting_list rb sc
       { Showvec_st_with_setting(settings); settings = 0; }

  | SHOWVEC_FILE STRING lk IDENTIFIER co IDENTIFIER rk sc 
       {Showvec_file_st(0);}
  | SHOWVEC_FILE STRING lk IDENTIFIER co IDENTIFIER rk lb setting_list rb sc
       { Showvec_file_st_with_setting(settings); settings = 0; }

  /* --------------------------------------------------------------
   *  contour Ê¸  [ ÊÑ¿ôÌ¾ ];
   *
   *  ÊÑ¿ô¤ÏfemÊÑ¿ô¤Ç¤Ê¤±¤ì¤Ð¤¤¤±¤Ê¤¤¡£
   * --------------------------------------------------------------*/
  | CONTOUR lk IDENTIFIER rk sc { Contour_st(0); }
  | CONTOUR lk IDENTIFIER rk lb setting_list rb sc 
       { Contour_st_with_setting( settings ); settings = 0; }


  /* --------------------------------------------------------------
   *  contour_file Ê¸  [ ÊÑ¿ôÌ¾ ];
   *
   *  ÊÑ¿ô¤ÏfemÊÑ¿ô¤Ç¤Ê¤±¤ì¤Ð¤¤¤±¤Ê¤¤¡£
   * --------------------------------------------------------------*/
  | CONTOUR_FILE STRING lk IDENTIFIER rk sc { Contour_file_st(); }
  | CONTOUR_FILE STRING lk IDENTIFIER rk lb setting_list rb sc
       { Contour_file_st_with_setting( settings ); settings = 0; }
  /* --------------------------------------------------------------
   *  perspect Ê¸  [ ÊÑ¿ôÌ¾ ];
   * 
   *  ÊÑ¿ô¤ÏfemÊÑ¿ô¤Ç¤Ê¤±¤ì¤Ð¤¤¤±¤Ê¤¤¡£
   * --------------------------------------------------------------*/
  | PERSPECT lk IDENTIFIER rk sc { Perspect_st(); }
  | PERSPECT lk IDENTIFIER rk lb setting_list rb sc 
       { Perspect_st_with_setting(settings); settings = 0; }

  /* --------------------------------------------------------------
   *  displacement Ê¸  [ ÊÑ¿ôÌ¾ ](fact=200);
   *
   *  ÊÑ¿ô¤ÏfemÊÑ¿ô¤Ç¤Ê¤±¤ì¤Ð¤¤¤±¤Ê¤¤¡£
   * --------------------------------------------------------------*/
  | DISPLACEMENT lk IDENTIFIER co IDENTIFIER rk sc {Displacement_st();}
  | DISPLACEMENT lk IDENTIFIER co IDENTIFIER rk lb setting_list rb sc 
       { Displacement_st_with_setting( settings ); settings = 0; }

  /* --------------------------------------------------------------
   *  AVScontour Ê¸  [ ÊÑ¿ôÌ¾ ];
   * 
   *  ÊÑ¿ô¤ÏfemÊÑ¿ô¤Ç¤Ê¤±¤ì¤Ð¤¤¤±¤Ê¤¤¡£
   * --------------------------------------------------------------*/
/*  | AVS_CONTOUR lk IDENTIFIER rk sc { AVScontour_st(); } */

  /* --------------------------------------------------------------
   *  writeÊ¸ ¤³¤ì¤Ïfeel¤Î°ú¤­¿ô¤òFORTRAN77¤ËÄ¾ÀÜ½ÐÎÏ¤·¤Þ¤¹
   *          Ê¸»úÎó¤Ï¡¢feel¤Îµ¬³Ê¤Ç "..."¤ÈÆþÎÏ¤·¡¢'¤Ï´Þ¤Þ¤ÌÍÍÃí°Õ¤·¤Æ¤Í
   * --------------------------------------------------------------*/
  | WRITE {Write_parse_init(); } lb write_components rb sc { Write_st(); }
  | FILE_WRITE STRING {File_Write_parse_init(); } lb write_components rb sc 
                          { File_Write_st(); }

  /* --------------------------------------------------------------
   *  readÊ¸  ¤³¤ì¤Ïfeel¤Î°ú¤­¿ô¤òFORTRAN77¤ËÄ¾ÀÜ½ÐÎÏ¤·¤Þ¤¹
   *          Ê¸»úÎó¤Ï¡¢feel¤Îµ¬³Ê¤Ç "..."¤ÈÆþÎÏ¤·¡¢'¤Ï´Þ¤Þ¤ÌÍÍÃí°Õ¤·¤Æ¤Í
   * --------------------------------------------------------------*/
  | READ lb parameter_list rb sc { Read_st(parameters); parameters = 0; }

  /* --------------------------------------------------------------
   *  xplotÊ¸  Í¿¤¨¤é¤ì¤¿ÅÀÎó(º£¤Ïline¤òÁÛÄê)¾å¤Î¥Ç¡¼¥¿¤ò¥¦¥¤¥ó¥É¥¦É½¼¨
   *  xplot[Àþ¤ÎÌ¾¾Î,½ÐÎÏ¤¹¤ëfemÊÑ¿ô,...(x,y,z¤Î¶õ´ÖÊÑ¿ô¤â²Ä) ]
   * --------------------------------------------------------------*/
  | XPLOT lk parameter_list rk sc { Xplot_st(parameters); parameters = 0;}
  | XPLOT lk parameter_list rk lb setting_list rb sc 
       { Xplot_st_with_setting(parameters,settings); parameters = 0;
                               settings   = 0; }
  /* --------------------------------------------------------------
   *  avsoutput statement 
   *  avsoutput[fem parameters];  list up avs output fem variables
   * --------------------------------------------------------------*/
  | AVSOUTPUT lk parameter_list rk sc { AVSoutput_st(parameters);
                                        parameters = 0;}

  /* --------------------------------------------------------------
   *  avsnetwork statement 
   *  avsnetwork[network items];  list up avs modules
   * --------------------------------------------------------------*/
  | AVSNETWORK lk parameter_list rk sc { AVSnetwork_st(parameters);
                                        parameters = 0;}

  /* --------------------------------------------------------------
   *  plot-fileÊ¸  Í¿¤¨¤é¤ì¤¿ÅÀÎó(º£¤Ïline¤òÁÛÄê)¾å¤Î¥Ç¡¼¥¿¤ò¥Õ¥¡¥¤¥ë¤Ë
   *          ½ÐÎÏ¤¹¤ë
   * 
   *  plot '¥Õ¥¡¥¤¥ëÌ¾'[Àþ¤ÎÌ¾¾Î,½ÐÎÏ¤¹¤ëfemÊÑ¿ô,...(x,y,z¤Î¶õ´ÖÊÑ¿ô¤â²Ä) ]
   * --------------------------------------------------------------*/
  | PLOT_FILE STRING lk parameter_list rk sc { plot_st(parameters);  parameters = 0;}
  | TIME_PLOT_FILE STRING lk parameter_list rk sc {time_plot_st(parameters);
						   parameters = 0;
					       }

  /* --------------------------------------------------------------
   *  ifÊ¸ ´Ø·¸
   * --------------------------------------------------------------*/
  | IF  condition  THEN               {p_if_then(if_left_ptr,condition_type );}
  | IF  condition  GOTO IDENTIFIER sc {p_if_goto(if_left_ptr,condition_type );}
  | ELSE           { p_else();  }
  | ENDIF sc       { p_endif(); }
  /*===============================================================
    solve ¥Ö¥í¥Ã¥¯¤ÎÊ¸Ë¡ÄêµÁ
    ===============================================================*/
  | solve_block

write_components
  : expression   { write_st_expression(); }
  | STRING       { write_st_string(); }
  | write_components co expression { write_st_expression(); }
  | write_components co STRING     { write_st_string(); }






/*-------------------------
  solve ¥Ö¥í¥Ã¥¯
  -------------------------*/
/*  ·×»»ÎÎ°è:Ì¤ÃÎÊÑ¿ô(´ûÃÎÊÑ¿ô):¿ôÃÍÀÑÊ¬Ë¡:·Á¾õÊÑ´¹´Ø¿ô
 *
 *
 *  solveÊ¸  Àþ·Á¤ÎÊÐÈùÊ¬ÊýÄø¼°¡¢¼å·Á¼°¡¢ÈÆ´Ø¿ôÄäÎ±ÃÍÌäÂê¤òµ­½Ò¤¹¤ë
 * 
 *  solve [Ì¤ÃÎfemÊÑ¿ô]{
 *  
 *  domain: ÎÎ°èÌ¾;   ¿·¤¿¤ËÀë¸À¤¹¤ëËø¤ÎÌäÂê¤¬°ì¤Ä¤ÎSolveElement¤Ë¤Ê¤ë
 *                    ¾ÊÎ¬²ÄÇ½(Í£°ì¤ÎdomainÊ¸¤òºÎÍÑ)
 *                    ------------------------------
 *                    ÎÎ°è¤ò»ØÄê¤¹¤ëºÝ¤Ë¤ÏÊýÄø¼°·²¤ÎÁ°¤ËÉ¬¤º¼Â¹Ô
 *    
 *  subdomain: ÎÎ°èÌ¾ 
 *    
 *  linear method: Ï¢Î©°ì¼¡ÊýÄø¼°²òË¡;  ¤³¤ì¤ÏsolveÊ¸Ãæ°ì¤Ä¤À¤±»ÈÍÑ²ÄÇ½
 *  quadrature method: ¿ôÃÍÀÑÊ¬Ë¡;      ¤³¤ì¤Ï³ÆSolveElement¤ËÂÐ¤·¤Æ»ØÄê¤¹¤ë
 *  boundary quadrature: ¥¬¥¦¥¹ÀÑÊ¬¼¡¿ô;  ¶­³¦ÀÑÊ¬¤Î¥¬¥¦¥¹¿ôÃÍÀÑÊ¬Ë¡¼¡¿ô¤Î»ØÄê
 *  isoparametric;     ¥¢¥¤¥½¥Ñ¥é¥á¥È¥ê¥Ã¥¯»ØÄê
 *                                    
 *  symmetry;          ÂÐ¾Î¹ÔÎó¤Î»ØÄê
 *  nonlinear;         ÈóÀþ·ÁÊýÄø¼°¤Î»ØÄê
 * 
 *  initial u = FEMÊÑ¿ô¼°;  ÈóÀþ·ÁÊýÄø¼°¤Î½é´üÃÍÀßÄê
 *
 *  eps = ¿ôÃÍ              ¼ýÂ«È½Äê¾ò·ï
 *
 *  newton-factor ´ËÏÂ·¸¿ô; Newton-RaphsonÈ¿Éü»þ¤Î´ËÏÂ·×¿ô¤ò»ØÄê¤¹¤ë
 *
 *  shape ·Á¾õ´Ø¿ôÌ¾   ·Á¾õ´Ø¿ô¤ÎÍÛÅª¤Ê»ØÄê
 *                                    
 *
 *  eq: ÊÐÈùÊ¬ÊýÄø¼° {,[ÀÑÊ¬ÊýË¡]ÊÐÈùÊ¬ÊýÄø¼°}{,<¶­³¦ÀÑÊ¬¹à>},{,@»î¸³´Ø¿ôÌ¾} ;
 *        .....
 *  weq: ÊÐÈùÊ¬ÊýÄø¼°¤Î¼å·Á¼°¡¢¶­³¦ÀÑÊ¬¹à¤Ï<...>¤Ëµ­½Ò , »î¸³´Ø¿ôÌ¾ ;
 *       ¼å·Á¼°Ãæ¡¢»î¸³´Ø¿ô¤Ï$¤Çµ­½Ò¤¹¤ë¡£
 *  
 *  eigen: ¸ÇÍ­ÃÍÌäÂê    eigen: A,B;    A[u] = ¦ËB[u]¤òµá¤á¤ë
 *
 *
 *  func: ÈÆ´Ø¿ôÌ¾¡¢¶­³¦ÀÑÊ¬¹à¤Ï <....>¤Ëµ­½Ò;
 *
 *  weq: expr1,expr2,<expr3>;
 *  ¤Ï¡¢expr1+expr2+expr3=0¤È¤¤¤¦ÊýÄø¼°¤ËÁêÅö¤¹¤ë¡£ 
 *
 *--------------------------------------------------------------------
 *  ¶­³¦¾ò·ï¤Ï¡¢°ì¤Ä¤ÎsolveÊ¸¤ËÂÐ¤·¤Æ1set»ØÄê¤¹¤ë¡£
 *  
 *  
 *--------------------------------------------------------------------
 * 
 *  ÈóÀþ·ÁÊýÄø¼°¤Î¾ì¹ç¤Ï¡¢solve ¢ª nonlinear ¤È¤¹¤ë¡£
 * 
 *--------------------------------------------------------------------
 */
solve_block
  :  SOLVE { solve_parse_init() ; } solve_vars lp solve_statements rp 
           { Make_SolveElement(); p_solve_complete(); }

solve_vars
  :  lk parameter_list rk {p_solve_unknowns(parameters); parameters = 0; }

solve_statements
  : solve_statement
  | solve_statements solve_statement

solve_statement
  : DOMAIN cc IDENTIFIER sc            {p_solve_domain(); }
         /* dbg: CAUTION: ÀÑÊ¬Ë¡»ØÄê»þ¤ÎÆâÁÞ»ØÄêË¡ÉÕµ­½Ò¤ò´°À®¤¹¤ë¤³¤È */
  | SUBDOMAIN cc IDENTIFIER sc         {p_solve_subdomain(); }  /* oimo Ãí°Õ
								1995/12/8
								Î®ÍÑ¤·¤¿ */
  | QUADRATURE METHOD cc IDENTIFIER sc {p_solve_quadrature_method(); } 
  | BOUNDARY QUADRATURE cc num sc        {p_solve_boundary_quadrature(); }
  | LINEAR METHOD cc IDENTIFIER sc     {p_solve_linear_method(); }
  | ISOPARAMETRIC sc                   {p_solve_isoparametric(); }
  | SHAPE IDENTIFIER sc                {p_solve_shape();         }
  | NONLINEAR sc                       {p_solve_nonlinear();     }
  | SYMMETRY sc                        {p_solve_symmetry();      }
  | INITIAL_VALUE IDENTIFIER eq expression sc
                                       {p_solve_initial();       }
  | EPS    num sc                      {p_solve_eps();           }  
  | NEWTON_FACTOR expression sc        {p_solve_newton_factor(); }
  | NEWTON_TIMES  expression sc        {p_solve_newton_times(); }
  | equations 
  | b_conditions    


equations          /* ÊýÄø¼°µ­½Ò */
  : equation              
  | equations equation    


b_conditions       /* ¶­³¦¾ò·ï */
  : b_condition
  | b_conditions b_condition


/*------------------------*/
/* ÊÐÈùÊ¬ÊýÄø¼°¤Î»ØÄêÊýË¡ */
/* ¼å·Á¼°¤ò´Þ¤à           */
/*------------------------*/
equation                       
  : EQ   equation_terms sc {  p_EQ();  }
  | WEQ  equation_terms sc {  p_WEQ(0); }
  | EIGEN equation_terms sc { p_EIGEN(); }
  | FUNC equation_terms sc {  p_FUNC();}


equation_terms
  : equation_term                   
  | equation_terms co equation_term 

equation_term
  : ATMARK IDENTIFIER                  /* »î¸³(½Å¤ß)´Ø¿ô¤ÎÄêµÁ */
                      {p_solve_test_function(); }
  | expression                         /* ÉáÄÌ¤Î»ØÄê           */
                      {p_solve_expression();    }
  | lk IDENTIFIER rk expression        /* ¿ôÃÍÀÑÊ¬Ë¡»ØÄêÉÕ¤­ */
                      {p_solve_expression_with_quad_method(); }
  | lt expression gt                   /* ¶­³¦ÀÑÊ¬¹à */
                      {p_solve_boundary_term(); }
  | lk IDENTIFIER rk lt expression gt  /* ¿ôÃÍÀÑÊ¬Ë¡»ØÄêÉÕ¤­¶­³¦ÀÑÊ¬¹à */
                      {p_solve_boundary_term_with_quad_method(); }
/*----------*/
/* ¶­³¦¾ò·ï */
/*----------*/
/*--------------------------------------------------------------------
 *  ¶­³¦¥ê¥¹¥È¤Ï,
 *
 *  on a,b,[1];  ¤Ê¤É
 *
 *  dbc: ¥Ç¥£¥ê¥¯¥ì¶­³¦¾ò·ï(´ðËÜ¶­³¦¾ò·ï)¤òµ­½Ò
 *       Ì¤ÃÎÊÑ¿ôÌ¾ = ¼°  , on ¶­³¦¥ê¥¹¥È;
 *  nbc: ¥Î¥¤¥Þ¥ó¶­³¦¾ò·ï(¼«Á³¶­³¦¾ò·ï)¤òµ­½Ò
 *       ¶­³¦ÀÑÊ¬¹à¤Ë¸½¤ì¤ë¼° = ¼° , ¼° = ¼° , on ¶­³¦¥ê¥¹¥È ;
 *       ÈÆ´Ø¿ô¡¢¼å·Á¼°¤Ç¶­³¦ÀÑÊ¬¹à¤¬ÍÛ¤Ëµ­½Ò¤µ¤ì¤Æ¤¤¤ë¾ì¹ç¤Ï¡¢
 *       µ­½Ò¤ÎÀ©¸Â¤¬´Ë¤á¤é¤ì¤ë(´Ë¤á¤¿¤¤)
 * 
 *  ¿ôÃÍ¥Ç¡¼¥¿¤È¤·¤ÆÍ¿¤¨¤é¤ì¤ë¶­³¦¾ò·ï
 * 
 *  A)¥Ç¥£¥ê¥¯¥ì¶­³¦¾ò·ï
 *  dbc:  Ì¤ÃÎÊÑ¿ôÌ¾  =  [¥Ç¡¼¥¿¥»¥Ã¥ÈÈÖ¹æ];  ¡ÚÃí°Õ¡Û¸½ºßÌ¤ÂÐ±þ
 * 

 ¤³¤ì¤Ï¥Ð¥Ã¥¯¥¢¥Ã¥×
  : NBC IDENTIFIER    { p_ncond_left_var();      } eq 
        expression    { p_ncond_right_expr();     } co
        ON edge_list  { p_ncond_edge(parameters);
                        parameters = 0;           }
        sc           

 *--------------------------------------------------------------------
 */
b_condition
  : NBC {p_ncond_init(); } 
        neumann_args
        co ON edge_list  { p_ncond_edge(parameters);
                           parameters = 0;           }
        sc           

  /* Dirichlet Boundary CONDITION */
  | DBC IDENTIFIER   { p_dcond_var();             } eq 
        expression   { p_dcond_expr();            } co 
        ON edge_list { p_dcond_edge(parameters);          
                       parameters = 0;            } 
        sc           

neumann_args 
  : IDENTIFIER eq expression                     { p_ncond_arg(); }
  | neumann_args co IDENTIFIER eq expression     { p_ncond_arg(); }

/* expression2  */                                      /* LEFT SIDE OF '=' */
/*  : expression  */

expression                                        /* GENERALLY RIGHT SIDE */
  : num                          
{
    expressions++;
    tmp_pop = (char *)pop();
    exp_atom_push(tmp_pop);
 }
  | IDENTIFIER                             /* ¥·¥ó¥Ü¥ë */
{      expressions++;
       push_identifier_and_push();         /* ¿ô¼°Ãæ¤Î¥·¥ó¥Ü¥ë¤òpop¤·¤Æ³ÊÇ¼¸å
					      ¤Þ¤¿push¤¹¤ë´Ø¿ô(YaccExp..c)   */
       tmp_pop = (char *)pop();
       exp_atom_push(tmp_pop);
}
/*----------------------------*/
/*  Êý¿ËÊÑ¹¹(¶­³¦ÀÑÊ¬¹à¡¢¿ôÃÍÀÑÊ¬¤Î»ØÄêÊýË¡)     */
/*----------------------------*/
/*  | lk IDENTIFIER rk lb expression rb  */    /* ¿ôÃÍÀÑÊ¬Ë¡¤¬»ØÄê¤µ¤ì¤¿¿ô¼° ¢« ¤³¤³¤Ï¤Á¤ç¤Ã¤ÈÊÑ¹¹  */  

  | IDENTIFIER  lb { push_function_and_push(); } expression rb  
{      expressions++;                      /* ´Ø¿ô */
       tmp_pop = (char *)pop();
       exp_func_push(tmp_pop);               /* ¿ô¼°Ãæ¤Ë½Ð¸½¤¹¤ë´Ø¿ôÌ¾¤òpop  */
}                                          /* ¤·¤Æ³ÊÇ¼¸å¤Þ¤¿push¤¹¤ë       */
  | IDENTIFIER lk expression rk
{                                          /* ÇÛÎó 
					      ¤³¤ì¤Ï¡¢¹´Â«¾ò·ïÉÕ¤­elementÀë¸À
					      Ê¸¤Ç¸½¤ì¤ë¡£                   */
       expressions++;
       push_identifier_and_push();         /* ¿ô¼°Ãæ¤Î¥·¥ó¥Ü¥ë¤òpop¤·¤Æ³ÊÇ¼¸å
					      ¤Þ¤¿push¤¹¤ë´Ø¿ô(YaccExp..c)   */
       tmp_pop = (char *)pop();
       exp_array_push(tmp_pop);
}
  | mi expression  /* Ã±¹à±é»»»Ò */
{
    exp_minus_push();
}
  | lb expression rb        /* ³ç¸Ì¤Ç¤¯¤¯¤é¤ì¤¿¿ô¼°(¤Ê¤Ë¤â½èÍý¤·¤Ê¤¤) */    

/*----------------------------*/
/*  Êý¿ËÊÑ¹¹(¶­³¦ÀÑÊ¬¹à¡¢¿ôÃÍÀÑÊ¬¤Î»ØÄêÊýË¡)     */
/*----------------------------*/
/*  | lt expression gt  */      /* ¶­³¦ÀÑÊ¬¤òÉ½¤¹¿ô¼° < ... > */
/*----------------------------*/
/*  Êý¿ËÊÑ¹¹(¶­³¦ÀÑÊ¬¹à¡¢¿ôÃÍÀÑÊ¬¤Î»ØÄêÊýË¡)     */
/*----------------------------*/
/*  |  lk IDENTIFIER rk lt expression gt */    /* ¿ôÃÍÀÑÊ¬Ë¡¤¬»ØÄê¤µ¤ì¤¿¿ô¼° */
                                           /* ¶­³¦ÀÑÊ¬¹à                 */
  | expression  pl expression 
{
    exp_pl_push();
}
  | expression mi expression
{
    exp_mi_push();
}
  | expression mu expression
{
    exp_mu_push();
}
  | expression di expression
{
    exp_di_push();
}

/* CONDITION FORMULA */

condition
  : lb expression {if_left_ptr=get_expr_structure(); } equal expression rb  {condition_type = 1; }
  | lb expression {if_left_ptr=get_expr_structure(); } le    expression rb  {condition_type = 2; }
  | lb expression {if_left_ptr=get_expr_structure(); } lt    expression rb  {condition_type = 3; }
  | lb expression {if_left_ptr=get_expr_structure(); } ge    expression rb  {condition_type = 4; }
  | lb expression {if_left_ptr=get_expr_structure(); } gt    expression rb  {condition_type = 5; }
  | lb expression {if_left_ptr=get_expr_structure(); } ne    expression rb  {condition_type = 6; }
/*
  variable
  : IDENTIFIER
  | num
  */
/*-----PARAMETERS-----*/

setting_list
  :  IDENTIFIER eq num { settings++; }
  |  IDENTIFIER eq IDENTIFIER { settings++; }
  |  IDENTIFIER eq STRING { settings++; }
  |  IDENTIFIER eq ON { push("on"); settings++;}
/*  |  MESH       eq ON {push("mesh"); push("on"); settings++;} */
  |  MESH       eq IDENTIFIER {char *tmpc; tmpc=(char *)pop();
                               push("mesh"); push(tmpc); settings++;}
  |  SUBDOMAIN  eq IDENTIFIER {char *tmpc; tmpc=(char *)pop();
                               push("subdomain"); push(tmpc); settings++;}
  |  setting_list co IDENTIFIER eq IDENTIFIER {settings++;}
  |  setting_list co IDENTIFIER eq ON { push("on"); settings++;}
  |  setting_list co IDENTIFIER eq num {settings++;}
  |  setting_list co IDENTIFIER eq STRING { settings++; }
  |  setting_list co SUBDOMAIN {push("subdomain");} eq IDENTIFIER {settings++;}
  |  setting_list co MESH {push("mesh"); } eq IDENTIFIER {settings++;}
/* |  setting_list co MESH {push("mesh"); } eq ON {push("on"); settings++;}  */

parameter_list
  :  IDENTIFIER   { parameters++;}
  |  parameter_list co IDENTIFIER {parameters++;}

num_parameter_list
  :  num          { parameters++;}
  |  num_parameter_list co num {parameters++;}

inner_point_list
  :  IDENTIFIER   { inner_parameters++;}
  |  inner_point_list co IDENTIFIER {inner_parameters++;}

inner_edge_lists
  :  lk inner_point_list rk   
     { pop_push_inner_points(inner_parameters); parameters++; 
       inner_parameters = 0;                                  }
  |  inner_edge_lists co lk inner_point_list rk 
     { pop_push_inner_points(inner_parameters); parameters++; 
       inner_parameters = 0;                                  }

edge_list
  :  IDENTIFIER   {parameters++;}
  |  edge_list co IDENTIFIER  {parameters++;}

edge_point_lists
  :  parameter_list
  |  parameter_list co inner_edge_lists 
