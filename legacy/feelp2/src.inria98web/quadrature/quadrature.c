/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1993/07/15
 *   
 *   Purpose:   quadrature.c
 *   Functions: 
 *              is_defined_quadrature( name ) 指定した名称を持つ数値積分法が
 *                                            定義されているかどうかを調べる
 *              
 *              【制限】
 *              現在、内挿値と変数の代入文に依存関係があるプログラムソース
 *              は生成していない。将来、計算量低減の為に一考の価値あり。
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "quadrature.h"

static Quadrature *quadXX[MAX_QUADRATURE];
static int quads = 0;

static int quad_dimension;     /* 積分の次数 */

/* 引き数情報 */
static int   quad_rvars;
static char *quad_rvar[MAX_QUAD_RVARS];
static char *quad_rvar_type[MAX_QUAD_RVARS];


static int quad_doubles;       /* 数値積分実数宣言 */
static char *quad_double_var[MAX_QUAD_DOUBLES];
static Expression *quad_double_expr[MAX_QUAD_DOUBLES];

static int quad_consts;        /* 数値積分定数宣言 */
static char *quad_const_var[MAX_QUAD_CONSTS];
static Expression *quad_const_expr[MAX_QUAD_CONSTS];

static int quad_lets;          /* 計算補助代入文 */
static char *quad_let_identifier[MAX_QUAD_LETS];
static int   quad_let_type[MAX_QUAD_LETS];
static Expression *quad_let_expr[MAX_QUAD_LETS];

/*
 *  依存関係を判定するフラグ類
 */

static int let_flag;           /* 代入文が宣言よりも後にあることを感知する
				  フラグ */
static int interpolate_flag;   /* 内挿値の指定が、通常の積分点、重み指定以前
				  に出現する際のエラーを感知するフラグ */
/* 
 *
 *積分点情報
 *
 */

static int quad_points;        /* 積分点数 */

static Expression *quad_r[MAX_QUAD_POINTS];  /* 積分点 r 座標 */
static Expression *quad_s[MAX_QUAD_POINTS];  /* 積分点 s 座標 */
static Expression *quad_tt[MAX_QUAD_POINTS];  /* 積分点 t 座標 */

static Expression  *weight[MAX_QUAD_POINTS]; /* 重み */


/* 内挿法付変数情報 */
static int   quad_interpolates;
static QuadInterpolate *current_interpolate_ptr; /* 変数の内挿補間点データ
						    収納位置ポインタ        */
static int   current_point_no;    /* 積分点座標番号【注意】積分点重み情報の
             	                                           配列番号を用いる */
static QuadInterpolate *q_ip[MAX_QUAD_INTERPOLATES];

/* 座標指定記憶スタック */
static Expression *tmp_rst[3];
static int         tmp_rsts;
static int         tmp_dimension;             /* 積分点の次元を入れる */

/*====================================================================*/

/*
 *  与えられた名称の数値積分法が登録されているかどうかを判定する
 */

int is_defined_quadrature( name )
     char *name;
{
    int i;
    
    for(i=0;i<quads;i++) {
	if(streq(name,quadXX[i]->name) ) return(YES);
    }
    return(NO);
}
    
/*
 *  メモリを取得し、数値積分名称の代入を行う
 */

void quadrature_parse_init()
{

    quadXX[quads] = (Quadrature *)FEEL_GetMemory(sizeof(Quadrature));
    quadXX[quads]->name = PopString(); /* 数値積分名称の設定 */

    quad_points  = 0;   /* 積分点数         */
    quad_rvars   = 0;   /* 内挿値指定付変数 */

    quad_doubles = 0;   /* 計算補助の為の変数 */
    quad_consts  = 0;   /* 計算補助の為の変数 */

    quad_lets    = 0;   /* 代入文の数 */

    tmp_rsts     = 0;   /* 座標記録用スタックポインタ初期化 */

    let_flag     =NO;
    interpolate_flag = NO;

    return;
}

