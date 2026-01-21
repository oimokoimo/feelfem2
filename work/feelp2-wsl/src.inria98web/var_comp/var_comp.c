/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   var_comp.c
 *      Date:   1992/09/18(Made) 1993/06/03 (Modified)
 *   
 *  Modified:   1998/09/03 avs extension
 *   
 *   Purpose:   変数定義ブロック処理
 *              
 *   このファイルには次の２種類の関数群があります。
 *   1)  構文解析処理(データを構造体に落とすプログラム)
 *   2)  構造体のデータを抽出するプログラム
 *   3)  エラー検出プログラム(var_error_check()から呼び出される)
 *              
 *   構文解析に関するもの
 *   Functions: 
 *              
 *              
 *              
 *              
 *              
 */
#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../feel_def/basic_struct.h"
#include "var_comp.h"
#include "../system/system.h"

static int  vars = 0;
static int  int_vars   = 0;
static int  double_vars= 0;
static int  const_vars = 0;
static int  avs_variables = 0;

static int  fem_vars   = 0;
static int  fem_types  = 0;

static int  ewise_vars = 0;
static int  ewise_types = 0;

static int  material_vars = 0;
static Var  *var[MAX_VARIABLES];
static int  avs_var_no[MAX_VARIABLES];


static EWISE_type *ewise_type[MAX_EWISE_TYPES];
static FEM_type *fem_type[MAX_FEM_TYPES];

/* ユーザ定義関数名記憶 */
static int userfuncs = 0;
static char *userfunc_name[MAX_USERFUNCS];

/* 構文解析プログラム */

/* 構文解析時共通エラーチェックルーチン群 */
static int is_max_var()
{
    if(vars == MAX_VARIABLES) {
	SystemError_yy("Too many declared variables.",yylineno_info());
	return(YES);
    }
    return(NO);

}

/* ユーザ指定FORTRAN関数チェック */
void var_userfunc_st()
{
    if(userfuncs == MAX_USERFUNCS ) {
	SystemWarning("Too many User defined Functions");
	return;
    }
    userfunc_name[userfuncs] = PopString();
    register_user_func( userfunc_name[userfuncs] );  /* 多重 */

    userfuncs++;

    return;
}

int how_many_userfuncs()
{
    return(userfuncs);
}

char *get_nth_userfunc_name( n )  /* これは、MakeMakefileで使用している */
     int n;
{
    if(n < 0 || n > userfuncs) {
	SystemAbort("get_nth_userfunc: illegal number");
    }
    return( userfunc_name[n] );
}



/*------ 整数型変数の処理 ------*/
void var_int_st( avsmode )
     int avsmode;
{
    char *name;

    if(avsmode == 1) {  
      avs_mode = 1;  
      avs_var_no[avs_variables]  = vars;
      avs_variables++; 
    }

    name = PopString();         /* 変数名 */

    if(is_max_var()) {          /* 最大定義可能変数内かどうかの検査 */
	FEEL_FreeMemory(name);  /* 獲った分は返す */
	return;
    }

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = INT;  /* 変数種別       */
    var[vars]->avsmode  = avsmode; /* AVS mode */
    var[vars]->initial  =  NO;  /* 初期値は未設定 */
    var[vars]->name     = name; /* 変数名         */
    var[vars]->yylineno = yylineno_info();

    vars++;
    int_vars++;
    return;
}

void var_int_with_value_st(avsmode)  /* 初期値付の場合 */
     int avsmode;
{
    char *name,*value;

    value = PopString();         /* 初期値 */
    name  = PopString();         /* 変数名 */

    if(avsmode == 1) {  
      avs_mode = 1;  
      avs_var_no[avs_variables]  = vars;
      avs_variables++; 
    }

    if(is_max_var()) {           /* 最大定義可能変数内かどうかの検査 */
	FEEL_FreeMemory(value);  /* 獲った分は返す */
	FEEL_FreeMemory(name);   /* 獲った分は返す */
	return;
    }

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = INT;  /* 変数種別       */
    var[vars]->avsmode  = avsmode; /* AVS mode */
    var[vars]->initial  = YES;  /* 初期値は設定   */
    var[vars]->name     = name; /* 変数名         */
    var[vars]->val      = value;/* 初期値         */
    var[vars]->yylineno = yylineno_info();

    vars++;
    int_vars++;
    return;
}

