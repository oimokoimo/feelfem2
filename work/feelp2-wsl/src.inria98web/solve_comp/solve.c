/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve.c
 *      Date:   1993/07/08
 *   
 *   Purpose:   solve文のパーサ
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "../scheme_comp/scheme_comp.h"
#include "solve_comp.h"

#include "../parallel/parallel.h"

static int    solves = 0;         /* solve文のcounter  
				     【注意】０にここで初期化 */

                                       
static Solve *solve[MAX_SOLVE];   /* solve文記録用配列織 */
static int isoparametric;         /* アイソパラメトリック要素フラグ */
static char  *shape_name;
static int nonlinear_flag;
static int initial_settings;
static char *eps_setting;
static char *initial_name[MAX_EQUATIONS];
static int initial_yylineno[MAX_EQUATIONS];
static Expression *initial_expr[MAX_EQUATIONS];
static int symmetry_flag;
static int boundary_gauss_points;    /* 境界積分項のガウス点数 */
static Expression   *newton_factor;
static int        yy_newton_factor;
static Expression   *newton_times;
static int        yy_newton_times;

static int        eigen_problem;     /* 固有値問題か否か？ */

/* 方程式の本体関係記録用 */

static int elemg;                 /* 要素グループ数 = domainの数
				                    = SolveElementの数 */
static SolveElement *solve_element[MAX_SOLVE_ELEMENT];

static Equation   *equation[MAX_EQUATIONS];       /* eq:等の一行の情報 */
static Expression *eq_term [MAX_EQUATION_TERMS];  /* 各数式バッファ    */
static Expression *bd_term [MAX_EQUATION_TERMS];  /* 境界式バッファ    */
static char       *eq_method[MAX_EQUATION_TERMS]; /* 数値積分法        */
static char       *bd_method[MAX_EQUATION_TERMS]; /* 境界条件数値積分法*/

static char *neumann_arg_name[MAX_NEUMANN_ARGS];  /* ノイマン境界条件に
						     指定する仮変数名  */
static Expression *neumann_arg_expr[MAX_NEUMANN_ARGS];
static int neumann_args;

static int  equations;            /* 方程式の総数 */
static int  eq_expressions;       /* 領域項の数式カウンタ */
static int  bd_expressions;       /* 境界項の数式カウンタ */

static char *quad_method;         /* 現在quad method文で明示的に定義された
				     数値積分法                            */
static int   isoparemetric = NO;  /* アイソパラメトリック要素指定 */
static char *linear_method;       /* 現在method文で明示的に定義された
				     連立一次方程式解法                    */
static char *current_domain;      /* 現在指定されている領域                */
static char *current_subdomain;   /* 現在指定されているsubdomain名         */

static char *test_function;       /* 試験関数 */


/* 境界条件関係記録用 */

static int  dconds;               /* ディリクレ境界条件の数 */
static int  nconds;               /* ノイマン境界条件の数   */

static DirichletData *dirichlet_data[MAX_BCONDS]; /* ディリクレ条件記録用 */
static NeumannData *neumann_data[MAX_BCONDS];     /* ノイマン条件記録用   */


/*
 *   solve文構文解析の開始ルーチン
 */

solve_parse_init()
{
    elemg     = 0;           /* 要素グループの数＝domaiの数 */
    equations = 0;           /* 方程式の数 */
    eigen_problem  = NO;     /* 固有値問題フラグ   */

    quad_method    = NULL;   /* 数値積分法         */
    linear_method  = NULL;   /* 連立一次方程式解法 */
    current_domain = NULL;   /* 領域名             */
    current_subdomain = NULL;/* サブ領域名         */


    boundary_gauss_points = 3; /* default の境界積分点におけるガウス積分点数 */

    test_function  = NULL;   /* 試験関数の初期化   */

    isoparametric  = NO;     /* アイソパラメトリック指定 */
    nonlinear_flag = NO;     /* 非線形フラグはNO         */

    eps_setting    = NULL;   /* 非線形収束判定条件       */

    initial_settings =0;     /* 初期値設定数は０         */

    newton_factor  = NULL;   /* 緩和係数の初期化         */
    yy_newton_factor = 0;

    newton_times   = NULL;
    yy_newton_times  = 0;

    shape_name     = NULL;   /* 形状変換関数名           */
    symmetry_flag  = NO;     /* 対称行列フラグ           */

    eq_expressions = 0;
    bd_expressions = 0;

    dconds = 0;              /* ディリクレ境界条件の数 */
    nconds = 0;              /* ノイマン境界条件の数   */

    solve[solves]  = (Solve *)FEEL_GetMemory( sizeof(Solve) );

    /* 構造体初期化処理 */
    solve[solves]->linear_method = NO;

    return;
}