/*
 *   定義されている基本要素形状の取得
 */
p_quadrature_shape()
{
    int etype;  /* 形状コード */

    char *cp;

    cp = pop();
    
    etype = get_etype_no( cp );  /* 要素形状番号に変換 エラーはERRを返す */

    quad_dimension = etype_dimension(etype);  /* etype に相当する次元を返す */
     
    quadXX[quads]->etype = etype;

    return;
}


/*
 *
 *  積分点座標をスタックに積む。(Expression 構造体)
 *
 */

void p_quad_coordinate_expr()
{
    Expression *expr;

    tmp_rst[tmp_rsts] = get_expr_structure();   /* 数式構造体 */

    tmp_rsts ++;

    return;
}

/*
 *
 *  積分点の座標の次元フラグを立てる
 *
 */

p_quadrature_coordinate_1dim()      /* 一次元 */
{
    
    tmp_dimension = 1;     /* tmp_rst 配列からの値の取得は次の段階で行う */

    tmp_rsts = 0;          /* スタッククリア */


    /* エラーチェック  quad_dimension が ０のときは、もともと間違い */

    if(quad_dimension !=0 && quad_dimension != tmp_dimension) {
	if(english_mesg) {
	    SystemError_yy("Illegal quadrature point cordinate",
			   yylineno_info());
	}
	else {
	    SystemError_yy("積分点の次元が違います",yylineno_info());
	}
    }

    return;
}


p_quadrature_coordinate_2dim()    /* 二次元 */
{
    
    tmp_dimension = 2;     /* tmp_rst 配列からの値の取得は次の段階で行う */

    tmp_rsts = 0;          /* スタッククリア */


    /* エラーチェック  quad_dimension が ０のときは、もともと間違い */

    if(quad_dimension !=0 && quad_dimension != tmp_dimension) {
	if(english_mesg) {
	    SystemError_yy("Illegal quadrature point cordinate",
			   yylineno_info());
	}
	else {
	    SystemError_yy("積分点の次元が違います",yylineno_info());
	}
    }

    return;
}


p_quadrature_coordinate_3dim()   /* 三次元 */
{
    
    tmp_dimension = 3;     /* tmp_rst 配列からの値の取得は次の段階で行う */

    tmp_rsts = 0;          /* スタッククリア */


    /* エラーチェック  quad_dimension が ０のときは、もともと間違い */

    if(quad_dimension !=0 && quad_dimension != tmp_dimension) {
	if(english_mesg) {
	    SystemError_yy("Illegal quadrature point cordinate",
			   yylineno_info());
	}
	else {
	    SystemError_yy("積分点の次元が違います",yylineno_info());
	}
    }

    return;
}


/*
 *
 * 積分点データ格納
 *
 */

p_quadrature_component()
{
    int i;

    if(interpolate_flag == YES) {
	if(english_mesg) {
	    SystemError_yy("Quadrature point specified after interpolation definitions",yylineno_info());
	}
	else {
	    SystemError_yy("変数に対する内挿指定後に積分点データがあります",
			   yylineno_info());
	}
	
	get_expr_structure();
	return;
    }


    if(quad_points == MAX_QUAD_POINTS) {
	if(english_mesg) {
	    SystemError_yy("Too many Quadrature points",yylineno_info());
	}
	else {
	    SystemError_yy("数値積分の積分点が多すぎます。",yylineno_info());
	}

	get_expr_structure();
	return;
    }

    quad_r[quad_points] = tmp_rst[0];
    quad_s[quad_points] = tmp_rst[1];
    quad_tt[quad_points] = tmp_rst[2];

    weight[quad_points] = get_expr_structure();   /* 数式構造体 */

    quad_points++;

    return;
}

/*-----------------------------------
 * 
 * 数値積分指定用補助変数宣言関係
 *
 *----------------------------------- */