/*------ 倍精度型変数の処理 ------*/
void var_double_st(avsmode)
     int avsmode;
{
    char *name;

    if(avsmode == 1) {  
      avs_mode = 1;  
      avs_var_no[avs_variables]  = vars;
      avs_variables++; 
    }


    name = PopString();         /* 変数名 */

    if(is_max_var()) {          /* 最大定義可能変数内かどうかの検査 */
	FEEL_FreeMemory(name);  /* 獲った分は返す */
	return;
    }

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = DOUBLE;  /* 変数種別       */
    var[vars]->avsmode  = avsmode; /* AVS mode (98/09/03) */
    var[vars]->initial  =  NO;  /* 初期値は未設定 */
    var[vars]->name     = name; /* 変数名         */
    var[vars]->yylineno = yylineno_info();

    vars++;
    double_vars++;
    return;
}

void var_double_with_value_st(avsmode)  /* 初期値付の場合 */
     int avsmode;
{
    char *name;
    char *value;

    value = PopString(); /* 初期値 */
    name  = PopString();          /* 変数名 */

    if(avsmode == 1) {  
      avs_mode = 1;  
      avs_var_no[avs_variables]  = vars;
      avs_variables++; 
    }

    if(is_max_var()) {           /* 最大定義可能変数内かどうかの検査 */
	FEEL_FreeMemory(value);  /* 獲った分は返す */
	FEEL_FreeMemory(name);   /* 獲った分は返す */
	return;
    }

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = DOUBLE;  /* 変数種別       */
    var[vars]->avsmode  = avsmode; /* AVS mode (98/09/03) */
    var[vars]->initial  = YES;  /* 初期値は設定   */
    var[vars]->name     = name; /* 変数名         */
    var[vars]->val      = value;/* 初期値         */
    var[vars]->yylineno = yylineno_info();

    vars++;
    double_vars++;
    return;
}

/*------ 定数型変数の処理 ------*/

void var_const_with_value_st()  /* 初期値付の場合 */
{
    char *name;
    Expression *value;
    Expression *expr_ptr;

    value = get_expr_structure();         /* 初期値 */
    name  = PopString();         /* 変数名 */

    if(is_max_var()) {           /* 最大定義可能変数内かどうかの検査 */
	FEEL_FreeMemory(value);  /* 獲った分は返す */
	FEEL_FreeMemory(name);   /* 獲った分は返す */
	return;
    }

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = CONST;  /* 変数種別       */
    var[vars]->initial  = YES;  /* 初期値は設定   */
    var[vars]->name     = name; /* 変数名         */
    var[vars]->val      = (char *)value;/* 初期値         */
    var[vars]->yylineno = yylineno_info();

    vars++;
    const_vars++;
    return;
}
/*------ material 変数の処理 ------*/
void var_material_st(parameters)
     int parameters;
{
    int      i;
    char    *name;
    double  *value;
    MATERIAL_var *material_ptr;
    
    if(is_max_var()) {           /* 最大定義可能変数内かどうかの検査 */
	for(i=0;i<parameters;i++) {
	    pop();
	}
	pop();
	return;
    }
    
    material_ptr =(MATERIAL_var *)FEEL_GetMemory(sizeof(MATERIAL_var));
    value        =(double *      )FEEL_GetMemory(sizeof(double) * parameters);

    for(i=0;i<parameters;i++) {
	*(value + parameters - i - 1) = PopDouble();
    }

    name = PopString();

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = MATERIAL;  /* 変数種別       */
    var[vars]->initial  = YES;       /* 初期値は設定   */
    var[vars]->name     = name;      /* 変数名         */
    var[vars]->val      = (char *)material_ptr;
    var[vars]->yylineno = yylineno_info();

    material_ptr->materials = parameters;
    material_ptr->val       = value;

    vars++;
    material_vars++;
    
    return;
}

/*------ fem変数の処理 ------*/
/*
   注意:fem文は、複数のregionに異なる構造でまたがる場合の為に、
        まず、fem_type[]に構造体を作成した後に、FEM_var構造体を
        作成し、Var[]構造体に登録する。各fem変数に対して宣言できる
        基底関数は、各メッシュ基本形状に対して一つのみである。
        よって、2次元では２つがmaxとなる。

 */

