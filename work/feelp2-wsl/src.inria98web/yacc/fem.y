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
    char *pop(void);            /* modernize 2026/01/21 */
    void push(char *s);         /* modernize 2026/01/21 */
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
  |   sections  { /* debug_start(); (注意！feel_exec_mainの中に移しました。)*/
                  feel_exec_main();
	          debug_terminate();
	          feel_terminate();  }

sections
  : section
  | sections section

section
  : mesh_definition                 /* 形状定義 */
  | element_definition              /* 要素定義 */
  | var_definition                  /* 変数定義 */
  | quadrature_definition           /* 積分法定義 */ 
  | scheme_definition               /* スキーム定義 */


/***********************************************/
/*  要素定義   element文 −−−−−−−−−−−*/
/***********************************************/
 /*  element 要素名 [図形要素] {
 *        double  変数名 = 評価式 ;
 *        const   変数名 = 評価式 ;
 *        (座標,座標,...)     : 基底関数 ;
 *        (座標,座標,...)[dn] : 基底関数 ;  エルミートタイプ
 *               .....
 *}
 *
 *  element 要素名 (拘束fem変数名[要素タイプ])[図形要素] {
 *        (座標,座標,...)     : 基底関数 ;
 *        (座標,座標,...)[dn] : 基底関数 ;  エルミートタイプ
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
/*  | DN { push("dn");   DNのtokenやんぴ */ /* DNはプッシュされない為 */ 

cordinate
  : num          { p_node_cordinate(1); } 
  | num di num   { p_node_cordinate(2); }

fem_var_parameters
  : fem_var_parameter
  | fem_var_parameters co fem_var_parameter

fem_var_parameter
  : IDENTIFIER lk IDENTIFIER rk { p_element_fem_restrains(); }

/*
 *    数値積分法 quadrature文
 * 
 *
 *    quadrature 数値積分名称[領域名称] {
 *
 *    quadrature 数値積分名称(引き数となる変数の宣言)[領域名称] {
 *                                    ↓
 *                               変数名[要素名]{,.....}{{,変数名}{,,,,}}
 *                        
 *    const 変数名: 式 ;    積分点、重みの指定に用いる
 *                        
 *   (積分点,積分点): 式;   重み
 *
 *   変数名(積分点,積分点): 評価式;   引き数に指定したfem,ewise,double変数の補間法
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

quadrature_component    /* 数値積分指定の各項目 */
  : lb quadrature_coordinate rb cc                 /* 一次元積分点座標指定*/
    { p_quadrature_coordinate_1dim(); } expression sc 
    { p_quadrature_component(); }
  | lb quadrature_coordinate co quadrature_coordinate rb cc   /* ２次元 */
    { p_quadrature_coordinate_2dim(); } expression sc    
    { p_quadrature_component(); } 
  | lb quadrature_coordinate co quadrature_coordinate co      /* ３次元 */
       quadrature_coordinate rb cc 
    { p_quadrature_coordinate_3dim(); } expression sc 
    { p_quadrature_component(); } 
  | IDENTIFIER  lb {p_quadrature_identifier(); }         /* 変数内挿法 */
    quadrature_interpolate
  | CONST IDENTIFIER eq expression sc       {p_quadrature_const(); } /* 定数 */
  | DOUBLE quadrature_double_identifiers sc  /* 実数変数宣言   */
  | IDENTIFIER eq expression sc             {p_quadrature_let_st();} /* 代入 */

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
  |  DIMENSION num sc { dimension_st(); }
  |  NODES   nodes_definitions sc     /* 各領域の節点数の定義 */
  |  SHOWMESH sc                      /* 生成メッシュの表示   */
               { showmesh_st(); }
  |  POINT   point_definitions sc
  |  REFINE  refine_definitions sc
  |  EDGE    line_definitions sc
  |  DOMAIN  IDENTIFIER lb parameter_list rb sc   /* domain文 */
               { domain_st(parameters); parameters = 0;}
  |  SUBDOMAIN  IDENTIFIER lb parameter_list rb sc   /* domain文 */
               { subdomain_st(parameters); parameters = 0;}
  |  REGION  IDENTIFIER lk IDENTIFIER rk lb edge_point_lists rb sc
               { region_with_meshmethod_st(parameters); parameters = 0;}