/* 定数(各要素によらない) */
p_quadrature_const()
{
    if(let_flag != NO) {

	if(english_mesg) {
	    SystemError_yy("Quadrature constant definition is specified after let sentences",yylineno_info());
	}
	else {
	    SystemError_yy("数値積分指定時の定数変数宣言が代入文より後にある",
			   yylineno_info());
	}

	get_expr_structure();
	pop();

	return;
    }

    if(quad_consts == MAX_QUAD_CONSTS) {

	if(english_mesg) {
	    SystemError_yy("Too many quadrature constant variables");
	}
	else {
	    SystemError_yy("数値積分指定時の定数変数宣言が多すぎます",
			   yylineno_info());
	}

	get_expr_structure();
	pop();

	return;
    }
    
    quad_const_expr[quad_consts] = get_expr_structure();
    quad_const_var[quad_consts]  = PopString();
    quad_consts++;

    return;
}

/*========================*/
/* 実数(各要素毎に再計算) */
/*========================*/
/* 宣言のみ */
p_quad_double_identifier()
{

    if(let_flag != NO) {

	if(english_mesg) {
	    SystemError_yy("Quadrature variable definition is specified after let sentences",yylineno_info());
	}
	else {
	    SystemError_yy("数値積分指定時の実数変数宣言が代入文より後にある",
			   yylineno_info());
	}

	pop();

	return;
    }

    if(quad_doubles == MAX_QUAD_DOUBLES) {
	
	if(english_mesg) {
	    SystemError_yy("Too many quadrature variable definitions",
			   yylineno_info());
	}
	else {
	    SystemError_yy("数値積分指定時の実数変数宣言が多すぎます",
			   yylineno_info());
	}

	pop();

	return;
    }
    
    quad_double_expr[quad_doubles] = NULL;        /* 宣言のみの場合は NULL */
    quad_double_var[quad_doubles]  = PopString();
    quad_doubles++;

    return;
}


/* 宣言内式指定付 */
p_quad_double_identifier_with_expr()
{

    if(let_flag != NO) {

	if(english_mesg) {
	    SystemError_yy("Quadrature variable definition is specified after let sentences.",yylineno_info());
	}
	else {
	    SystemError_yy("数値積分指定時の実数変数宣言が代入文より後にある",
			   yylineno_info());
	}

	get_expr_structure();
	pop();

	return;
    }

    if(quad_doubles == MAX_QUAD_DOUBLES) {

	if(english_mesg) {
	    SystemError_yy("Too many quadrature variable definitions",
			   yylineno_info());
	}
	else {
	    SystemError_yy("数値積分指定時の実数変数宣言が多すぎます",
			   yylineno_info());
	}

	get_expr_structure();
	pop();

	return;
    }
    
    quad_double_expr[quad_doubles] = get_expr_structure();
    quad_double_var[quad_doubles]  = PopString();

    quad_doubles++;

    return;
}




/* 実数関係の代入文 */
p_quadrature_let_st()
{
    int i;
    int err_flag;       /* 代入文の変数種別(const/double)判別の為 */
    let_flag = YES;     /* 宣言文が先行していることを確認するためのフラグ */

    if(quad_lets == MAX_QUAD_LETS) {
	if(english_mesg) {
	    SystemError_yy("Too many let sentences in quadrature block",
			   yylineno_info());
	}
	else {
	    SystemError_yy("数値積分定義内の代入文が多すぎる",yylineno_info());
	}

	get_expr_structure();
	pop();
	return;
    }

    quad_let_expr[quad_lets] = get_expr_structure();
    quad_let_identifier[quad_lets]  = PopString();

    /* quad_let_typeの設定 */

    err_flag = YES;
    for(i=0;i<quad_consts;i++) {
	if(streq(quad_let_identifier[quad_lets],quad_const_var[i])) {
	    err_flag = NO;
	    quad_let_type[quad_lets] = CONST;
	    break;
	}
    }
    
    /* constとdoubleの変数名重複はquad_checkでやろう(現在未実行) dbg: */
    for(i=0;i<quad_doubles;i++) {
	if(streq(quad_let_identifier[quad_lets],quad_double_var[i])) {
	    err_flag = NO;
	    quad_let_type[quad_lets] = DOUBLE;
	    break;
	}
    }

    if(err_flag) {
	if(english_mesg) {
	    SystemError_yy("this quadrature variable is undefined",
			   yylineno_info());
	}
	else {
	    SystemError_yy("quadrature定義内の代入文の変数未定義",yylineno_info());
	}
	return;
    }

    quad_lets++;

    return;
}