void var_fem_st()
{
    char *name;
    char *type;
    FEM_type *fem_ptr;

    type = PopString();      /* basis function type */
    name = PopString();      /* variable name       */

    if(is_max_var()) {
	FEEL_FreeMemory(name);
	FEEL_FreeMemory(type);
	return;
    }

    if(fem_types == MAX_FEM_TYPES) { 
	SystemError_yy("Too many fem statements.",yylineno_info());
	FEEL_FreeMemory(name);
	FEEL_FreeMemory(type);
	return;
    }


    fem_ptr = (FEM_type *)FEEL_GetMemory(sizeof(FEM_type));

    fem_ptr->name     = name;
    fem_ptr->yylineno = yylineno_info();

    fem_ptr -> type = type;
    fem_ptr -> domain_name = NULL;   /* 定義領域名はNULL！ */
    fem_ptr -> restrictions = 0;

    fem_type[fem_types] = fem_ptr;
    fem_types++;

    return;
}

/* domain指定付 */
void var_fem_with_dom_st()
{
    char *name;
    char *domain;
    char *type;
    FEM_type *fem_ptr;

    type = PopString();      /* basis function type */
    domain = PopString();    /* domain名            */
    name = PopString();      /* variable name       */

    if(is_max_var()) {
	FEEL_FreeMemory(name);
	FEEL_FreeMemory(domain);
	FEEL_FreeMemory(type);
	return;
    }

    if(fem_types == MAX_FEM_TYPES) { 
	SystemError_yy("Too many fem statements.",yylineno_info());
	FEEL_FreeMemory(name);
	FEEL_FreeMemory(domain);
	FEEL_FreeMemory(type);
	return;
    }


    fem_ptr = (FEM_type *)FEEL_GetMemory(sizeof(FEM_type));

    fem_ptr->name     = name;
    fem_ptr->yylineno = yylineno_info();

    fem_ptr -> type = type;
    fem_ptr -> domain_name = domain;
    fem_ptr -> restrictions = 0;

    fem_type[fem_types] = fem_ptr;
    fem_types++;

    return;
}

/* 拘束条件付き */
void var_fem_with_restrictions_st(parameters)
     int parameters;
{
    int i;
    char *name;
    char *type;
    FEM_type *fem_ptr;
    char **parameter_names;

    if(is_max_var()) {
	for(i=0;i<parameters;i++) pop();
	pop();	pop();
	return;
    }

    if(fem_types == MAX_FEM_TYPES) { 
	SystemError_yy("Too many fem statements.",yylineno_info());
	for(i=0;i<parameters;i++) pop();
	pop();	pop();
	return;
    }
    
    parameter_names = (char **)FEEL_GetMemory(sizeof(char *) * parameters);

    for(i=0;i<parameters;i++ ) {  /* 拘束変数名の取得、順序に注意 */
	*(parameter_names + parameters - 1 - i) = PopString(); 
    }

    type = PopString();      /* basis function type */
    name = PopString();      /* variable name       */

    fem_ptr = (FEM_type *)FEEL_GetMemory(sizeof(FEM_type));

    fem_ptr  -> name     = name;
    fem_ptr  -> yylineno = yylineno_info();

    fem_ptr -> type = type;
    fem_ptr -> domain_name = NULL;             /* 領域名はNULL */
    fem_ptr -> restrictions = parameters;
    fem_ptr -> restrict_var = parameter_names;

    fem_type[fem_types] = fem_ptr;
    fem_types++;

    return;
}

/* 拘束条件およびdomain指定付き */
void var_fem_with_restrictions_and_dom_st(parameters)
     int parameters;
{
    int i;
    char *name;
    char *type;
    char *domain;
    FEM_type *fem_ptr;
    char **parameter_names;

    if(is_max_var()) {
	for(i=0;i<parameters;i++) pop();
	pop();	pop(); pop();
	return;
    }

    if(fem_types == MAX_FEM_TYPES) { 
	SystemError_yy("Too many fem statements.",yylineno_info());
	for(i=0;i<parameters;i++) pop();
	pop();	pop(); pop();
	return;
    }
    
    parameter_names = (char **)FEEL_GetMemory(sizeof(char *) * parameters);

    for(i=0;i<parameters;i++ ) {  /* 拘束変数名の取得、順序に注意 */
	*(parameter_names + parameters - 1 - i) = PopString(); 
    }

    type = PopString();      /* basis function type */
    domain = PopString();    /* domain名            */
    name = PopString();      /* variable name       */


    fem_ptr = (FEM_type *)FEEL_GetMemory(sizeof(FEM_type));

    fem_ptr  -> name     = name;
    fem_ptr  -> yylineno = yylineno_info();

    fem_ptr -> type = type;
    fem_ptr -> domain_name = domain;
    fem_ptr -> restrictions = parameters;
    fem_ptr -> restrict_var = parameter_names;

    fem_type[fem_types] = fem_ptr;
    fem_types++;

    return;
}


