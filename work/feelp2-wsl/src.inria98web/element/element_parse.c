/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   
 *      Date:   1993/05/25
 *   
 *   Purpose:   element文の処理(情報入力)
 *   Functions: element_parse_init();
 *              
 *              1993/11/18   element_let を追加  数値積分法指定時と
 *                                               同様な取扱を予定
 *              
 */

#include "../feel_def/feel_def.h"  /* feel p2 プログラム規定ヘッダー */
#include "../feel_def/pop.h"       /* modernize 2026/01/21  */
#include "../feel_def/feel_msg.h"  /* modernize 2026/01/22  */
#include "../system/system.h"
#include "element.h"
#include <stdlib.h>

static int elements = 0;  /* element文の数 */
static Element *element[MAX_ELEMENT];
void reduce_fraction(Frac *); 
int tri_node_order(Frac,Frac,int,Frac,Frac,int);
int rect_node_order(Frac,Frac,int,Frac,Frac,int);
int line_node_order(Frac,int,Frac,int);

int tri_node_cordinate_check(Frac,Frac);
int rect_node_cordinate_check(Frac,Frac);
int line_node_cordinate_check(Frac);

void element_order(int etype , int basis, Frac r[],Frac s[],Frac t[],int ntype[],Expression *expr[]);

/*--------- 構文解析中のスタック用配列----------*/
static  int basis;
static  int nodes;
static  int scalars;
static  int doubles;
static  int consts;
static  int lets;

static  Scalar scalar[MAX_ELEMENT_SCALAR]; /* element文中でマクロ定義される
					      スカラー変数用のスタック   */

static  char  *let_var_name[MAX_ELEMENT_LETS]; /* element文中のLET文 */
static  int    let_var_type[MAX_ELEMENT_LETS]; /* 代入クラス(const/double) */
static  Expression *let_expr[MAX_ELEMENT_LETS]; /* 代入文本体 */

static  Expression *expr[MAX_BASIS_PER_ELEMENT];

static  int     ntype[MAX_BASIS_PER_ELEMENT];
static  Frac   r_frac[MAX_BASIS_PER_ELEMENT];
static  Frac   s_frac[MAX_BASIS_PER_ELEMENT];
static  Frac   t_frac[MAX_BASIS_PER_ELEMENT];

static  int    restrains;
static  char  *restrain_fem_var_name[MAX_RESTRAINS];
static  char  *restrain_fem_var_type[MAX_RESTRAINS];

static  int    frac_stacks = 0;     /* 座標スタック */
static  Frac   frac_stack[3];

#include "../feel_def/feel_msg.h"
int element_etype_no(char *);
int get_etype_no(char *);

/*----------------------------------------------*/
void element_parse_init()    /* メモリを取得し、要素名の代入を行う */
{
    element[elements] = (Element *)FEEL_GetMemory(sizeof(Element));
    element[elements]->name = PopString();   /* 要素名の入力 */

    element[elements]->type = LAGRANGE;  /* デフォルト値の設定 */
    element[elements]->restrains = NO;    

    element[elements]->nodes = 0;        /* 構造体内の初期化 */
    element[elements]->basis = 0;
    element[elements]->scalar_vars = 0;

    element[elements]->yylineno = yylineno_info(); /* ソース上での位置 */

    nodes = 0;      /* スタック用配列の初期化 */
    basis = 0;
    scalars = 0;  /* 変数宣言 */
    doubles = 0;
    consts  = 0;
    lets  = 0;    /* 代入文用 */

    restrains = 0;

    return;
}


void p_element_let() /* 要素内で使用される実数変数の宣言 */
{
    int i;
    int err_flag;
    Expression *expr;

    err_flag = YES;

    expr = get_expr_structure();  /* メモリ獲得は関数内で */

    if(lets == MAX_ELEMENT_LETS) {
	SystemAbort("element文内の代入文が多すぎる");
    }

    let_expr[lets]          = expr;        /* 代入文本体   */
    let_var_name[lets]      = PopString(); /* 変数名の取得 */

    for(i=0;i<scalars;i++) {
	if(streq(scalar[i].name , let_var_name[lets]) ) {
	    let_var_type[lets] = scalar[i].type;
	    err_flag = NO;
	    break;
	}
    }

    if(err_flag) {
	SystemError_yy_s("element定義内の代入文の変数 %s は未定義",
		       let_var_name[lets],yylineno_info());
	return;
    }
    lets++;

    return;
}