/*
 *
 * 引き数データの構文解析
 *
 */

/* fem変数 */
p_quadrature_fem_var()
{

    if(quad_rvars == MAX_QUAD_RVARS) {
	
	if(english_mesg) {
	    SystemError_yy("Too many quadrature argument variables",
			   yylineno_info());
	}
	else {
	    SystemError_yy("数値積分法の引き数となる変数指定が多すぎる",
			   yylineno_info());
	}

	pop();  pop();
	return;
    }

    quad_rvar_type[quad_rvars] = PopString();  /* 基底関数(要素)名 */
    quad_rvar[quad_rvars]      = PopString();  /* 変数名           */

    quad_rvars++;

    return;
}

/* fem変数以外の引き数 */

p_quadrature_scalar_var()
{
    if(quad_rvars == MAX_QUAD_RVARS) {
	
	if(english_mesg) {
	    SystemError_yy("Too many quadrature argument variables.",
			   yylineno_info());
	}
	else {
	    SystemError_yy("数値積分法の引き数となる変数指定が多すぎる",
			   yylineno_info());
	}

	pop();
	return;
    }

    quad_rvar_type[quad_rvars] = NULL;         /* 基底関数名の場所 */
    quad_rvar[quad_rvars]      = PopString();  /* 変数名           */

    quad_rvars++;

    return;
}

/*
 *
 * 内挿指定変数の各積分点での内挿値
 *
 */

/* 内挿指定変数の名前から格納先のポインタを割り出す
   初めて出現する場合は、QuadInterpolate構造体の領域を確保する 
   ☆変数current_interpolate_ptr の設定を行う                      */

/* 【重要】引き数に指定されているかどうかは、check系ルーチンで行う */

p_quadrature_identifier()
{
    int i;

    char *name;

    QuadInterpolate *q_ptr;

    name = PopString();

    for(i=0;i<quad_interpolates;i++) {
	q_ptr = q_ip[i];

	/* 既に登録済み */
	if(streq(name,q_ptr->var_name)) {
	    current_interpolate_ptr = q_ptr;

	    /* name のメモリ開放は行わないが、まぁ、いいでしょう。 */

	    return;
	}
    }

    if(quad_interpolates == MAX_QUAD_INTERPOLATES) {

	if(english_mesg) {
	    SystemError_yy("Too many quadrature interpolation variables",
			   yylineno_info());
	}
	else {
	    SystemError_yy("内挿指定の変数の数が多すぎる",yylineno_info());
	}

	current_interpolate_ptr = q_ip[0]; /* エラーを起こさない為に
					      ０番変数に書く          */

	/* name のメモリ開放は行わないが、まぁ、いいでしょう。 */

	return;
    }

    /* 領域の取得 */

    q_ptr = (QuadInterpolate *)FEEL_GetMemory(sizeof(QuadInterpolate));

    q_ip[quad_interpolates] = q_ptr;
    current_interpolate_ptr = q_ptr;

    /* QuadInterpolateの初期化では、積分点数で取得サイズを決めるので、
       文法上、積分点と重みの指定が内挿法指定より後にあってはならない。 */

    q_ptr->var_name = name;    /* var_name の設定 */
    q_ptr->nodes    =    0;
    q_ptr->node_no  =(int *)FEEL_GetMemory(quad_points * sizeof(int));
    q_ptr->interpolate_expr = 
      (Expression **)FEEL_GetMemory(quad_points * sizeof( Expression *));


    return;
}