/* ewise変数の処理 */
/* 注意:ewise文は、feel fort77のCOMMONブロックサイズの関係上
        構文解析のMAX_VARIABLESの制限以外に、MAX_EWISEのチェック
        も行わなければいけない。

   注意:ewise文は、複数のregionに異なる構造でまたがる場合の為に、
        まず、ewise_type[]に構造体を作成した後に、EWISE_var構造体を
        作成し、Var[]構造体に登録する。
 */
static int pushed_nums;  /* 座標の指定に要した 'num'の数  
                            2ならば分数ということ        */
static int cordinates = 0;  /* 注意：この変数は使用後は０に初期化すること */
static double push_r[MAX_NODES_FOR_EWISE];
static double push_s[MAX_NODES_FOR_EWISE];
static double push_t[MAX_NODES_FOR_EWISE];


double myatof( s )
     char *s;
{
    double x;
    if(sscanf(s,"%lf",&x)!=1) {
	SystemAbort("myatof error");
    }

    return(x);
}

void push_ewise_cordinate_dat( n )
     int n;
{
    pushed_nums = n;
}

void push_ewise_cordinate_inc()
{
    cordinates++;
}

void push_ewise_cordinate_r()
{

    if(cordinates == MAX_NODES_FOR_EWISE) {
	SystemWarning_yy("Too many ewise points per element.",yylineno_info());
	return;
    }
    if(pushed_nums == 1) {
	push_r[cordinates]=(double)myatof(pop());/* pop() の使用方法に注意 */
    }
    else {
	push_r[cordinates] = (double)myatof(pop());
	push_r[cordinates] = (double)myatof(pop()) / push_r[cordinates];
    }
    return;
}

void push_ewise_cordinate_s()
{

    if(cordinates == MAX_NODES_FOR_EWISE) {
	return;
    }
    if(pushed_nums == 1) {
	push_s[cordinates]=(double)myatof(pop());/* pop() の使用方法に注意 */
    }
    else {
	push_s[cordinates] = (double)myatof(pop());
	push_s[cordinates] = (double)myatof(pop()) / push_s[cordinates];
    }
    return;
}

void push_ewise_cordinate_t()
{

    if(cordinates == MAX_NODES_FOR_EWISE) {
	return;
    }
    if(pushed_nums == 1) {
	push_t[cordinates]=(double)myatof(pop());/* pop() の使用方法に注意 */
    }
    else {
	push_t[cordinates] = (double)myatof(pop());
	push_t[cordinates] = (double)myatof(pop()) / push_t[cordinates];
    }
    return;
}

/* ewise文処理の本体 */
void var_ewise_st()
{
    int i;
    char *name;

    EWISE_type *ewise_ptr;

    if(is_max_var()) {
	pop();    /* domain名            */
	pop();    /* ewise変数の名前の分 */
	return;
    }
    
    if(ewise_types == MAX_EWISE_TYPES) { 
	SystemError_yy("Too many ewise statements.",yylineno_info());
	pop();      /* domain名 */
	pop();      /* ewise変数の名前の分 */
	return;
    }

    ewise_ptr = (EWISE_type *)FEEL_GetMemory(sizeof(EWISE_type));

    ewise_ptr -> quadrature = NULL;

    ewise_ptr -> domain_name = PopString();  /* ewise変数定義domain名 */

    name = PopString();   /* 変数名       */

    ewise_ptr->name     = name;
    ewise_ptr->points   = 0;              /* 指定点は０としておく */
    ewise_ptr->yylineno = yylineno_info();

    ewise_type[ewise_types] = ewise_ptr;  /* ewiseに関してスタックに積むだけ */

    ewise_types++;

    return;
}