/*  |  REGION  IDENTIFIER lb edge_point_lists rb sc   regionにメッシュ生成
                                                      方法指定は必須(7/16変更)
               { region_st(parameters); parameters = 0;} */
/*
  |  CURVE   IDENTIFIER lb parameter_list rb lk IDENTIFIER rk sc
               { curve_st();}
  |  RECTANGLE IDENTIFIER lb IDENTIFIER co IDENTIFIER co IDENTIFIER co IDENTIFIER rb sc
               { rectangle_st();}
*/

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

/*  変数定義    −−−−−−−−−−−*/
/*--------------------------------------------------------------------
 *  変数定義関係構文解析パ〜サのプログラム規約
 *
 *  決定        1993/06/03              
 *--------------------------------------------------------------------
 *  double文    倍精度型変数の宣言
 *              倍精度型の変数は、メインルーチン上で定義される
 *              また、初期値を指定することもできる
 *              初期値は、データ入力後、メインルーチン上で代入する
 *  double  変数名 {{= 初期値 }, .... };
 *--------------------------------------------------------------------
 *  int文       整数型変数の宣言
 *       
 *  int  変数名 {{= 初期値 }, .... };
 *--------------------------------------------------------------------
 *  const文     定数型変数の宣言
 *              定数型変数の宣言は暗黙の型宣言を守らなければいけない
 *  
 *  const 変数名 = 定数値 {, 変数名 = 定数値, ... };
 *--------------------------------------------------------------------
 *  fem文       fem変数の宣言 fem変数は、基底関数と共に指定する
 *              fem変数は基本要素形状に対して一つの基底関数のみ指定できる
 *  
 *  fem 変数名[基底関数名]{[domain名]};
 *  
 *  
 *  fem 変数名[基底関数名(拘束変数名)]{[domain名]};
 *      
 *      
 *  一つのfem変数に対して基本要素形状またはdomain毎に基底関数を指定する場合は
 *  この宣言を繰り返す。    
 *--------------------------------------------------------------------
 *  ewise文     ewise変数(要素指向変数)の宣言
 *              変数名と共に各要素での値を求める座標も指定する。
 *              省略時はdefaultの位置で計算する
 *  
 *              ewise変数は、domainに対して一つ定まる。
 *              複数のdomainにまたがる場合、
 *  
 *  ewise 変数名[domain名];
 *  ewise 変数名[domain名]:(x座標,y座標){,(x座標,y座標),...};
 *  ewise 変数名[domain名]:数値積分名;
 *  
 *  一つのewise変数に対して複数のこの宣言を実行してもよい【今は駄目】
 *  ただし、もちろん重複があってはいけない
 *--------------------------------------------------------------------
 *  material文  material変数(要素のMATNOによって要素毎に決まる物理量)
 *              を表す変数の宣言
 *  
 *  matreial 変数名[MATNO=1の時の値,MATNO=2の時の値,...];
 *  
 *           実際のMATNOがここで指定した値より大きな場合は不都合が生じる
 *--------------------------------------------------------------------
 *  function文  ユーザ定義のFORTRAN関数名を指定する
 *
 *              この文の目的は、関数宣言有無チェックの際のチェック回避
 *              および、Makefileへの登録にあります。
 *--------------------------------------------------------------------
 */
var_definition
  :  VAR lp var_statements rp

var_statements
  : var_statement
  | var_statements var_statement

var_statement
  : INT       int_identifiers      sc   /* 整数変数の宣言 */
  | AVSINT    avsint_identifiers   sc   /* avsint declaration */
  | EWISE     ewise_definitions         /* 要素指向変数の宣言 */
  | CONST     const_identifiers    sc   /* 定数変数の宣言 */
  | FEM       fem_definitions      sc   /* fem 変数の宣言 */
  | MATERIAL  material_definitions sc   /* 物質変数の宣言 */
  | DOUBLE    double_identifiers   sc   /* 倍精度変数の宣言 */
  | AVSDOUBLE avsdouble_identifiers   sc   /* avsdouble declaration */
  | FUNCTION  userfunc_identifiers sc   /* ユーザ指定関数の宣言 */