/*
 *  未知変数の登録 
 */

p_solve_unknowns( parameters )
     int parameters;
{
    int i;
    char **unknown_name;   /* 未知変数名へのポインタ */
    
    unknown_name = (char **)FEEL_GetMemory(sizeof(char *)*parameters);

    for(i=0;i<parameters;i++) {
	*(unknown_name + parameters - i - 1) = PopString();
    }

    solve[solves]->unknowns = parameters;
    solve[solves]->unknown_name = unknown_name;

    return;
}

/*
 *   標準で使用する数値積分法の指定
 */

p_solve_quadrature_method()
{
    quad_method = PopString();   /* これはSolveElement構造体に指定 */

    return;
}

/*
 *   境界積分のガウス数値積分点数の構文解釈
 */
p_solve_boundary_quadrature()
{
    boundary_gauss_points = PopInt(); /* 数値積分点数 */
    if(boundary_gauss_points <1 || boundary_gauss_points >MAX_GAUSS_POINTS) {
	if(english_mesg) {
	    SystemWarning_yy("Illegal boundary quadrature method is specified.",
			     yylineno_info());
	}
	else {
	    SystemWarning_yy("境界ガウス点指定が不正(3点積分を選択)",
			     yylineno_info());
	}
	boundary_gauss_points = 3;
    }
    return;
}


/*
 *   アイソパラメトリック要素の指定
 */
p_solve_isoparametric()
{
    isoparametric = YES;

    if(english_mesg) {
	SystemWarning("High-degree isoparametric element specified.");
    }
    else {
	SystemWarning("現在(高次)isoparametric要素には対応していません。");
    }

    return;
}

/*
 *  形状関数の指定
 */
void p_solve_shape()
{
    shape_name = PopString();
    
    return;
}

/*
 * 非線形問題指定
 */
void p_solve_nonlinear()
{
    if(elemg != 0) {
	if(english_mesg) {
	    SystemError_yy("nonlinear definition after equation definitions",
			   yylineno_info());
	}
	else {
	    SystemError_yy("方程式が指定された後にnonlinearを宣言した",
			   yylineno_info());
	}
    }
    nonlinear_flag = YES;
}


/*
 *  非線形時の収束条件設定
 */
void p_solve_eps()
{
    eps_setting = PopString();
    return;
}

/*
 *  非線形時の初期値設定 
 */
void p_solve_initial()
{
    if(initial_settings == MAX_EQUATIONS) {
	if(english_mesg) {
	    SystemError_yy("Too many initial value definitions",
			   yylineno_info());
	}
	else {
	    SystemError_yy("初期値の設定が多すぎる",yylineno_info());
	}

	get_expr_structure();
	PopString();
	return;
    }
    
    initial_expr[initial_settings] = get_expr_structure();
    initial_name[initial_settings] = PopString();
    initial_yylineno[initial_settings] = yylineno_info();
    initial_settings++;
    return;
}
/*
 * 非線形問題時の緩和係数設定
 */
void p_solve_newton_factor()
{
    if(newton_factor != NULL) {
	if(english_mesg) {
	    SystemError_yy("Too many newton-factor sentences",yylineno_info());
	}
	else {
	    SystemError_yy("複数のnewton-factor宣言をした",yylineno_info());
	}
    }
    newton_factor = get_expr_structure();
    yy_newton_factor = yylineno_info();

    return;
}

void p_solve_newton_times()
{
    if(newton_times != NULL) {
	if(english_mesg) {
	    SystemError_yy("Too many newton-times sentences",yylineno_info());
	}
	else {
	    SystemError_yy("Too many newton-times sentences",yylineno_info());
	}
    }
    newton_times    = get_expr_structure();
    yy_newton_times = yylineno_info();

    return;
}

/*
 *  対称行列指定
 */
void p_solve_symmetry()
{
    symmetry_flag = YES;
}



/*
 *   領域の指定 
 */