void var_ewise_with_quadrature_st()
{
    int i;
    char *name;
    char *quadrature_name;

    EWISE_type *ewise_ptr;

    if(is_max_var()) {
	pop();        /* domain名の分 */
	pop(); pop(); /* ewise変数の名前、数値積分法名称の分 */
	return;
    }
    
    if(ewise_types == MAX_EWISE_TYPES) { 
	SystemError_yy("Too many ewise statements.",yylineno_info());
	pop();
	pop(); pop();
	return;
    }


    ewise_ptr = (EWISE_type *)FEEL_GetMemory(sizeof(EWISE_type));

    ewise_ptr -> quadrature = PopString();  /* 数値積分名称 */
    ewise_ptr -> domain_name = PopString(); /* domain名 */

    name = PopString();   /* 変数名       */

    ewise_ptr->name     = name;
    ewise_ptr->points   = 0;              /* 指定点は０としておく */
    ewise_ptr->yylineno = yylineno_info();

    ewise_type[ewise_types] = ewise_ptr;  /* ewiseに関してスタックに積むだけ */

    ewise_types++;

    return;
}

/* 座標が陽に指定される ewise 変数 */
void var_ewise_with_cordinates_st()
{
    int i;
    char *name;
    char *type;
    EWISE_type *ewise_ptr;


    if(is_max_var()) {
	pop();
	pop();
	return;
    }

    if(ewise_types == MAX_EWISE_TYPES) { 
	SystemError_yy("Too many ewise statements.",yylineno_info());
	pop();
	pop();
	return;
    }

    ewise_ptr = (EWISE_type *)FEEL_GetMemory(sizeof(EWISE_type));

    ewise_ptr->domain_name = PopString();  /* domain名 */
    
    name = PopString();   /* 変数名       */

    ewise_ptr->name     = name;
    ewise_ptr -> points  = cordinates;     /* エラーチェック部で行う      */

    ewise_type[ewise_types] = ewise_ptr;  /* ewiseに関してスタックに積むだけ */

    for(i=0;i<cordinates;i++) {
	ewise_ptr->r[i] = push_r[i];
	ewise_ptr->s[i] = push_s[i];
	ewise_ptr->t[i] = push_t[i];
    }
    ewise_ptr -> quadrature = NULL;
    ewise_ptr->yylineno = yylineno_info();

    cordinates = 0;          /* cordinates のリセット */

    ewise_type[ewise_types] = ewise_ptr;  /* 一次記憶用 */

    ewise_types++;

    return;
}


/*----- type2 関数群 -----*/
int how_many_vars()  
{
    return(vars);
}

int how_many_int_vars()
{
    return(int_vars);
}
int how_many_double_vars()
{
    return(double_vars);
}
int how_many_const_vars()
{
    return(const_vars);
}
int how_many_fem_vars()
{
    return(fem_vars);
}
int how_many_ewise_vars()
{
    return(ewise_vars);
}
int how_many_material_vars()
{
    return(material_vars);
}
int how_many_ewise_types()
{
    return(ewise_types);
}

int how_many_fem_types()
{
    return(fem_types);
}

/*-----------------------------------------------*/
Var *get_nth_var_ptr( n )
     int n;
{
    if(n < 0 || n >= vars) {
	SystemAbort("Illegal var number(get_nth_var_ptr)");
    }
    return(var[n]);
}



EWISE_type *get_nth_ewise_type_ptr(n)
     int n;
{
    if(n >= ewise_types || n < 0) {
	SystemAbort("get_nth_ewise_type_ptr error.\n");
    }
    return(ewise_type[n]);
}

FEM_type *get_nth_fem_type_ptr(n)
     int n;
{
    if(n >= fem_types || n < 0) {
	SystemAbort("get_nth_fem_type_ptr error.\n");
    }
    return(fem_type[n]);
}