int_identifiers         /* 整数型変数の宣言 */
  : IDENTIFIER          { var_int_st(0); }
  | IDENTIFIER eq num   { var_int_with_value_st(0); }
  | int_identifiers co IDENTIFIER { var_int_st(0);}
  | int_identifiers co IDENTIFIER eq num { var_int_with_value_st(0); }

avsint_identifiers         /* 整数型変数の宣言(AVS) */
  : IDENTIFIER          { var_int_st(1); }
  | IDENTIFIER eq num   { var_int_with_value_st(1); }
  | avsint_identifiers co IDENTIFIER { var_int_st(1);}
  | avsint_identifiers co IDENTIFIER eq num { var_int_with_value_st(1); }

double_identifiers      /* 倍精度変数の宣言 */
  : IDENTIFIER          { var_double_st(0); }
  | IDENTIFIER eq num   { var_double_with_value_st(0); }
  | double_identifiers co IDENTIFIER { var_double_st(0);}
  | double_identifiers co IDENTIFIER eq num { var_double_with_value_st(0); }

avsdouble_identifiers      /* 倍精度変数の宣言(AVS) */
  : IDENTIFIER          { var_double_st(1); }
  | IDENTIFIER eq num   { var_double_with_value_st(1); }
  | avsdouble_identifiers co IDENTIFIER { var_double_st(1);}
  | avsdouble_identifiers co IDENTIFIER eq num { var_double_with_value_st(1); }

userfunc_identifiers
  : IDENTIFIER                         {var_userfunc_st(); }
  | userfunc_identifiers co IDENTIFIER {var_userfunc_st(); }

const_identifiers      /* 定数変数の宣言 */
  : IDENTIFIER eq expression   { var_const_with_value_st(); }
  | const_identifiers co IDENTIFIER eq expression {var_const_with_value_st(); }

material_definitions
  : IDENTIFIER lk num_parameter_list rk {var_material_st(parameters);
				     parameters = 0;               }

fem_definitions        /* fem 変数の宣言 */
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

ewise_definitions      /* ewise 変数の宣言 +*/
/* デフォルト評価点位置のみでのewise変数宣言 */
  : IDENTIFIER lk IDENTIFIER rk sc {var_ewise_st(); parameters = 0;}
/* 陽な評価点の記述 */
  | IDENTIFIER lk IDENTIFIER rk cc ewise_cordinates sc
                  {var_ewise_with_cordinates_st(); parameters = 0;}
/* 数値積分法による評価点の指定 */
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
ewise_cordinates       /* ewise 変数の座標指定処理 */
  : lb ewise_cordinate {push_ewise_cordinate_r();} co ewise_cordinate rb 
                       {push_ewise_cordinate_s();  push_ewise_cordinate_inc();}
  | ewise_cordinates co lb ewise_cordinate     {push_ewise_cordinate_r();}
                        co ewise_cordinate  rb {push_ewise_cordinate_s();
                                                push_ewise_cordinate_inc(); }
ewise_cordinate
  : num di num  { push_ewise_cordinate_dat(2); }
  | num         { push_ewise_cordinate_dat(1); }

/*  schemeブロック定義    −−−−−−−−−−−*/
/*--------------------------------------------------------------------
 *  scheme関係構文解析パ〜サのプログラム規約
 *
 *  決定        1993/06/07
 *--------------------------------------------------------------------
 */
scheme_definition
  : SCHEME lp scheme_statements rp  

scheme_statements
  : scheme_statement
  | scheme_statements scheme_statement

