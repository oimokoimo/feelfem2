/*
 *  Numerical Simulation Language for Finite Element Method
 *
 *  FILE fem.y   Date          1991/12/24
 *               LastModified  1992/01/24
 *               Version       0.2
 *
 *  For feel p2  version       1993/05/25
 */

/* declarations */
%{
#include <stdio.h>

    extern int parameters;   /* to count the number of  parameter */
    extern int expressions;  /* to count the items in expression  */
    extern int settings;
    extern int inner_parameters; /* to count the number of inner points */
    extern int condition_type;   /* condition type */

    char *tmp_pop;               /* debug for DEC/Alpha AXP/ OSF/1(941024) */
    extern char *get_expr_structure();
    extern char *if_left_ptr;
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
%token  FEM              /* "fem"         */
%token  EWISE            /* "ewise"       */
%token  INT              /* "int"         */
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
%token  DISPLACEMENT     /* "displacement" */
%token  MAXNORM          /* "MAXnorm"     */
%token  L2NORM           /* "L2NORM"      */
%token  ADAPTMESH        /* "adaptmesh"   */

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
  |   sections  { /* debug_start(); (注意！feel_exec_mainの中に移しました。)*/
	          viewmesh();  }

sections
  : section
  | sections section

section
  : mesh_definition                 /* 形状定義 */

/*  形状定義    −−−−−−−−−−−*/
/*--------------------------------------------------------------------
 *  mesh生成関係構文解析パ〜サのプログラム規約
 *
 *  諸定数値は  ../feel_def/feel_def.h  に定義する
 *  構造体等は  各関数自体で宣言する
 *  関数名は    yaccの直呼びだし関数は 関数名の最後に _st を付ける
 *  決定        1993/06/03              
 *--------------------------------------------------------------------
 *  dimension文 次元の設定(通常は２)
 *
 *    dimension 次元;
 *--------------------------------------------------------------------
 *  nodes文     各領域の節点数を指定する
 *
 *    nodes 領域名(節点数) {,領域名(節点数),...};
 *--------------------------------------------------------------------
 *  showmesh文  生成したメッシュを表示する
 *
 *    showmesh;
 *--------------------------------------------------------------------
 *  point文     点の指定する
 *
 *    point 点の名前(x座標,y座標){,点の名前(x座標,y座標),...};
 *--------------------------------------------------------------------
 *  refine statement
 *
 *    refine a(factor);
 *--------------------------------------------------------------------
 *  line文      線を指定する
 *
 *    line 線の名前(lineを構成する点のリスト);
 *--------------------------------------------------------------------
 *  domain文    計算領域の指定
 *
 *    domain 名前(region名のリスト);
 *--------------------------------------------------------------------
 *  region文    領域形状、基本要素形状の指定
 *
 *    region 名前[tri/rect](点のリスト,...{,[穴領域の点のリスト],...})
 *--------------------------------------------------------------------
 *  subdomain文 部分領域集合の定義
 *    
 *    subdomain 名前(領域のリスト)
 *--------------------------------------------------------------------
 *  number文    領域,境界番号の定義 
 *
 *  region number 名称(番号);
 *  line number   名称(番号);
 *
 *--------------------------------------------------------------------
 */
mesh_definition 
  :  MESH lp mesh_statements rp     

mesh_statements
  :  mesh_statement
  |  mesh_statements mesh_statement

mesh_statement
  :  /* empty */                      /* 空文読み飛ばし       */
  |  NODES   nodes_definitions sc     /* 各領域の節点数の定義 */
  |  POINT   point_definitions sc
  |  REFINE  refine_definitions sc
  |  EDGE    line_definitions sc
  |  DOMAIN  IDENTIFIER lb parameter_list rb sc   /* domain文 */
               { domain_st(parameters); parameters = 0;}
  |  SUBDOMAIN  IDENTIFIER lb parameter_list rb sc   /* domain文 */
               { subdomain_st(parameters); parameters = 0;}
  |  REGION  IDENTIFIER lk IDENTIFIER rk lb edge_point_lists rb sc
               { region_with_meshmethod_st(parameters); parameters = 0;}

nodes_definitions   /* nodes 文の本体 */
  : IDENTIFIER lb num rb                      {nodes_st(); }
  | nodes_definitions co IDENTIFIER lb num rb {nodes_st(); }

point_definitions   /* point 文の本体 */
  : IDENTIFIER lb num co num rb { point_2d_st();}
  | point_definitions co IDENTIFIER lb num co num rb { point_2d_st();}

refine_definitions  /* refine statement */
  : IDENTIFIER lb num rb { refine_st(); }
  | refine_definitions co IDENTIFIER lb num rb { refine_st();}

line_definitions
  : IDENTIFIER lb parameter_list rb { line_st(parameters); parameters = 0;}
  | line_definitions co IDENTIFIER lb parameter_list rb 
               { line_st(parameters); parameters = 0; }
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

edge_list
  :  IDENTIFIER   {parameters++;}
  |  edge_list co IDENTIFIER  {parameters++;}

edge_point_lists 
  :  parameter_list
  |  parameter_list co inner_edge_lists