p_solve_domain()
{
    char *domain_name;

    domain_name = PopString();

/*    printf("domain:指定がされました。 %s  equations=%d elemg=%d\n",
	   domain_name,equations,elemg);
*/

    if(equations == 0 && elemg != 0) { /* domain文を指定する時は、すべての
					  方程式の記述に優先する         
					  この場合は、方程式が指定されていない
					  のに２度目のdomain文が呼び出された
					  ということになる。  
					  */
	if(english_mesg) {
	    SystemError_yy("domain definition must be the top of solve block",
			   yylineno_info());
	}
	else {
	    SystemError_yy("solve文でのdomain指定位置が不正である",yylineno_info());
	}
	return;
    }

    
    /* 最初の方程式群に対してdomainが指定されていない場合のエラー処理 */
    if(equations != 0 && current_domain == NULL) {
	if(english_mesg) {
	    SystemError_yy("ERROR: solve.c(1): future function",
			   yylineno_info());
	}
	else {
	    SystemError_yy("solve文中にdomain指定をする場合全ての方程式に対して指定すること",yylineno_info());
	}

	Make_SolveElement();            /* 一応作る */

	current_domain = domain_name;   /* 次の為に */ 
	return;
    }

    if(elemg != 0 || (equations != 0 && current_domain != NULL)) {
	Make_SolveElement();   /* 前のdomainで指定された要素単位構造体の作成 */
    }

/*    elemg++;   */                /* 注意CAUTION:ここでは必要無し？ */

    current_domain = domain_name;

    return;
}


/*
 *   領域の指定 
 */

p_solve_subdomain()
{
    char *subdomain_name;
    subdomain_name = PopString();
    current_subdomain = subdomain_name;
    return;
}

/*
 *  連立一次方程式解法の指定
 */ 

p_solve_linear_method()
{
    if(linear_method != NULL) {
	if(english_mesg) {
	    SystemError_yy("Solver definition must be alone in each solve block",yylineno_info());
	}
	else {
	    SystemError_yy("solve文内では一つの連立一次解法しか指定できない",
			   yylineno_info());
	}

	pop();
	return;
    }

    linear_method = PopString();

    
    /* SKYLINE法か？ */
    if(streq(linear_method , SKYLINE_METHOD)) {
	solve[solves]->linear_method = SKYLINE;
	if(parallel) {
	    if(english_mesg) {
		SystemError("skyline method is not available with parallel option now.");
	    }
	    else {
		SystemError("skylineは並列処理に使用不可");
	    }

	}
	return;
    }

    /* PCGS法か？ */
    if(streq(linear_method , PCGS_METHOD)) {
	solve[solves]->linear_method = PCGS;
	UseLibrary(ITERATIVE_SOLVER,"pccg");
	if(parallel) {

	    if(english_mesg) {
		SystemError("pcgs is not available with parallel option now.");
	    }
	    else {
		SystemError("pcgsは並列処理に使用不可");
	    }

	}
	return;
    }

    /* PBCG法か？ */
    if(streq(linear_method , PBCG_METHOD)) {
	solve[solves]->linear_method = PBCG;
	UseLibrary(ITERATIVE_SOLVER,"pbcg");
	if(parallel) {
	    
	    if(english_mesg) {
		SystemError("pbcg is not available with parallel option now.");
	    }
	    else {
		SystemError("pbcgは並列処理に使用不可");
	    }
	}
	return;
    }

    if(streq(linear_method , MPPSCG_METHOD)) {
	solve[solves]->linear_method = MPPSCG;
	UseLibrary(MPP_SOLVER,"pbcg");

	if(parallel == 0) {

	    if(english_mesg) {
		SystemError("mppscg method is available only for parallel version.");
	    }
	    else {
		SystemError("mppscgは並列処理にのみ使用可");
	    }

	}
	return;
    }


    /* ICCG法か？ */
    if(streq(linear_method , ICCG_METHOD)) {
	solve[solves]->linear_method = ICCG;
	
	if(english_mesg) {
	    SystemError("ICCG is not available now.");
	}
	else {
	    SystemError("現在ICCG法はサポートしていません");
	}

	return;
    }

    if(english_mesg) {
	SystemError_s("Solver method %s is not registered.",linear_method);
    }
    else {
	SystemError_s("連立一次方程式解法 %s は登録されていません",linear_method);
    }

    return;
}

/*
 *   試験関数の設定
 */
p_solve_test_function()
{
    if( test_function != NULL ) {

	if(english_mesg){
	    SystemError_yy("Too many test function definitions",
			   yylineno_info());
	}
	else {
	    SystemError_yy("複数の試験関数が指定されています。",yylineno_info());
	}

	pop();
	return;
    }

    test_function = PopString();

    return;
}

/*
 *  領域積分項の設定(数値積分法はなし)
 */
p_solve_expression()
{
    if(eq_expressions == MAX_EQUATION_TERMS) {

	if(english_mesg) {
	    SystemError("Too many terms in one equation");
	}
	else {
	    SystemError("一つの方程式を構成する項が多すぎます。");
	}

	get_expr_structure();
	return;
    }

    eq_term[eq_expressions] = get_expr_structure();
    eq_method[eq_expressions] = quad_method;  /* デフォルト数値積分法 */
    
    eq_expressions++;

    return;
}