void p_element_double() /* 要素内で使用される実数変数(宣言だけ) */
{
 
    if(scalars == MAX_ELEMENT_SCALAR) {
	SystemAbort("element文内の変数宣言が多すぎる");
    }
    scalar[scalars].type = DOUBLE;
    scalar[scalars].expr = NULL;

    scalar[scalars].name = PopString(); /* 変数名の取得 */

    scalars++;
    doubles++;

    return;
}

void p_element_double_with_expr() /* 要素内で使用される実数変数の宣言代入 */
{
    Expression *expr;

    scalar[scalars].type = DOUBLE;
    
    expr = get_expr_structure();  /* メモリ獲得は関数内で */

    scalar[scalars].expr = expr;

    scalar[scalars].name = PopString(); /* 変数名の取得 */

    scalars++;
    doubles++;

    return;
}

void p_element_const() /* 要素内で使用される実数変数の宣言 */
{
    Expression *expr;

    scalar[scalars].type = CONST;
    
    expr = NULL;  

    scalar[scalars].expr = NULL;

    scalar[scalars].name = PopString(); /* 変数名の取得 */

    scalars++;
    consts++;

    return;
}


void p_element_const_with_expr() /* 要素内で使用される実数変数の宣言 */
{
    Expression *expr;

    scalar[scalars].type = CONST;
    
    expr = get_expr_structure();  /* メモリ獲得は関数内で */

    scalar[scalars].expr = expr;

    scalar[scalars].name = PopString(); /* 変数名の取得 */

    scalars++;
    consts++;

    return;
}
    

 
void p_element_shape() /* 要素形状タイプの取得と入力 */
{
    int no;
    char *cp;
    cp = PopString();
    no = get_etype_no(cp);
    element[elements]->etype=no; 
    FEEL_FreeMemory(cp);
/*
    printf("要素タイプ番号＝%d\n",no);
*/
    return;
}

void  p_element_fem_restrains()
{
    if(restrains == MAX_RESTRAINS) {
	SystemParseWarning("Too many RESTRAIN fem variables.\n");
	pop(); pop();
    }

    restrain_fem_var_type[restrains] = PopString();
    restrain_fem_var_name[restrains] = PopString();

/*    printf("%s %s \n", restrain_fem_var_type[restrains],restrain_fem_var_name[restrains]);
*/
    restrains++;

    return;
}

/* 分数スタック関数 -----------------*/
static void push_frac( frac )
     Frac frac;
{
    if(frac_stacks == 3) {
	SystemAbort("push_frac error");
    }

    frac_stack[frac_stacks] = frac;

/*    printf("FRAC %d/%d\n",frac.bunsi,frac.bunbo);
*/

    frac_stacks ++;

    return;
}

static Frac pop_frac() 
{
    if(frac_stacks == 0) {
	SystemAbort("pop_frac error");
    }
    
    frac_stacks--;
    return(frac_stack[frac_stacks]);
}
/*------------------------------------*/


static void check_integer(cp) /* lex で num として字句解析されたものが整数か？ */
     char *cp;
{
    if(strindex(cp,".")) {
	SystemParseWarning("node cordinate must be fraction.\n");
    }
    
    return;
}

void p_node_cordinate( n )   /* 各分数成分をスタックに積む */
     int n;
{
    Frac frac;
    char *cp;
    
    if(n == 2) {
	cp = pop();
	check_integer(cp);

	frac.bunbo = atoi(cp);
    }
    else {
	frac.bunbo = 1;
    }

    cp = pop();
    check_integer(cp);
    frac.bunsi = atoi(cp);

    push_frac(frac);

    return;
}

void check_max_basis()                /* 最大要素内基底関数数に付いてチェック */
                                 /* と同時に、 ntypeの初期化    D0(zero) */
{
    if(basis == MAX_BASIS_PER_ELEMENT) {
	print_yylineno();
	SystemAbort("Too many basis functions in an element.\n");
    }
    ntype[basis] = D0;   /* D+'zero' */

    return;
}

void p_element_cordinate_2dim()  /* ２次元node座標をスタックに積む */
{
    Frac pop_frac();

    check_max_basis();

    s_frac[basis] = pop_frac();
    r_frac[basis] = pop_frac();

    return;
}

void p_element_cordinate_1dim()  /* １次元node座標をスタックに積む */
{
    Frac pop_frac();

    check_max_basis();

    r_frac[basis] = pop_frac();

    return;
}