Var *get_nth_int_ptr(n)  /* n starts 0 */
     int n;
{
    int i,counter;
    if(n > int_vars) {
	SystemAbort("get_nth_int_ptr error.");
    }
    counter = 0;
    for(i=0;i<vars;i++) {
	if(var[i]->type == INT) counter++;
	if(counter-1 == n) return(var[i]);
    }
    SystemAbort("get_nth_int_ptr error.");
}
Var *get_nth_double_ptr(n)  /* n starts 0 */
     int n;
{
    int i,counter;
    if(n > double_vars) {
	SystemAbort("get_nth_double_ptr error.");
    }
    counter = 0;
    for(i=0;i<vars;i++) {
	if(var[i]->type == DOUBLE) counter++;
	if(counter-1 == n) return(var[i]);
    }
    SystemAbort("get_nth_double_ptr error.");
}
Var *get_nth_const_ptr(n)  /* n starts 0 */
     int n;
{
    int i,counter;
    if(n > const_vars) {
	SystemAbort("get_nth_const_ptr error.");
    }
    counter = 0;
    for(i=0;i<vars;i++) {
	if(var[i]->type == CONST) counter++;
	if(counter-1 == n) return(var[i]);
    }
    SystemAbort("get_nth_const_ptr error.");
}
Var *get_nth_fem_ptr(n)  /* n starts 0 */
     int n;
{
    int i,counter;
    if(n > fem_vars) {
	SystemAbort("get_nth_fem_ptr error.");
    }
    counter = 0;
    for(i=0;i<vars;i++) {
	if(var[i]->type == FEM) counter++;
	if(counter-1 == n) return(var[i]);
    }
    SystemAbort("get_nth_fem_ptr error.");
}

Var *get_nth_ewise_ptr(n)  /* n starts 0 */
     int n;
{
    int i,counter;
    if(n > ewise_vars) {
	SystemAbort("get_nth_ewise_ptr error.");
    }
    counter = 0;
    for(i=0;i<vars;i++) {
	if(var[i]->type == EWISE) counter++;
	if(counter-1 == n) return(var[i]);
    }
    SystemAbort("get_nth_ewise_ptr error.");
}

Var *get_nth_material_ptr(n)  /* n starts 0 */
     int n;
{
    int i,counter;
    if(n > material_vars) {
	SystemAbort("get_nth_material_ptr error.");
    }
    counter = 0;
    for(i=0;i<vars;i++) {
	if(var[i]->type == MATERIAL) counter++;
	if(counter-1 == n) return(var[i]);
    }
    SystemAbort("get_nth_material_ptr error.");
}
/*-----------------------------------------------*/
int get_var_kind( name )
     char *name;
{
    int i;
    
    if(is_feel_system_var( name )) {    /* ../check/check_var.cの関数
					   空間変数を意味する
					   (小文字の x,y,z )          */
	return( SYSTEM_VAR );
    }

    if(is_feel_test_var( name )) {
	return( TEST_VAR );
    }

    for(i=0;i<vars;i++) {
	if(streq(var[i]->name,name)) {
	    return(var[i]->type);
	}
    }

    return( NO );
}


store_fem_type_2_var( name , fem_type_ptr )
     char *name;
     FEM_type *fem_type_ptr;  
{
    FEM_var *fem_ptr;

    fem_ptr = (FEM_var *)FEEL_GetMemory(sizeof(FEM_var));

    fem_ptr->name = name; 
    fem_ptr->basis_types = 1;   /* 初期化 */
    fem_ptr->fem_type_ptr[0] = fem_type_ptr;

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = FEM;       /* 変数種別       */
    var[vars]->initial  = NO;        /* 初期値は設定   */
    var[vars]->name     = name;      /* 変数名         */
    var[vars]->val      = (char *)fem_ptr;

    vars++;
    fem_vars++;
    
    return;
}

Var *get_var_ptr_by_name( name ) /* 1998/12/17  for modulef */
     char *name;
{
    int i;

    for(i=0;i<vars;i++) {
      if(streq(var[i]->name,name)) return(var[i]);
    }

    SystemAbort("Cannot find specified var pointer(this is extension for modulef)");
}


int get_fem_var_no_byname( name )
     char *name;
{
    int i;
    int count;

    count = 0;
    for(i=0;i<vars;i++) {
	
	if(var[i]->type == FEM) {
	    
	    if(streq(var[i]->name,name)) return(count);

	    count++;

	}
    }

    return(NOTHING);
}