/*
 *  境界積分項(数値積分法は指定されていない)
 */
p_solve_boundary_term()
{
    if(bd_expressions == MAX_EQUATION_TERMS) {

	if(english_mesg) {
	    SystemError("Too many terms in boundary expression");
	}
	else {
	    SystemError("一つの方程式を構成する項が多すぎます。");
	}

	get_expr_structure();
	return;
    }

    bd_term[bd_expressions] = get_expr_structure(); 
    bd_method[bd_expressions] = NULL;   /* 数値積分法境界積分項に
					   デフォルトの数値積分法は無し  */

    bd_expressions++;

    return;
}

/*
 *  数値積分法の指定付の領域積分項
 */
p_solve_expression_with_quad_method()
{
    if(eq_expressions == MAX_EQUATION_TERMS) {
	
	if(english_mesg) {
	    SystemError("Too many terms in one equation");
	}
	else {
	    SystemError("一つの方程式を構成する項が多すぎます。");
	}

	get_expr_structure();
	return;
    }

    eq_term[eq_expressions] = get_expr_structure();
    eq_method[eq_expressions] = PopString();  /* 数値積分法 */
    
    eq_expressions++;

    return;
}

/*
 *  数値積分法の指定付の境界積分項
 */
p_solve_boundary_term_with_quad_method()
{
    if(bd_expressions == MAX_EQUATION_TERMS) {

	if(english_mesg){
	    SystemError("Too many terms in one equations.");
	}
	else {
	    SystemError("一つの方程式を構成する項が多すぎます。");
	}

	get_expr_structure();
	return;
    }

    bd_term[bd_expressions] = get_expr_structure();
    bd_method[bd_expressions] = PopString();  /* 数値積分法 */
    
    bd_expressions++;

    return;
}


/*
 *  偏微分方程式が与えられた
 */

p_EQ()
{
    int   i;
    Equation *eq_ptr;
    Expression **expr_ptrptr;
    char       **cp_ptrptr;
    
    if(equations == MAX_EQUATIONS) {

	if(english_mesg) {
	    SystemError_yy("Too many equations",yylineno_info());
	}
	else {
	    SystemError_yy("連立している方程式の数が多すぎます。",yylineno_info());
	}

	return;
    }

    if(eq_expressions == 0 ) {
	
	if(english_mesg) {
	    SystemError_yy("方程式が指定されていません。",yylineno_info());
	}
	else {
	    SystemError_yy("No equation is defined.",yylineno_info());
	}

	return;
    }

    eq_ptr= (Equation *)FEEL_GetMemory(sizeof(Equation));

    equation[equations] = eq_ptr;

    eq_ptr->type = DIFFEQ;   /* 偏微分方程式 */

    eq_ptr->yylineno = yylineno_info();
    eq_ptr->test_function = test_function;

    eq_ptr->equation_terms = eq_expressions;
    eq_ptr->boundary_terms = bd_expressions;


    /* 領域積分項の格納 */    

    expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Equation *) *
						eq_expressions        );
    cp_ptrptr   = (char **)FEEL_GetMemory(sizeof(char *) *
					  eq_expressions        );

    for(i=0;i<eq_expressions;i++) {
	*(expr_ptrptr+i) = eq_term[i];
	*(cp_ptrptr  +i) = eq_method[i];
    }
    eq_ptr->eq_term   = expr_ptrptr;
    eq_ptr->eq_method = cp_ptrptr;

    
    /* 境界項の格納 */
    if(bd_expressions != 0) {
	expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Equation *) *
						    bd_expressions        );
	cp_ptrptr   = (char **)FEEL_GetMemory(sizeof(char *) *
					      bd_expressions        );

	
	for(i=0;i<bd_expressions;i++) {
	    *(expr_ptrptr+i) = bd_term[i];
	    *(cp_ptrptr  +i) = bd_method[i];
	}

	eq_ptr->bd_term = expr_ptrptr;
	eq_ptr->bd_method = cp_ptrptr;
    }
    else {
	eq_ptr->bd_term   = NULL;
	eq_ptr->bd_method = NULL;
    }

    /* 記録用配列のリセット */
    test_function = NULL;
    eq_expressions = 0;
    bd_expressions = 0;

    /* equation[]へのポインタをincrement */
    equations++;

    return;
}


/*
 *  弱形式が与えられた
 */