/* 各内挿補間法の格納   

   格納先の領域は、p_quadrature_identifier() で取得し、
   current_interpolate_ptr に入っている
 */
p_quadrature_interpolate()
{
    int i;
    int nodes;        /* 計算用 */
    int node_no;      /* starts 0 */
    int find_flag;
    Expression *expr_ptr;


    interpolate_flag =  YES;            /* 内挿変数が定義されたフラグ */

    expr_ptr = get_expr_structure();

    nodes = current_interpolate_ptr->nodes;
    
    if(quad_points == 0) {

	if(english_mesg) {
	    SystemError_yy("Interpolation definition was defined before quadrature point definitions",yylineno_info());
	}
	else {
	    SystemError_yy("数値積分点の指定の前に変数の内挿を指定した",
			   yylineno_info());
	}

	return;
    }

    if(nodes == quad_points ) {
	
	if(english_mesg) {
	    SystemError_yy("Too many interpolation points",
			   yylineno_info());
	}
	else {
	    SystemError_yy("内挿点の指定が多すぎる",yylineno_info());
	}

	return;
    }


    /* Node 番号の検索 (この検索では、文字列として節点座標を認識するので
                        積分点重み指定と全く同じ書き方をしなければならない)
     */

    find_flag = NO;

    for(i=0;i<quad_points;i++) {
	
	/* 【注意】文字列として比較する */

	/* ｒ座標 */
	if(streq(tmp_rst[0]->expr,quad_r[i]->expr)) {
	    /* １次元 */
	    if(quad_dimension == 1) {
		if(find_flag == YES) {

		    if(english_mesg) {
			SystemError_yy("Duplicated interpolation definitions",
				       yylineno_info());
		    }
		    else {
			SystemError_yy("内挿法指定が重複定義されている",
				       yylineno_info());
		    }

		    node_no   = i;
		    break;
		}

		find_flag = YES;
		node_no   = i;
	    }
	    
	    /* ｓ座標 */
	    if(streq(tmp_rst[1]->expr,quad_s[i]->expr)) {
		/* ２次元 */
		if(quad_dimension == 2) {
		    
		    if(find_flag == YES) {

			if(english_mesg) {
			    SystemError_yy("Duplicated interpolation definitions",
					   yylineno_info());
			}
			else {
			    SystemError_yy("内挿法指定が重複定義されている",
					   yylineno_info());
			}

			node_no   = i;
			break;
		    }
		    
		    
		    find_flag = YES;
		    node_no   = i;
		}
		
		
		/* ｔ座標 */
		if(streq(tmp_rst[1]->expr,quad_tt[i]->expr)) {
		    /* ３次元 */
		    if(quad_dimension == 3) {
			
			if(find_flag == YES) {

			    if(english_mesg) {
				SystemError_yy("Duplicated interpolation definitions",
					       yylineno_info());
			    }
			    else {
				SystemError_yy("内挿法指定が重複定義されている",
					       yylineno_info());
			    }

			    node_no   = i;
			    break;
			}
			
			find_flag = YES;
			node_no   = i;
		    }
		} /* t coordinate check */
	    } /* s coordinate check */
	} /* r coordinate check */
    }  /* this is loop end */
    
    if(find_flag == NO) {
	
	if(english_mesg) {
	    SystemError_yy("There is no quadrature point correspond to this interpolation point.",yylineno_info());
	}
	else {
	    SystemError_yy("内挿指定点に対応する積分点がない",
			   yylineno_info());
	}

	return;
    }
    

    *(current_interpolate_ptr->node_no + nodes) = node_no;
    *(current_interpolate_ptr->interpolate_expr + nodes ) = expr_ptr;

    current_interpolate_ptr->nodes = nodes + 1;

    return;
}