static int get_ntype_no( s )  /* 節点値意味の文字列から節点値意味番号に変換 */
     char *s;
{
    if(streq( DX_KEY,s))  return(DX);
    if(streq( DY_KEY,s))  return(DY);
    if(streq( DZ_KEY,s))  return(DZ);
    if(streq( DN_KEY,s))  return(DN);
    if(streq( DXX_KEY,s))  return(DXX);
    if(streq( DYY_KEY,s))  return(DYY);
    if(streq( DZZ_KEY,s))  return(DZZ);
    if(streq( DXY_KEY,s))  return(DXY);
    if(streq( DYZ_KEY,s))  return(DYZ);
    if(streq( DZX_KEY,s))  return(DZX);

    print_yylineno();
    SystemWarning(NULL);
    SystemStderr(s);
    SystemStderr(" is not differential operator key word.\n");
    return(ERR);
}

void p_basis_type()             /* エルミート型のタイプを代入 */
{
    char *cp;
    cp = pop();
    ntype[basis] =  get_ntype_no(cp);

    element[elements]->type = HELMITE;  /* エルミートタイプ設定 */

    return;
}

void p_basis_complete()        /* 一つのbasisについての登録終了 */
{

    expr[basis] =  get_expr_structure();
    basis++;

}

/*
 * 関数 p_element_complete()
 */

void p_element_complete()
{
    int i,err_flag;
    Scalar *scalar_var;
    char  **char_ptrptr;
    Expression **expr_ptrptr;
    int    *i_ptr;

    /* 節点座標のチェック */

    err_flag = NO;

    for(i=0;i<basis;i++) {

	switch(element[elements]->etype) {
	  case TRI:
	    reduce_fraction(&r_frac[i]);       /* 約分処理 */
	    reduce_fraction(&s_frac[i]);
	    err_flag = tri_node_cordinate_check(r_frac[i],s_frac[i]);
	    break;

	  case RECT:
	    reduce_fraction(&r_frac[i]);       /* 約分処理 */
	    reduce_fraction(&s_frac[i]);
	    err_flag = rect_node_cordinate_check(r_frac[i],s_frac[i]);
	    break;

          case LINE:
	    reduce_fraction(&r_frac[i]);
	    err_flag = line_node_cordinate_check(r_frac[i]);
	    break;

	  default:
	    fprintf(stderr,"not implement(element_parse.c)\n");
	    break;
	}
	if(err_flag == ERR) {
	    SystemParseWarning("Wrong node cordinate.\n");
	}
    }
    element_order(element[elements]->etype,basis,
		  r_frac,s_frac,t_frac,ntype,expr);

    element[elements]->restrains = restrains;
    element[elements]->basis     = basis;


    /*----------------------------*/
    /* Element 構造体への代入処理 */
    /*----------------------------*/

    /* スカラー変数の登録処理 */
    
    element[elements]->scalar_vars = scalars;
    element[elements]->doubles     = doubles;
    element[elements]->consts      = consts;

    /* 積分点での基底関数評価が要素毎か、一度だけかの処理(94/06/28)*/
    if(doubles == 0) {
	element[elements]->quad_type   =  NO;
    }
    else {
	element[elements]->quad_type   = YES;
    }


    if(scalars != 0 ) {
	scalar_var = (Scalar *)FEEL_GetMemory(sizeof(Scalar)*scalars);
	element[elements]->scalar_var = scalar_var;

	for(i=0;i<scalars;i++) {
	    (scalar_var+i)->type = scalar[i].type;
	    (scalar_var+i)->name = scalar[i].name;
	    (scalar_var+i)->expr = scalar[i].expr;
	}

    }

    /* 代入文の登録処理 */
    if(lets != 0) {
	element[elements]->element_lets = lets;
	char_ptrptr = (char **)FEEL_GetMemory( sizeof(char *) * lets);
	expr_ptrptr = (Expression **)FEEL_GetMemory( sizeof(Expression *) *
						    lets                    );
	i_ptr       = (int *)FEEL_GetMemory(sizeof(int) * lets);
	element[elements]->let_var_name = char_ptrptr;
	element[elements]->let_var_type = i_ptr;
	element[elements]->let_expr     = expr_ptrptr;
	
	for(i=0;i<lets;i++) {
	    *(char_ptrptr+i) = let_var_name[i];
	    *(i_ptr      +i) = let_var_type[i];
	    *(expr_ptrptr+i) = let_expr[i];
	}
    }
	    
    /* 拘束変数名 */
    if(restrains == 0) {
	element[elements]->rest_var_name = NULL;
	element[elements]->rest_var_type = NULL;
    }
    else {
	element[elements]->rest_var_name = 
	  (char **)FEEL_GetMemory(sizeof(char *) * restrains);
	element[elements]->rest_var_type = 
	  (char **)FEEL_GetMemory(sizeof(char *) * restrains);
	for(i=0;i<restrains;i++) {
	    *(element[elements]->rest_var_name+i) = restrain_fem_var_name[i];
	    *(element[elements]->rest_var_type+i) = restrain_fem_var_type[i];
	}
    }

    /* 基底関数 */
    if(basis == 0 ) {
	SystemParseWarning("No basis function is specified.\n");
	elements++;
	return;
    }
    else {
	element[elements]->r_frac = 
	  (Frac *)FEEL_GetMemory(sizeof(Frac)*basis);
	element[elements]->s_frac = 
	  (Frac *)FEEL_GetMemory(sizeof(Frac)*basis);
	element[elements]->t_frac = 
	  (Frac *)FEEL_GetMemory(sizeof(Frac)*basis);

	element[elements]->ntype = 
	  (int *)FEEL_GetMemory(sizeof(int)*basis);

	element[elements]->expr = 
	  (Expression **)FEEL_GetMemory(sizeof(Expression *)*basis);

	for(i=0;i<basis;i++) {
	    *(element[elements]->r_frac+i) = r_frac[i];
	    *(element[elements]->s_frac+i) = s_frac[i];
	    *(element[elements]->t_frac+i) = t_frac[i];
	    
	    *(element[elements]->ntype +i) = ntype[i];

	    *(element[elements]->expr +i)  = expr[i];
	}
    }

    /* element名の重複検査 */
    for(i=0;i<elements-1;i++) {
	if(streq(element[i]->name,element[elements]->name)) {
	    SystemError_s("要素名%sが重複定義されています。",element[i]->name);
	}
    }


    elements++;

    return;
    
}