p_WEQ(p_weq_type)
     int p_weq_type;
{
    int   i;
    Equation *eq_ptr;
    Expression **expr_ptrptr;
    char       **cp_ptrptr;

    if(p_weq_type == 0 && eigen_problem != NO) {

	if(english_mesg) {
	    SystemError_yy("Eigen problem is also definied.",yylineno_info());
	}
	else {
	    SystemError_yy("solve文内に固有値問題が混在している",
			   yylineno_info());
	}

    }

    if(equations == MAX_EQUATIONS) {
	if(english_mesg) {
	    SystemError_yy("Too many equations",yylineno_info());
	}
	else {
	    SystemError_yy("連立している方程式の数が多すぎる",
			   yylineno_info());
	}

	return;
    }

    if(eq_expressions == 0 ) {
	if(english_mesg) {
	    SystemError_yy("No equation is defined.",yylineno_info());
	}
	else {
	    SystemError_yy("方程式が指定されていません。",
			   yylineno_info());
	}

	return;
    }

    if(bd_expressions == 0) {
/*	SystemWarning_yy("弱形式中に境界積分項がありません。",
			 yylineno_info());
*/
    }

    eq_ptr= (Equation *)FEEL_GetMemory(sizeof(Equation));

    equation[equations] = eq_ptr;

    eq_ptr->type = WEAKEQ;   /* 弱形式 */

    eq_ptr->equation_terms = eq_expressions;
    eq_ptr->boundary_terms = bd_expressions;

    eq_ptr->test_function  = test_function;
    eq_ptr->yylineno       = yylineno_info();

    /* 領域積分項の格納 */    

    expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Equation *) *
						eq_expressions        );
    cp_ptrptr   = (char **)FEEL_GetMemory(sizeof(char *) *
					  eq_expressions        );

    for(i=0;i<eq_expressions;i++) {
	*(expr_ptrptr+i) = eq_term[i];
	*(cp_ptrptr  +i) = eq_method[i];
    }
    eq_ptr->eq_term   = expr_ptrptr;
    eq_ptr->eq_method = cp_ptrptr;

    
    /* 境界項の格納 */
    if(bd_expressions != 0) {
	expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Equation *) *
						    bd_expressions        );
	cp_ptrptr   = (char **)FEEL_GetMemory(sizeof(char *) *
					      bd_expressions        );

	
	for(i=0;i<bd_expressions;i++) {
	    *(expr_ptrptr+i) = bd_term[i];
	    *(cp_ptrptr  +i) = bd_method[i];
	}

	eq_ptr->bd_term = expr_ptrptr;
	eq_ptr->bd_method = cp_ptrptr;
    }
    else {
	eq_ptr->bd_term   = NULL;
	eq_ptr->bd_method = NULL;
    }

    /* 記録用配列のリセット */
    test_function = NULL;
    eq_expressions = 0;
    bd_expressions = 0;

    /* equation[]へのポインタをincrement */
    equations++;

    return;
}

/*
 *  固有値問題が与えられた(P2では暫定的に、積分が二つあるweq問題として扱う)
 */
p_EIGEN()
{
    if(equations != 0 ) {
	if(eigen_problem == NO) {

	    if(english_mesg) {
		SystemError_yy("There is another eigen-value problem in one solve block",yylineno_info());
	    }
	    else {
		SystemError_yy("solve文内に固有値問題が混在している",
			       yylineno_info());
	    }

	}
	eigen_problem = YES;
    }
    p_WEQ(1); 
}

/*
 *  汎関数の停留値問題が与えられた
 */