scheme_statement
  /* --------------------------------------------------------------
   *  let 文     変数名  = 式 ; 
   *             変数名  = 式 , at 点のリスト  ;
   *             変数名  = 式 , in 領域名リスト(domainまたはregion);
   *             変数名  = 式 , on 境界名リスト;
   *             変数名  = 式 , where 条件;
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
   *  goto 文     goto ラベル名 ;
   * --------------------------------------------------------------*/
  | GOTO  IDENTIFIER sc { Goto_st(); }
  /* --------------------------------------------------------------
   *  label 文    ラベル名:
   * --------------------------------------------------------------*/
  | IDENTIFIER cc       { Label_st(); }

  /* --------------------------------------------------------------
   *  norm 文シリーズ    
   * --------------------------------------------------------------*/
  | L2NORM  lk IDENTIFIER co expression rk sc { L2_norm();  }
  | MAXNORM lk IDENTIFIER co expression rk sc { MAX_norm(); }

  /* --------------------------------------------------------------
   *  Adaptmesh
   * --------------------------------------------------------------*/
  | ADAPTMESH lk expression rk sc { parse_adaptmesh(); }
  | ADAPTMESH STRING lk expression rk sc { parse_adaptmesh_with_option(); }

  /* --------------------------------------------------------------
   *  showvec 文  showvec[ 変数名 , 変数名];
   *
   *  変数は同じ種類のfem変数、またはewise変数でなければならない。
   * --------------------------------------------------------------*/
  | SHOWVEC lk IDENTIFIER co IDENTIFIER rk sc { Showvec_st(0);}
  | SHOWVEC lk IDENTIFIER co IDENTIFIER rk lb setting_list rb sc
       { Showvec_st_with_setting(settings); settings = 0; }

  | SHOWVEC_FILE STRING lk IDENTIFIER co IDENTIFIER rk sc 
       {Showvec_file_st(0);}
  | SHOWVEC_FILE STRING lk IDENTIFIER co IDENTIFIER rk lb setting_list rb sc
       { Showvec_file_st_with_setting(settings); settings = 0; }

  /* --------------------------------------------------------------
   *  contour 文  [ 変数名 ];
   *
   *  変数はfem変数でなければいけない。
   * --------------------------------------------------------------*/
  | CONTOUR lk IDENTIFIER rk sc { Contour_st(0); }
  | CONTOUR lk IDENTIFIER rk lb setting_list rb sc 
       { Contour_st_with_setting( settings ); settings = 0; }


  /* --------------------------------------------------------------
   *  contour_file 文  [ 変数名 ];
   *
   *  変数はfem変数でなければいけない。
   * --------------------------------------------------------------*/
  | CONTOUR_FILE STRING lk IDENTIFIER rk sc { Contour_file_st(); }
  | CONTOUR_FILE STRING lk IDENTIFIER rk lb setting_list rb sc
       { Contour_file_st_with_setting( settings ); settings = 0; }
  /* --------------------------------------------------------------
   *  perspect 文  [ 変数名 ];
   * 
   *  変数はfem変数でなければいけない。
   * --------------------------------------------------------------*/
  | PERSPECT lk IDENTIFIER rk sc { Perspect_st(); }
  | PERSPECT lk IDENTIFIER rk lb setting_list rb sc 
       { Perspect_st_with_setting(settings); settings = 0; }

  /* --------------------------------------------------------------
   *  displacement 文  [ 変数名 ](fact=200);
   *
   *  変数はfem変数でなければいけない。
   * --------------------------------------------------------------*/
  | DISPLACEMENT lk IDENTIFIER co IDENTIFIER rk sc {Displacement_st();}
  | DISPLACEMENT lk IDENTIFIER co IDENTIFIER rk lb setting_list rb sc 
       { Displacement_st_with_setting( settings ); settings = 0; }

  /* --------------------------------------------------------------
   *  AVScontour 文  [ 変数名 ];
   * 
   *  変数はfem変数でなければいけない。
   * --------------------------------------------------------------*/