int get_ewise_var_no_byname( name )
     char *name;
{
    int i;
    int count;

    count = 0;
    for(i=0;i<vars;i++) {
	
	if(var[i]->type == EWISE) {
	    
	    if(streq(var[i]->name,name)) return(count);

	    count++;

	}
    }

    return(NOTHING);
}



FEM_var *get_fem_ptr_by_name( name )
     char *name;
{
    int i;

    for(i=0;i<vars;i++) {

	if(var[i]->type != FEM) continue;
	
	if(streq(var[i]->name,name)) return((FEM_var *)( var[i]->val) );
    }
    
    return(NULL);
}

EWISE_var *get_ewise_ptr_by_name( name )
     char *name;
{
    int i;

    for(i=0;i<vars;i++) {

	if(var[i]->type != EWISE) continue;
	
	if(streq(var[i]->name,name)) return((EWISE_var *) (var[i]->val ));
    }
    
    return(NULL);
}


/* 指定されたdomain名を定義域に持つfem変数のポインタを返す。
   指定されたfem変数名が存在し、なおかつfem変数が指定された
   domain名について個別に対応していない場合は、指定したdomain_name
   に対応するetypeをもつものを返す。
 */

FEM_type *get_fem_type_ptr_by_2name( var_name , domain_name)
     char *var_name;
     char *domain_name;
{
    int i,types;
    int etype;
    FEM_var  *fem_ptr;
    FEM_type *fem_type_ptr;

    fem_ptr = get_fem_ptr_by_name( var_name );
    if(fem_ptr == NULL) return(NULL);

    types = fem_ptr->basis_types;
    /* まず、domainとして陽に定義されている物と適合するか調べる */
    for(i=0;i<types;i++) {
	fem_type_ptr = fem_ptr->fem_type_ptr[i];
	if(fem_type_ptr->domain_name == NULL) continue;
	if(streq(fem_type_ptr->domain_name,domain_name)) {
	    return(fem_type_ptr);
	}
    }

    etype = get_domain_etype_by_name( domain_name );

    /* 次にdomain_nameがNULLかつ適合する最初のものを返す */
    for(i=0;i<types;i++) {
	fem_type_ptr = fem_ptr->fem_type_ptr[i];
	if(fem_type_ptr->domain_name != NULL) continue;
	
	if(fem_type_ptr->etype == etype) {
	    return(fem_type_ptr);
	}
    }
    return(NULL);
}

/* 指定されたewise変数が、単一のdomainでのみ指定されたものと
   仮定して、(プレα版)EWISE_type構造体を返す                */
EWISE_type *get_ewise_type_ptr_by_name( var_name )
     char *var_name;
{
    EWISE_var  *ewise_var_ptr;
    EWISE_type *ewise_type_ptr;

    ewise_var_ptr = get_ewise_ptr_by_name( var_name );
    if(ewise_var_ptr == NULL) {
	return(NULL);   /* error */
    }

    if(ewise_var_ptr -> ewise_types != 1) {
	SystemWarning_s("ewise変数 %s はマルチdomain宣言(未対応)",var_name);
	return(NULL);
    }
    
    return(ewise_var_ptr ->ewise_type_ptr[0]);
}




/* 指定されたdomain名を定義域に持つfem変数のポインタを返す。
   指定されたfem変数名が存在し、なおかつfem変数が指定された
   domain名について個別に対応していない場合は、指定したdomain_name
   に対応するetypeをもつものを返す。
 */

EWISE_type *get_ewise_type_ptr_by_2name( var_name , domain_name)
     char *var_name;
     char *domain_name;
{
    int i,types;
    int etype;
    EWISE_var  *ewise_ptr;
    EWISE_type *ewise_type_ptr;

    ewise_ptr = get_ewise_ptr_by_name( var_name );
    if(ewise_ptr == NULL) return(NULL);

    types = ewise_ptr->ewise_types;

    for(i=0;i<types;i++) {
	ewise_type_ptr = ewise_ptr->ewise_type_ptr[i];

	if(streq(ewise_type_ptr->domain_name,domain_name)) {
	    return(ewise_type_ptr);
	}
    }

    return(NULL);

}