p_FUNC()
{
    int   i;
    Equation *eq_ptr;
    Expression **expr_ptrptr;
    char       **cp_ptrptr;
    
    if(equations == MAX_EQUATIONS) {
	if(english_mesg) {
	    SystemError_yy("Too many simultaneous equations",yylineno_info());
	}
	else {
	    SystemError_yy("連立している方程式の数が多すぎます。",yylineno_info());
	}

	return;
    }

    if(eq_expressions == 0 ) {
	if(english_mesg) {
	    SystemError_yy("No equation is specified.",yylineno_info());
	}
	else {
	    SystemError_yy("方程式が指定されていません。",yylineno_info());
	}

	return;
    }

    eq_ptr= (Equation *)FEEL_GetMemory(sizeof(Equation));

    equation[equations] = eq_ptr;

    eq_ptr->type = FUNCTIONAL;   /* 汎関数停留値問題 */

    eq_ptr->equation_terms = eq_expressions;
    eq_ptr->boundary_terms = bd_expressions;

    eq_ptr->yylineno       = yylineno_info();

    if(test_function != NULL) {
	if(english_mesg) {
	    SystemWarning_yy("There is test function symbol in functional.",
			     yylineno_info());
	}
	else {
	    SystemWarning_yy("汎関数問題に試験関数が指定されています",yylineno_info());
	}
    }

    test_function = NULL;


    /* 領域積分項の格納 */    

    expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Equation *) *
						eq_expressions        );
    cp_ptrptr   = (char **)FEEL_GetMemory(sizeof(char *) *
					  eq_expressions        );

    for(i=0;i<eq_expressions;i++) {
	*(expr_ptrptr+i) = eq_term[i];
	*(cp_ptrptr  +i) = eq_method[i];
    }
    eq_ptr->eq_term   = expr_ptrptr;
    eq_ptr->eq_method = cp_ptrptr;

    
    /* 境界項の格納 */
    if(bd_expressions != 0) {
	expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Equation *) *
						    bd_expressions        );
	cp_ptrptr   = (char **)FEEL_GetMemory(sizeof(char *) *
					      bd_expressions        );

	
	for(i=0;i<bd_expressions;i++) {
	    *(expr_ptrptr+i) = bd_term[i];
	    *(cp_ptrptr  +i) = bd_method[i];
	}

	eq_ptr->bd_term = expr_ptrptr;
	eq_ptr->bd_method = cp_ptrptr;
    }
    else {
	eq_ptr->bd_term   = NULL;
	eq_ptr->bd_method = NULL;
    }

    /* 記録用配列のリセット */
    test_function = NULL;
    eq_expressions = 0;
    bd_expressions = 0;

    equations++;            /* equation 記録インデックスのインクリメント */

    return;
}

/* 
 *  ノイマン境界条件のデータ構造体作成
 */
p_ncond_init()
{
    NeumannData *ptr;

    if(nconds == MAX_BCONDS) {
	if(english_mesg) {
	    SystemError_yy("Too many boundary conditions.",yylineno_info());
	}
	else {
	    SystemError_yy("境界条件の数が多すぎる",yylineno_info());
	}

	return;
    }
    ptr = (NeumannData *)FEEL_GetMemory(sizeof(NeumannData));

    neumann_data[nconds] = ptr;

    neumann_args = 0;

    ptr->args            =   0;
    ptr->yylineno  = yylineno_info();


    return;
}	

p_ncond_arg()
{

    if(nconds == MAX_BCONDS) {
	get_expr_structure();
	pop();
	return;
    }
    if(neumann_args == MAX_NEUMANN_ARGS) {

	if(english_mesg) {
	    SystemError_yy("Too many Neumann temporary variables",
			   yylineno_info());
	}
	else {
	    SystemError_yy("ノイマン境界条件での仮変数が多すぎる",yylineno_info());
	}

	get_expr_structure();
	pop();
	return;
    }	
    
    neumann_arg_expr[neumann_args] = get_expr_structure();
    neumann_arg_name[neumann_args] = PopString();
    
/*
    fprintf(stderr,"ノイマン条件仮変数 %s = %s\n",
	    neumann_arg_name[neumann_args],
	    neumann_arg_expr[neumann_args]->expr);
*/

    neumann_args++;

    return;
}

p_ncond_edge(parameters)
     int parameters;
{
    int i;
    char **arg;
    
    char       **left_var;
    Expression **expr_right;


    if(nconds == MAX_BCONDS) {
	for(i=0;i<parameters;i++) pop();
	return;
    }
    arg = (char **)FEEL_GetMemory(sizeof(char *)*parameters);

/*
    fprintf(stderr,"come to p_ncond_edge parameters = %d\n",parameters);
    fprintf(stderr,"neumann_args  = %d\n",neumann_args);
*/
    for(i=0;i<parameters;i++) {
	*(arg+parameters-i-1) = PopString();
    }

    neumann_data[nconds]->boundaries = parameters;    
    neumann_data[nconds]->b_name = arg;


    left_var   = (char **)FEEL_GetMemory(sizeof(char *) * neumann_args);
    expr_right = 
      (Expression **)FEEL_GetMemory(sizeof(Expression *) * neumann_args);

    neumann_data[nconds]->left_var = left_var;
    neumann_data[nconds]->expr_right = expr_right;


    neumann_data[nconds]->args = neumann_args;

    for(i=0;i<neumann_args;i++) {
/*	fprintf(stderr,"in ncond edge  %d  %s\n",i,
		*(left_var+i));
*/
	*(expr_right+i) = neumann_arg_expr[i];
	*(left_var  +i) = neumann_arg_name[i];
    }

    nconds++;

    return;
}


/*
 * ディリクレ境界条件の処理 
 */