/*  | AVS_CONTOUR lk IDENTIFIER rk sc { AVScontour_st(); } */

  /* --------------------------------------------------------------
   *  write文 これはfeelの引き数をFORTRAN77に直接出力します
   *          文字列は、feelの規格で "..."と入力し、'は含まぬ様注意してね
   * --------------------------------------------------------------*/
  | WRITE {Write_parse_init(); } lb write_components rb sc { Write_st(); }
  | FILE_WRITE STRING {File_Write_parse_init(); } lb write_components rb sc 
                          { File_Write_st(); }

  /* --------------------------------------------------------------
   *  read文  これはfeelの引き数をFORTRAN77に直接出力します
   *          文字列は、feelの規格で "..."と入力し、'は含まぬ様注意してね
   * --------------------------------------------------------------*/
  | READ lb parameter_list rb sc { Read_st(parameters); parameters = 0; }

  /* --------------------------------------------------------------
   *  xplot文  与えられた点列(今はlineを想定)上のデータをウインドウ表示
   *  xplot[線の名称,出力するfem変数,...(x,y,zの空間変数も可) ]
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
   *  plot-file文  与えられた点列(今はlineを想定)上のデータをファイルに
   *          出力する
   * 
   *  plot 'ファイル名'[線の名称,出力するfem変数,...(x,y,zの空間変数も可) ]
   * --------------------------------------------------------------*/
  | PLOT_FILE STRING lk parameter_list rk sc { plot_st(parameters);  parameters = 0;}
  | TIME_PLOT_FILE STRING lk parameter_list rk sc {time_plot_st(parameters);
						   parameters = 0;
					       }

  /* --------------------------------------------------------------
   *  if文 関係
   * --------------------------------------------------------------*/
  | IF  condition  THEN               {p_if_then(if_left_ptr,condition_type );}
  | IF  condition  GOTO IDENTIFIER sc {p_if_goto(if_left_ptr,condition_type );}
  | ELSE           { p_else();  }
  | ENDIF sc       { p_endif(); }
  /*===============================================================
    solve ブロックの文法定義
    ===============================================================*/
  | solve_block

write_components
  : expression   { write_st_expression(); }
  | STRING       { write_st_string(); }
  | write_components co expression { write_st_expression(); }
  | write_components co STRING     { write_st_string(); }






/*-------------------------
  solve ブロック
  -------------------------*/
/*  計算領域:未知変数(既知変数):数値積分法:形状変換関数
 *
 *
 *  solve文  線形の偏微分方程式、弱形式、汎関数停留値問題を記述する
 * 
 *  solve [未知fem変数]{
 *  
 *  domain: 領域名;   新たに宣言する迄の問題が一つのSolveElementになる
 *                    省略可能(唯一のdomain文を採用)
 *                    ------------------------------
 *                    領域を指定する際には方程式群の前に必ず実行
 *    
 *  subdomain: 領域名 
 *    
 *  linear method: 連立一次方程式解法;  これはsolve文中一つだけ使用可能
 *  quadrature method: 数値積分法;      これは各SolveElementに対して指定する
 *  boundary quadrature: ガウス積分次数;  境界積分のガウス数値積分法次数の指定
 *  isoparametric;     アイソパラメトリック指定
 *                                    
 *  symmetry;          対称行列の指定
 *  nonlinear;         非線形方程式の指定
 * 
 *  initial u = FEM変数式;  非線形方程式の初期値設定
 *
 *  eps = 数値              収束判定条件
 *
 *  newton-factor 緩和係数; Newton-Raphson反復時の緩和計数を指定する
 *
 *  shape 形状関数名   形状関数の陽的な指定
 *                                    
 *
 *  eq: 偏微分方程式 {,[積分方法]偏微分方程式}{,<境界積分項>},{,@試験関数名} ;
 *        .....
 *  weq: 偏微分方程式の弱形式、境界積分項は<...>に記述 , 試験関数名 ;
 *       弱形式中、試験関数は$で記述する。
 *  
 *  eigen: 固有値問題    eigen: A,B;    A[u] = λB[u]を求める
 *
 *
 *  func: 汎関数名、境界積分項は <....>に記述;
 *
 *  weq: expr1,expr2,<expr3>;
 *  は、expr1+expr2+expr3=0という方程式に相当する。 
 *
 *--------------------------------------------------------------------
 *  境界条件は、一つのsolve文に対して1set指定する。
 *  
 *  
 *--------------------------------------------------------------------
 * 
 *  非線形方程式の場合は、solve → nonlinear とする。
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
         /* dbg: CAUTION: 積分法指定時の内挿指定法付記述を完成すること */
  | SUBDOMAIN cc IDENTIFIER sc         {p_solve_subdomain(); }  /* oimo 注意
								1995/12/8
								流用した */
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