store_fem_type_2_var_add( name , fem_type_ptr )
     char *name;
     FEM_type *fem_type_ptr;  
{
    FEM_var *fem_ptr;

    fem_ptr  = get_fem_ptr_by_name( name );

    if(fem_ptr == NULL) {
	SystemAbort("store_fem_type_2_var_add: Internal error.\n");
    }

    fem_ptr->fem_type_ptr[fem_ptr->basis_types] = fem_type_ptr;

    fem_ptr->basis_types =    fem_ptr->basis_types  + 1 ;

    return;
}



store_ewise_type_2_var( name , ewise_type_ptr )
     char *name;
     EWISE_type *ewise_type_ptr;  /* (EWISE_var *)だけれども */
{
    EWISE_var *ewise_ptr;

    ewise_ptr = (EWISE_var *)FEEL_GetMemory(sizeof(EWISE_var));

    ewise_ptr->name = name; 
    ewise_ptr->ewise_types = 1;   /* 初期化 */
    ewise_ptr->ewise_type_ptr[0] = ewise_type_ptr;

    var[vars] = (Var *)FEEL_GetMemory(sizeof(Var));
    var[vars]->type     = EWISE;       /* 変数種別       */
    var[vars]->initial  = NO;          /* 初期値は設定   */
    var[vars]->name     = name;        /* 変数名         */
    var[vars]->val      = (char *)ewise_ptr;

    vars++;
    ewise_vars++;
    
    return;
}



store_ewise_type_2_var_add( name , ewise_type_ptr )
     char *name;
     EWISE_type *ewise_type_ptr;  
{
    EWISE_var *ewise_ptr;

    ewise_ptr  = get_ewise_ptr_by_name( name );

    if(ewise_ptr == NULL) {
	SystemAbort("store_ewise_type_2_var_add: Internal error.\n");
    }

    ewise_ptr->ewise_type_ptr[ewise_ptr->ewise_types] = ewise_type_ptr;

    ewise_ptr->ewise_types =    ewise_ptr->ewise_types  + 1 ;

    return;
}


int how_many_avs_variables()
{
  return(avs_variables);
}

void put_nth_avs_feel_name_fp(fp,n)
     FILE *fp;
     int    n;
{
  int var_no;

  if(n >= avs_variables || n <0) {
    SystemAbort("Illegal number for put_nth_avs_feel_name_fp");
  }

  var_no = avs_var_no[n];
  fprintf(fp,SCALAR_VAR_NAME77,var[var_no]->name);

  return;
}


void put_nth_avs_initial_val_fp(fp,n)
     FILE *fp;
     int    n;
{
  int var_no;

  if(n >= avs_variables || n <0) {
    SystemAbort("Illegal number for put_nth_avs_initial_val_fp");
  }

  var_no = avs_var_no[n];
  if(var[var_no]->initial == NO) {  /* No initial value */
    fprintf(fp,"0");
  }
  else {
    fprintf(fp,"%s",var[var_no]->val);
  }
  return;
}


void put_nth_avs_real_name_fp(fp,n)
     FILE *fp;
     int    n;
{
  int var_no;

  if(n >= avs_variables || n <0) {
    SystemAbort("Illegal number for put_nth_avs_feel_name_fp");
  }

  var_no = avs_var_no[n];
  fprintf(fp,"%s",var[var_no]->name);
  return;
}

Var *get_nth_avs_feel_var_ptr(n)
     int n;
{
  int var_no;

  if(n >= avs_variables || n <0) {
    SystemAbort("Illegal number for put_nth_avs_feel_var_type");
  }
  var_no = avs_var_no[n];
  return(var[var_no]);
}


int get_nth_avs_feel_var_type(n)
     int n;
{
  int var_no;

  if(n >= avs_variables || n <0) {
    SystemAbort("Illegal number for put_nth_avs_feel_var_type");
  }
  var_no = avs_var_no[n];
  return(var[var_no]->type);
}
  
void put_nth_avs_feel_declare_fp(fp,n)
     FILE *fp;
     int    n;
{
  int var_no;

  if(n >= avs_variables || n <0) {
    SystemAbort("Illegal number for put_nth_avs_feel_name_fp");
  }

  var_no = avs_var_no[n];
  if(var[var_no]->type == INT ) {
    fprintf(fp,"      integer ");
  }
  else {
    fprintf(fp,"      real*8  ");
  }
  fprintf(fp,SCALAR_VAR_NAME77,var[var_no]->name);
  fprintf(fp,"\n");

  return;
}