p_dcond_var()
{
    DirichletData *ptr;

    if(dconds == MAX_BCONDS) {
	
	if(english_mesg) {
	    SystemError_yy("Too many boundary conditions.",yylineno_info());
	}
	else {
	    SystemError_yy("境界条件が多すぎます。",yylineno_info());
	}

	pop();
	return;
    }

    ptr = (DirichletData *)FEEL_GetMemory(sizeof(DirichletData));
    
    ptr->var  = PopString();
    ptr->yylineno = yylineno_info();  

    dirichlet_data[dconds] = ptr;
    
    return;
}

p_dcond_expr()
{

    if(dconds == MAX_BCONDS) {
	get_expr_structure();
	return;
    }

    dirichlet_data[dconds]->expr = get_expr_structure();

    return;
}

p_dcond_edge(parameters)
     int parameters;
{
    int i;
    char **arg;

    if(dconds == MAX_BCONDS) {
	for(i=0;i<parameters;i++) pop();
	return;
    }
    arg = (char **)FEEL_GetMemory(sizeof(char *)*parameters);

    for(i=0;i<parameters;i++) {
	*(arg+parameters-i-1) = PopString();
    }

    dirichlet_data[dconds]->boundaries = parameters;    
    dirichlet_data[dconds]->b_name = arg;

    dconds++;

    return;
}

/*
 *  Make_SolveElement()
 *
 *  各要素のプログラム本体の作成
 *
 *
 */
  
Make_SolveElement()
{
    int i;
    int type;

    SolveElement  *solve_element_ptr;
    Equation     **eq_data;

    if(elemg == MAX_SOLVE_ELEMENT) {
	if(english_mesg) {
	    SystemError("Too many Solve Elements(solve.c)");
	}
	else {
	    SystemError("作成要素数が多すぎます(solve_element)");
	}

	equations = 0;
	return;
    }

    if(equations == 0) {
	
	if(english_mesg) {
	    SystemError("No equation is defined in making solve element");
	}
	else {
	    SystemError("要素作成時に方程式が指定されていません。");
	}

	equations = 0;
	return;
    }
    if(equations != 1) { /* 連立問題の場合のエラーチェック */

	/* 汎関数問題の場合は常にエラー */
	for(i=0;i<equations;i++) {
	    if(equation[i]->type == FUNCTIONAL) {

		if(english_mesg) {
		    SystemError_yy("another functional is defined",yylineno_info());
		}
		else {
		    SystemError_yy("汎関数停留値問題に対して連立方程式が指定されています。",yylineno_info());
		}

		equations = 0;
		return;
	    }

	}
	
	type = equation[0]->type;

	for(i=1;i<equations;i++) {
	    if(equation[i]->type != type) {

		if(english_mesg) {
		    SystemError_yy("Both weak and strong form are defined.",
				   yylineno_info());
		}
		else {
		    SystemError_yy("連立問題で、弱形式と偏微分方程式系が混在しています。",yylineno_info());
		}

		equations = 0;
		return;
	    }
	}
    }

    type = equation[0]->type;   /* この要素に関する問題の形式 */

    solve_element_ptr = (SolveElement *)FEEL_GetMemory( sizeof(SolveElement) );

    solve_element_ptr -> type = type;         /* 方程式のタイプ */
    solve_element[elemg] = solve_element_ptr; /* SolveElement用配列に記憶 */

    solve_element_ptr -> domain_name    = current_domain;
    solve_element_ptr -> subdomain_name = current_subdomain;

    eq_data = (Equation **)FEEL_GetMemory(sizeof(Equation *)*equations);

    solve_element_ptr -> equations = equations;  /* 方程式の数 */
    solve_element_ptr -> eq_data   = eq_data;    /* 方程式へのポインタ */

    solve_element_ptr -> nonlinear_flag = nonlinear_flag;

    /* 形状変換関数の設定 */
    solve_element_ptr -> shape_func = shape_name;


    solve_element_ptr -> yylineno = yylineno_info();  /* 大体のソース行位置 */

    for(i=0;i<equations;i++) {
	*(eq_data+i) = equation[i];              /* 方程式のデータ */
    }

    elemg++;             /* elemg がSolveElementの総数と同じ */
    quad_method = NULL;  /* 数値積分法のデフォルト値は各SolveElement毎に有効 */
    shape_name = NULL;   /* 形状変換関数は各SolveElement毎設定 */

    equations = 0;
    eq_expressions = 0;

    return;
}



/*
 *  p_solve_complete()
 *
 *  solve文構造体の作成
 *
 */ 
    