int how_many_elements()
{
    return(elements);
}

Element *get_nth_element_ptr( n )
     int n;
{
    if(n < 0 || n >= elements) {
	SystemAbort("get_nth_element_ptr ERROR");
    }

    return(element[n]);
}



Element *get_element_ptr_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<elements;i++) {
	if(streq(element[i]->name,name)) {
	    Element *ptr;
 	    
	    ptr = element[i];
	    
	    return(element[i]);
	}
    }
    return(NULL);  /* 指定されたFEM基底関数は定義されていない */
}

void show_element_structure()      /* デバッグ用関数 */
{
    int i,j,k;
    printf("登録 総要素数   %d\n",elements);
    
    for(j=0;j<elements;j++) {
	printf("element name : %s\n",element[j]->name);
	printf("element type : %d\n",element[j]->type);
	printf("element etype: %d\n",element[j]->etype);
	printf("element rest : %d\n",element[j]->restrains);
	printf("element line : %d\n",element[j]->yylineno);
    
	if(element[j]->scalar_vars != 0) {
	    printf("要素定義内スカラー変数 %d\n",element[j]->scalar_vars);
	    for(i = 0;i<element[j]->scalar_vars;i++ ) {
		Scalar *scalar_ptr;
		scalar_ptr = (element[j]->scalar_var + i);
		printf(" スカラー変数 %d 名称 %s   type %d  式 : %s\n",
		       i+1,
		       scalar_ptr -> name,
		       scalar_ptr -> type,
		       (scalar_ptr -> expr)->expr );
	    }
	}
		       
		

	for(i=0;i<element[j]->restrains;i++) {
	    printf("rest. No.%d  %s[%s]\n",i+1,
		   element[j]->rest_var_name[i],
		   element[j]->rest_var_type[i]);
	}

	for(i=0;i<element[j]->basis;i++) {
	    Expression *expr_ptr;
	    expr_ptr = *(element[j]->expr+i);
	    printf("basis. No.%d (%d/%d,%d/%d) type[%d] %s :",i+1,
		   element[j]->r_frac[i].bunsi,
		   element[j]->r_frac[i].bunbo,
		   element[j]->s_frac[i].bunsi,
		   element[j]->s_frac[i].bunbo,
		   element[j]->ntype[i],
		   expr_ptr->expr);
	    printf("identifiers : ");
	    for(k=0;k<expr_ptr->identifiers;k++) {
		printf("%s",*(expr_ptr->identifier+k));
		if(k!=expr_ptr->identifiers-1) printf(",");
	    }
	    printf("\n");

	    printf("functions   : ");
	    for(k=0;k<expr_ptr->functions;k++) {
		printf("%s",*(expr_ptr->function+k));
		if(k!=expr_ptr->functions-1)  printf(",");
	    }
	    printf("\n");
	}

	printf("\n");
    }
}