equations          /* 方程式記述 */
  : equation              
  | equations equation    


b_conditions       /* 境界条件 */
  : b_condition
  | b_conditions b_condition


/*------------------------*/
/* 偏微分方程式の指定方法 */
/* 弱形式を含む           */
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
  : ATMARK IDENTIFIER                  /* 試験(重み)関数の定義 */
                      {p_solve_test_function(); }
  | expression                         /* 普通の指定           */
                      {p_solve_expression();    }
  | lk IDENTIFIER rk expression        /* 数値積分法指定付き */
                      {p_solve_expression_with_quad_method(); }
  | lt expression gt                   /* 境界積分項 */
                      {p_solve_boundary_term(); }
  | lk IDENTIFIER rk lt expression gt  /* 数値積分法指定付き境界積分項 */
                      {p_solve_boundary_term_with_quad_method(); }
/*----------*/
/* 境界条件 */
/*----------*/
/*--------------------------------------------------------------------
 *  境界リストは,
 *
 *  on a,b,[1];  など
 *
 *  dbc: ディリクレ境界条件(基本境界条件)を記述
 *       未知変数名 = 式  , on 境界リスト;
 *  nbc: ノイマン境界条件(自然境界条件)を記述
 *       境界積分項に現れる式 = 式 , 式 = 式 , on 境界リスト ;
 *       汎関数、弱形式で境界積分項が陽に記述されている場合は、
 *       記述の制限が緩められる(緩めたい)
 * 
 *  数値データとして与えられる境界条件
 * 
 *  A)ディリクレ境界条件
 *  dbc:  未知変数名  =  [データセット番号];  【注意】現在未対応
 * 

 これはバックアップ
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
  | IDENTIFIER                             /* シンボル */
{      expressions++;
       push_identifier_and_push();         /* 数式中のシンボルをpopして格納後
					      またpushする関数(YaccExp..c)   */
       tmp_pop = (char *)pop();
       exp_atom_push(tmp_pop);
}
/*----------------------------*/
/*  方針変更(境界積分項、数値積分の指定方法)     */
/*----------------------------*/
/*  | lk IDENTIFIER rk lb expression rb  */    /* 数値積分法が指定された数式 ← ここはちょっと変更  */  

  | IDENTIFIER  lb { push_function_and_push(); } expression rb  
{      expressions++;                      /* 関数 */
       tmp_pop = (char *)pop();
       exp_func_push(tmp_pop);               /* 数式中に出現する関数名をpop  */
}                                          /* して格納後またpushする       */
  | IDENTIFIER lk expression rk
{                                          /* 配列 
					      これは、拘束条件付きelement宣言
					      文で現れる。                   */
       expressions++;
       push_identifier_and_push();         /* 数式中のシンボルをpopして格納後
					      またpushする関数(YaccExp..c)   */
       tmp_pop = (char *)pop();
       exp_array_push(tmp_pop);
}
  | mi expression  /* 単項演算子 */
{
    exp_minus_push();
}
  | lb expression rb        /* 括弧でくくられた数式(なにも処理しない) */    

/*----------------------------*/
/*  方針変更(境界積分項、数値積分の指定方法)     */
/*----------------------------*/
/*  | lt expression gt  */      /* 境界積分を表す数式 < ... > */
/*----------------------------*/
/*  方針変更(境界積分項、数値積分の指定方法)     */
/*----------------------------*/
/*  |  lk IDENTIFIER rk lt expression gt */    /* 数値積分法が指定された数式 */
                                           /* 境界積分項                 */
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