p_solve_complete()
{
    int i;
    
    Solve *solve_ptr;

    SolveElement  **solve_element_ptrptr;
    DirichletData **dirichlet_ptr;
    NeumannData   **neumann_ptr;

    if(elemg == 0) {
	if(english_mesg) {
	    SystemError("No valid equation in solve block.");
	}
	else {
	    SystemError("solve文内に有効な方程式が記述されていません。");
	}

	solves++;
	return;
    }

    solve_ptr = solve[solves]; /* 領域はinitialize時に取得済み */

    solve_ptr ->solve_eigen_flag = eigen_problem;   /* 固有値問題かどうか */

    solve_element_ptrptr = (SolveElement **)FEEL_GetMemory(sizeof(SolveElement *)*
							elemg               );
    /* Dirichletデータ記録用領域取得 */
    if(dconds != 0) {
	dirichlet_ptr=(DirichletData **)FEEL_GetMemory(sizeof(DirichletData *)*
						       dconds );
    }
    else {
	dirichlet_ptr = NULL;
    }

    /* ノイマンデータ記録用領域取得 */
    if(nconds != 0) {
	neumann_ptr=(NeumannData **)FEEL_GetMemory(sizeof(NeumannData *)*
						       nconds );
    }
    else {
	neumann_ptr = NULL;
    }

    /* 連立一次方程式の解法設定 */
    if(solve[solves]->linear_method == NO ) {
	if(parallel) {
	    solve[solves]->linear_method = DEFAULT_MPP_LINEAR_METHOD;
	}
	else {
	    solve[solves]->linear_method = DEFAULT_LINEAR_METHOD;
	}
    }

    if(solve[solves]->linear_method == SKYLINE) {
	skyline_flag = 1;
    }

    /* 境界ガウス積分点数を指定 */
    solve[solves]->boundary_gauss_points = boundary_gauss_points;
    
    /* 対称フラグ、非線形フラグを入れる */
    solve[solves] -> symmetry_flag  = symmetry_flag;
    solve[solves] -> nonlinear_flag = nonlinear_flag;

    /* 非線形問題の場合の初期値代入指定 */
    solve[solves] -> initial_settings = initial_settings;
    solve[solves] -> initial_name = (char **)FEEL_GetMemory(sizeof(char *) *
							    initial_settings );
    solve[solves] -> initial_yylineno = (int *)FEEL_GetMemory(sizeof(int ) *
							    initial_settings );
    solve[solves] -> initial_expr = 
      (Expression **)FEEL_GetMemory(sizeof(Expression *) *  initial_settings );
    for(i=0;i<initial_settings;i++) {
	*(solve[solves] -> initial_name + i) = initial_name[i];
	*(solve[solves] -> initial_yylineno + i) = initial_yylineno[i];
	*(solve[solves] -> initial_expr + i) = initial_expr[i];
    }

    /*  非線形問題時の収束判定値代入 */
    solve[solves] -> eps_setting = eps_setting;


    /*  非線形問題時の緩和係数代入 */
    solve[solves] -> newton_factor = newton_factor;
    solve[solves] -> yy_newton_factor = yy_newton_factor;

    solve[solves] -> newton_times     = newton_times;
    solve[solves] -> yy_newton_times  = yy_newton_times;

    /* 格納用アドレスの代入 */
    solve[solves]->solve_elem_dat = solve_element_ptrptr;
    solve[solves]->d_dat    = dirichlet_ptr;
    solve[solves]->n_dat    = neumann_ptr;

    solve[solves]->solve_elements = elemg;
    solve[solves]->d_conditions   = dconds;
    solve[solves]->n_conditions   = nconds;

    solve[solves]->yylineno       = yylineno_info();

    for(i=0;i<elemg;i++) {
	*(solve_element_ptrptr+i) = solve_element[i];
    }
    
    for(i=0;i<dconds;i++) {
	*(dirichlet_ptr+i) = dirichlet_data[i];
    }

    for(i=0;i<nconds;i++) {
	*(neumann_ptr+i) = neumann_data[i];
    }

    /* scheme ブロックに登録 */
    store_scheme( SOLVE , solve[solves]);


    elemg  = 0;
    dconds = 0;
    nconds = 0;

    solves++;
    return;
}


/*
 *  solveブロック用の情報戻し関数群
 *
 *
 */

how_many_solves()
{
    return(solves);
}

Solve *get_nth_solve_ptr( n )
     int n;
{
    if(n < 0 || n >= solves) {
	if(english_mesg) {
	    SystemAbort("INNER ERROR(get_nth_solve_ptr");
	}
	else {
	    SystemAbort("内部エラー(get_nth_solve_ptr)");
	}
    }

    return( solve[n] );
}