/*
 *  quadrature 構文解析データの作成
 *
 *  quads  累積定義quadrature数
 *
 *  quad_points         積分点数
 *  quad_rvars
 *  quad_consts
 *  quad_doubles
 *  quad_lets
 *  quad_interpolates
 *  
 */
p_quadrature_complete()
{
    int i,j;

    Quadrature  *quad_ptr;
    QuadWeight **quad_weight_ptrptr;
    QuadWeight  *quad_weight_ptr;

    char **var_ptrptr;
    Expression **expr_ptrptr;
    int         *i_ptr;
    
    quad_ptr = quadXX[quads];

    /*  name  定義済み
	etype 定義済み
     */

    quad_ptr->dimension = quad_dimension;  /* 次元 */
    
    quad_ptr->nodes     = quad_points;     /* 積分点数 */

    if(quad_points == 0) {

	if(english_mesg) {
	    SystemError_yy("No quadrature point was specified.",
			   yylineno_info());
	}
	else {
	    SystemError_yy("数値積分の積分点が指定されていない",yylineno_info());
	}

	return;
    }

    /* 引き数の格納 */
    quad_ptr->rvars = quad_rvars;
    if(quad_rvars) {
	/* 変数名 */
	var_ptrptr = (char **)FEEL_GetMemory(sizeof(char *) * quad_rvars);
	quad_ptr->rvar_name = var_ptrptr;
	for(j=0;j<quad_rvars;j++) {
	    *(var_ptrptr+j) = quad_rvar[j];
	}
	/* 変数タイプ */
	var_ptrptr = (char **)FEEL_GetMemory(sizeof(char *) * quad_rvars);
	quad_ptr->rvar_name = var_ptrptr;
	for(j=0;j<quad_rvars;j++) {
	    *(var_ptrptr+j) = quad_rvar[j];
	}
    }


    /* 積分点へのポインタ */
    quad_weight_ptrptr  = (QuadWeight **)FEEL_GetMemory(sizeof(QuadWeight *)
							* quad_points       );
    quad_ptr->quad_weight_ptrptr = quad_weight_ptrptr;

    /* 積分点データ格納 */
    for(i=0;i<quad_points;i++) {
	quad_weight_ptr = (QuadWeight *)FEEL_GetMemory(sizeof(QuadWeight));
	*(quad_weight_ptrptr+i) = quad_weight_ptr;

	quad_weight_ptr -> r = quad_r[i];
	quad_weight_ptr -> s = quad_s[i];
	quad_weight_ptr -> t = quad_tt[i];

	quad_weight_ptr -> weight = weight[i];

/*	printf("INPUT -> (s) %s\n",quad_weight_ptr -> s -> expr); */
    }

    /* 定数データの格納 */
    quad_ptr->consts = quad_consts;
    if(quad_consts) {
	var_ptrptr = (char **)FEEL_GetMemory(sizeof(char *) * quad_consts);
	quad_ptr->const_var = var_ptrptr;
	expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Expression *) *
						    quad_consts           );
	quad_ptr->const_val = expr_ptrptr;

	for(j=0;j<quad_consts;j++) {
	    *(var_ptrptr+j) = quad_const_var[j];
	    *(expr_ptrptr+j) = quad_const_expr[j];
	}
    }

    /* 実数データの格納 */
    quad_ptr->doubles = quad_doubles;
    if(quad_doubles) {
	var_ptrptr = (char **)FEEL_GetMemory(sizeof(char *) * quad_doubles);
	quad_ptr->double_var = var_ptrptr;
	expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Expression *) *
						    quad_doubles           );
	quad_ptr->double_val = expr_ptrptr;

	for(j=0;j<quad_doubles;j++) {
	    *(var_ptrptr+j) = quad_double_var[j];
	    *(expr_ptrptr+j) = quad_double_expr[j];
	}
    }
    
    /* 代入文データの格納 */
    quad_ptr->quad_lets = quad_lets;
    if(quad_lets) {
	var_ptrptr = (char **)FEEL_GetMemory(sizeof(char *) * quad_lets);
	quad_ptr->let_var = var_ptrptr;
	expr_ptrptr = (Expression **)FEEL_GetMemory(sizeof(Expression *) *
						    quad_lets             );
	quad_ptr->let_val = expr_ptrptr;
	i_ptr = (int *)FEEL_GetMemory(sizeof(int) * quad_lets);
	quad_ptr->let_var_type = i_ptr;

	for(j=0;j<quad_lets;j++) {
	    *(var_ptrptr+j)  = quad_let_identifier[j];
	    *(expr_ptrptr+j) = quad_let_expr[j];
	    *(i_ptr+j)       = quad_let_type[j];
	}
    }
    
    /* 重複検査 */
    for(i=0;i<quads-1;i++) {
	if(streq(quadXX[i]->name , quadXX[quads]->name)) {
	    
	    if(english_mesg) {
		SystemError_s("Quadrature method %s is duplicatedly defined.",
			      quadXX[i]->name);
	    }
	    else {
		SystemError_s("数値積分法 %s は重複定義されている",quadXX[i]->name);
	    }
	}
    }

    quads++;

    return;
}

Quadrature *get_quadrature_ptr_by_name ( name )
     char *name;
{
    int i;


    for(i=0;i<quads;i++) {
	if(streq(quadXX[i] -> name , name) ) {
	    return(quadXX[i]);
	}
    }
    SystemAbort("UNKNOWN quadrature name(get_quadrature_ptr_by_name)");
}



/*
 *  デバッグチェックルーチン
 */

debug_quad(ptr)
     Quadrature *ptr;
{
    int i;
    QuadWeight *weight_ptr;
    QuadInterpolate *interpolate_ptr;
    Expression *expr_ptr;

    printf("quadrature デバッグコード\n");
    printf("数値積分名称 [%s]\n",ptr->name);
    printf("形状タイプ   [%d]\n",ptr->etype);
    printf("空間次元     [%d]\n",ptr->dimension);
    printf("\n");
    printf("引き数       [%d]  ",ptr->rvars);
    printf("定数変数     [%d]  ",ptr->consts);
    printf("実数変数     [%d]  ",ptr->doubles);
    printf("代入文       [%d]  ",ptr->quad_lets);
    for(i=0;i<ptr->rvars;i++) {
	if(i) printf("("); printf(",");
	printf("%s",*(ptr->rvar_name + i));
	if(*(ptr->rvar_type+i)!=NULL) printf("[%s]",*(ptr->rvar_type + i));
    }

    printf("積分点数     [%d]\n",ptr->nodes);
    for(i=0;i<ptr->nodes;i++) {
	weight_ptr = *(ptr->quad_weight_ptrptr+i);
	printf(" <%d> ",i);

	if(ptr->dimension == 1) {
	    printf("[%s] ",weight_ptr->r->expr);
	}

	if(ptr->dimension == 2) {
	    printf("[%s,%s] ",weight_ptr->r->expr,weight_ptr->s->expr);
	}

	if(ptr->dimension == 3) {
	    printf("[%s,%s,%s] ",weight_ptr->r->expr,weight_ptr->s->expr,weight_ptr->t->expr);
	}

	printf("%s\n",(weight_ptr->weight + i)->expr);
    }
    return;
}

/*====================================
  定義されている数値積分法の数を返す
  ====================================*/
int how_many_quads()
{
    return(quads);
}


/*====================================
  定義されている数値積分法の数を返す
  ====================================*/
Quadrature *get_nth_quad_ptr( n )
     int n;
{
    if( n < 0 || n >= quads) {
	SystemAbort("Illegal quad No. (get_nth_quad_ptr)");
    }

    return(quadXX[n]);
}
