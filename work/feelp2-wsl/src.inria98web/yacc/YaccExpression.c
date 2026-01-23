/*
  FILE       YaccExpression.c
  Made             1991/12/26
  Modified         1992/02/14

  GREAT Modified   1992/02/24           with some LISP program
  Modified         1992/08/10

  Modified         1993/05/25           配列表現を可能にした

  Version    1.1

  Purpose    This program makes prefix form of expression.

*/

#include <stdio.h>
#include <stdlib.h>  /* modernize 2026/01/21 */
#include <string.h>  /* modernize 2026/01/21 */
#include "../system/system.h"
#include "YaccExpression.h"

#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
int streq(char *,char *);



/* ---------- forward declarations (modernize 2026/01/xx) ---------- */

/* local helper */
static int identifier_no(char *name);
static int function_no(char *name);

/* debug routines */
static void show_expression_string(char *s);
static void show_list_string(int lst, char *s, int *str_ptr);

/* cell/list primitives (defined in this file) */
static int  get_new_cell(void);
static void cons(int new_lst, int car_cell, int old_lst);
static void put_atom(int atom, char *a);
static void make_2_op(int new_cell, int op_cell, int left_cell, int right_cell);

/* expression stack */
static int  exp_pop(void);
static void exp_push(int lst);

/* public-ish entry points used by yacc actions (keep non-static if referenced elsewhere) */
void cell_init(void);
void exp_atom_push(char *a);
void exp_func_push(char *a);
void exp_array_push(char *a);
void exp_pl_push(void);
void exp_mi_push(void);
void exp_mu_push(void);
void exp_minus_push(void);
void exp_di_push(void);

void show_expression(void);
void show_list(int lst);
void show_expression_fp(FILE *fp);
void show_list_fp(int lst, FILE *fp);

char *get_expression_string(void);
Expression *get_expr_structure(void);

void push_identifier_and_push(void);
char **get_exp_identifiers(int *symbols);

void push_function_and_push(void);
char **get_exp_functions(int *symbols);

/* external functions this file calls (declared somewhere else, but ensure prototypes exist) */
int streq(char *a, char *b);
void *FEEL_GetMemory(int size);
void SystemAbort(char *msg);
char *PopString(void);
char *MakeStringCopy(char *s);

/* ----------------------------------------------------------------- */


/*-----EXPRESSION STACK DEFINITION-----*/
#define MAX_STACK    2000

/*-----CELL DEFINITION-----*/
#define  MAX_CELL  9192 

#define  FREE      0   /* cell type */
#define  ATOM      1   /* cell type */
#define  LIST      2   /* cell type */

#define  NORMAL    0   /* NORMAL LIST     */
#define  FUNCTION  1   /* function symbol */
#define  ARRAY     2   /* 配列リスト      */

#define  NIL    -999   /* NULL POINTER */
#define  LAST     -1   /* cell empty flag */

#define  MAX_EXPRESSION_STRING_SIZE   2048
#define  MAX_EXPRESSION_IDENTIFIER     256 /* 式に現れる変数シンボルを記憶
					      する領域の大きさ             */
#define  MAX_EXPRESSION_FUNCTION       256 /* 式に現れる関数シンボルを記憶
					      する領域の大きさ             */

void put_atom(int atom, char *a);  /* modernize 2026/01/21 */


struct CELL {
    char        type;   /* type */
    char        symbol; /* function symbol? */
    char        *val;   /* Value of CELL */
    int         eptr;   /* Empty cell pointer */
    int         car;
    int         cdr;
};

static struct CELL cell[MAX_CELL];
static int    empty_cell_ptr  = 0;
static int    remain_cell     = MAX_CELL;

static char *identifier_name[MAX_EXPRESSION_IDENTIFIER]; /* 変数名記憶用 */
static int   identifier_list[MAX_EXPRESSION_IDENTIFIER]; /* 各expression用 */
static int   identifiers      = 0;
static int   current_expression_identifiers = 0;

static char *function_name[MAX_EXPRESSION_FUNCTION]; /* 変数名記憶用 */
static int   function_list[MAX_EXPRESSION_FUNCTION]; /* 各expression用 */
static int   functions      = 0;
static int   current_expression_functions = 0;

/* constant cells */
static int pl_cell;
static int mi_cell;
static int mu_cell;
static int di_cell;
static int minus_one_cell;
static int nil_cell;



/*-----EXPRESSION STACK DEFINITION-----*/
static int           exp_pos = 0;
static int cell_stack[MAX_STACK];


/*  CELL INITIALIZE  */
void cell_init()
{
    int i;
    for(i=0;i<MAX_CELL;i++) {
	cell[i].type = FREE;
	cell[i].symbol = NORMAL;
	cell[i].eptr = i+1;
	cell[i].val  = NULL;
	cell[i].car  = NIL;
	cell[i].cdr  = NIL;
    }
    pl_cell = get_new_cell();
    mi_cell = get_new_cell();
    mu_cell = get_new_cell();
    di_cell = get_new_cell();
    minus_one_cell = get_new_cell();
    nil_cell = get_new_cell();            /* NIL */

    put_atom(pl_cell,"+");
    cell[pl_cell].symbol = FUNCTION;
    put_atom(mi_cell,"-");
    cell[mi_cell].symbol = FUNCTION;
    put_atom(mu_cell,"*");
    cell[mu_cell].symbol = FUNCTION;
    put_atom(di_cell,"/");
    cell[di_cell].symbol = FUNCTION;

    put_atom(minus_one_cell,"-1");
    cell[minus_one_cell].symbol =NORMAL ;
    
    cell[nil_cell].cdr = NIL;
    cell[nil_cell].car = NIL;
    cell[nil_cell].type = ATOM;
    cell[nil_cell].val  = NULL;

    return;
}

/*----- LIST PROCESSING -----*/
int get_new_cell()
{
    int new_cell_no;
    if(remain_cell == 0 ) {
	SystemAbort("No more empty CELL.");
    }
    remain_cell--;
    new_cell_no = empty_cell_ptr;
    empty_cell_ptr = cell[empty_cell_ptr].eptr;
    return(new_cell_no);
}

void cons(new_lst,car_cell,old_lst)
int new_lst;
int car_cell;
int old_lst;
{
    cell[new_lst].type = LIST;
    cell[new_lst].car  = car_cell;
    cell[new_lst].cdr  = old_lst;
  
    return;
}

void put_atom(atom,a)
int atom;
char *a;
{
    cell[atom].type = ATOM;
    cell[atom].val  = (char *)malloc(strlen(a)+1);
    strcpy(cell[atom].val , a);

    return;
}

/*  EXPRESSION STACK PROCEDURES */    
int exp_pop() 
{
    if(exp_pos == 0) {
	SystemAbort("POP_EXP: stack empty");
    }
    exp_pos--;
    return( cell_stack[exp_pos]);
}

void exp_push(lst)
int lst;
{
    if(exp_pos == MAX_STACK) {
	SystemAbort("NO space is left for expression stack.");
    }
    cell_stack[exp_pos] = lst;
    exp_pos++;

    return;
}




void exp_atom_push( a )
char *a;
{
    int atom_cell;

    atom_cell = get_new_cell();

    put_atom(atom_cell,a);

    exp_push(atom_cell);    /* PUSH CELL TYPE is ATOM */

    return;
}

void exp_func_push( a )
     char *a;
{
    int parm_cell;
    int new_parm_cell;
    int atom_cell;
    int new_list_cell;

    parm_cell     = exp_pop();   /* the parameter of the function */
    if(cell[parm_cell].type == ATOM || cell[cell[parm_cell].car].symbol == FUNCTION) {
	new_parm_cell = get_new_cell();
	cell[new_parm_cell].type = LIST;
	cell[new_parm_cell].car  = parm_cell;
	parm_cell = new_parm_cell;             /* little danger */
    }	
	
    atom_cell     = get_new_cell();
    new_list_cell = get_new_cell();

    put_atom(atom_cell,a);
    cell[atom_cell].symbol = FUNCTION;

    cons(new_list_cell,atom_cell,parm_cell); 

    exp_push(new_list_cell);

    return;
}

void exp_array_push( a )    /* 配列の場合のpush */
     char *a;
{
    int parm_cell;
    int new_parm_cell;
    int atom_cell;
    int new_list_cell;

    parm_cell     = exp_pop();   /* the parameter of the function */
    if(cell[parm_cell].type == ATOM || cell[cell[parm_cell].car].symbol == FUNCTION) {
	new_parm_cell = get_new_cell();
	cell[new_parm_cell].type = LIST;
	cell[new_parm_cell].car  = parm_cell;
	parm_cell = new_parm_cell;             /* little danger */
    }	
	
    atom_cell     = get_new_cell();
    new_list_cell = get_new_cell();

    put_atom(atom_cell,a);
    cell[atom_cell].symbol = ARRAY;

    cons(new_list_cell,atom_cell,parm_cell); 

    exp_push(new_list_cell);

    return;
}
    
void exp_pl_push()
{
    int left_cell;
    int right_cell;
    int new_cell;

    right_cell = exp_pop();
    left_cell  = exp_pop();
    
    new_cell = get_new_cell();

    make_2_op(new_cell,pl_cell,left_cell,right_cell);

    exp_push(new_cell);
 
    return;
}

void exp_mi_push()
{
    int left_cell;
    int right_cell;
    int new_cell;

    right_cell = exp_pop();
    left_cell  = exp_pop();
    
    new_cell = get_new_cell();

    make_2_op(new_cell,mi_cell,left_cell,right_cell);
    
    exp_push(new_cell);
 
    return;
}

void exp_mu_push()
{
    int left_cell;
    int right_cell;
    int new_cell;

    right_cell = exp_pop();
    left_cell  = exp_pop();
    
    new_cell = get_new_cell();

    make_2_op(new_cell,mu_cell,left_cell,right_cell);

    exp_push(new_cell);
 
    return;
}

void exp_minus_push()     /* 単項演算子の処理 */
{
    int left_cell;
    int right_cell;
    int new_cell;

    right_cell = minus_one_cell;     /* -1 セル */
    left_cell  = exp_pop();

    new_cell = get_new_cell();
    make_2_op(new_cell,mu_cell,left_cell,right_cell);
    exp_push(new_cell);

    return;
}


void exp_di_push()
{
    int left_cell;
    int right_cell;
    int new_cell;

    right_cell = exp_pop();
    left_cell  = exp_pop();
    
    new_cell = get_new_cell();

    make_2_op(new_cell,di_cell,left_cell,right_cell);

    exp_push(new_cell);
 
    return;
}


make_2_op(new_cell,op_cell,left_cell,right_cell)
     int new_cell;
     int op_cell;
     int left_cell;
     int right_cell;
{
    int new_left_cell;
    int new_right_cell;

    cell[new_cell].type = LIST;
    cell[new_cell].car  = op_cell;

    new_left_cell = get_new_cell();
    new_right_cell = get_new_cell();

    cell[new_cell].cdr  = new_left_cell;
    cell[new_left_cell].type = LIST;
    cell[new_left_cell].car  = left_cell;
    cell[new_left_cell].cdr  = new_right_cell;
    
    cell[new_right_cell].type = LIST;
    cell[new_right_cell].car  = right_cell;
    cell[new_right_cell].cdr  = NIL;

    return;
}

/*** PRINT a LIST (This program pops)***/

show_expression()
{
    int exp_cell;

    exp_cell = exp_pop();
    exp_push(exp_cell);

    show_list(exp_cell);

    return;
}


show_list(lst)
     int lst;
{
    int ptr;

    if(cell[lst].type == ATOM ) {
	printf(" %s ",cell[lst].val);
	return;
    }
    
    if(cell[lst].type != LIST ) {
	printf("\nlst=%d  type = %d  val=[%s]\n",lst,cell[lst].type,cell[lst].val);
	SystemAbort("show_list: NOT LIST NOR ATOM CELL!");
    }

    printf("(");
    show_list(cell[lst].car);

    ptr = cell[lst].cdr;
    
    while(ptr != NIL ) {
	show_list(cell[ptr].car);
	ptr = cell[ptr].cdr;
    }

    printf(")");
    return;
}
    
/*-----FOR FILE OUT----------------------------------*/
show_expression_fp(fp)
FILE *fp;
{
    int exp_cell;

    exp_cell = exp_pop();
    exp_push(exp_cell);

    show_list_fp(exp_cell,fp);

    return;
}


show_list_fp(lst,fp)
     int lst;
     FILE *fp;
{
    int ptr;

    if(cell[lst].type == ATOM ) {
	fprintf(fp," %s ",cell[lst].val);
	return;
    }
    
    if(cell[lst].type != LIST ) {
	fprintf(stderr,"\nlst=%d  type = %d  val=[%s]\n",lst,cell[lst].type,cell[lst].val);
	SystemAbort("show_list_fp: NOT LIST NOR ATOM CELL!");
    }

    fprintf(fp,"(");
    show_list_fp(cell[lst].car,fp);

    ptr = cell[lst].cdr;
    
    while(ptr != NIL ) {
	show_list_fp(cell[ptr].car,fp);
	ptr = cell[ptr].cdr;
    }

    fprintf(fp,")");
    return;
}

/*-LIST string out--------------------------------------------------*/
char *get_expression_string()
{
    char buf[MAX_EXPRESSION_STRING_SIZE];
    char *MakeStringCopy();

    show_expression_string(buf);

    return(MakeStringCopy( buf ));
}


show_expression_string(s)
char *s;
{
    int exp_cell;
    int str_ptr;

    str_ptr = 0;

    exp_cell = exp_pop();
    exp_push(exp_cell);

    show_list_string(exp_cell,s,&str_ptr);

    return;
}


show_list_string(lst,s,str_ptr)
     int lst;
     char *s;
     int *str_ptr;
{
    int ptr;

    if(cell[lst].type == ATOM ) {
	sprintf(s+*str_ptr," %s ",cell[lst].val);
	*str_ptr += (strlen(cell[lst].val)+2);
	return;
    }
    
    if(cell[lst].type != LIST ) {
	fprintf(stderr,"\nlst=%d  type = %d  val=[%s]\n",lst,cell[lst].type,cell[lst].val);
	SystemAbort("show_list_string: NOT LIST NOR ATOM CELL!");
    }

    sprintf(s+*str_ptr,"(");  *str_ptr += 1;

    show_list_string(cell[lst].car,s,str_ptr);

    ptr = cell[lst].cdr;
    
    while(ptr != NIL ) {
	show_list_string(cell[ptr].car,s,str_ptr);
	ptr = cell[ptr].cdr;
    }

    sprintf(s+*str_ptr,")");  *str_ptr += 1;
    return;
}

/*--------LISP BASIC FUNCTIONS--------*/
int colisp_length( lst )
     int lst;
{
    int length,ptr;

    if(cell[lst].type != LIST) {
	SystemAbort("LISP FUNCTION colisp_length  NOT LIST ");
    }

    ptr = lst;
    length = 1;

    while(cell[ptr].cdr != NIL) {
	length++;
	ptr = cell[ptr].cdr;
    }

    return(length);
}


/***********************************************************************/
/* LISP PROGRAM WRITTEN IN C                                           */
/***********************************************************************/
/*
int colisp_pre_to_inf ( lst )
     int lst ;
{

    int list_len;
    
    if(lst == NIL || cell[lst].car == NIL) {
	return(nil_cell) ;
    }

    if(cell[lst].type == ATOM) {
	return( lst ) ;
    }
}
    
*/



push_identifier_and_push() /* expressionに現れる変数名を格納する為の関数 */
{
    int    i;
    int   no;
    char *cp;
    
    cp = PopString();
    push(cp);
    no = identifier_no( cp );

    for(i=0;i<current_expression_identifiers;i++) {
	if(no == identifier_list[i]) return;
    }

    if(current_expression_identifiers == MAX_EXPRESSION_IDENTIFIER) {
	SystemAbort("Too many identifiers in expression.[p_iden_and_pu()]\n");
    }

    identifier_list[current_expression_identifiers] = no;
    current_expression_identifiers++;

    return;
}

char **get_exp_identifiers( symbols )
     int *symbols;
{
    int i;
    char **identifier_stack;

    identifier_stack = (char **)FEEL_GetMemory((sizeof(char *))*
					      current_expression_identifiers);

    for(i=0;i<current_expression_identifiers;i++) {
	*(identifier_stack + i) = identifier_name[identifier_list[i]];
    }

    *symbols = current_expression_identifiers ;
    current_expression_identifiers = 0;  /* reset */

    return(identifier_stack);
}


int identifier_no( name )  /* nameのIDENTIFIER番号を返す、identifier_name[]に
			  登録されていなければ登録し、その番号を返す。
			  名前の為の領域は引き数で示されるところが既に
			  確保されているものとする。                      */
     char *name;
{
    int i;

    for(i=0;i<identifiers;i++) {
	if(streq(identifier_name[i],name)) return(i);
    }

    if(identifiers == MAX_EXPRESSION_IDENTIFIER) {
	SystemAbort("Too many identifiers in expression.[identifier_no()]\n");
    }

    identifier_name[identifiers] = name;   /* 領域は新たには獲らない */

    identifiers++;

    return(identifiers - 1);
}

int function_no(char *);

push_function_and_push() /* expressionに現れる変数名を格納する為の関数 */
{
    int    i;
    int   no;
    char *cp;
    
    cp = PopString();
    push(cp);
    no = function_no( cp );

    for(i=0;i<current_expression_functions;i++) {
	if(no == function_list[i]) return;
    }

    if(current_expression_functions == MAX_EXPRESSION_FUNCTION) {
	SystemAbort("Too many functions in expression.[p_iden_and_pu()]\n");
    }

    function_list[current_expression_functions] = no;
    current_expression_functions++;

    return;
}

char **get_exp_functions( symbols )
     int *symbols;
{
    int i;
    char **function_stack;

    function_stack = (char **)FEEL_GetMemory((sizeof(char *))*
					      current_expression_functions);

    for(i=0;i<current_expression_functions;i++) {
	*(function_stack + i) = function_name[function_list[i]];
    }

    *symbols = current_expression_functions ;
    current_expression_functions = 0;  /* reset */

    return(function_stack);
}


function_no( name )  /* nameのFUNCTION番号を返す、function_name[]に
			  登録されていなければ登録し、その番号を返す。
			  名前の為の領域は引き数で示されるところが既に
			  確保されているものとする。                      */
     char *name;
{
    int i;

    for(i=0;i<functions;i++) {
	if(streq(function_name[i],name)) return(i);
    }

    if(functions == MAX_EXPRESSION_FUNCTION) {
	SystemAbort("Too many functions in expression.[function_no()]\n");
    }

    function_name[functions] = name;   /* 領域は新たには獲らない */

    functions++;

    return(functions - 1);
}


/*-----------------------------------------------------------------*/
Expression *get_expr_structure()
{
    Expression *expr_struct;
    int identifiers;
    int functions;

    expr_struct = (Expression *)FEEL_GetMemory(sizeof(Expression));

    expr_struct->expr = get_expression_string();
    expr_struct->identifier = get_exp_identifiers(&identifiers);
    expr_struct->function = get_exp_functions(&functions);
    
    expr_struct->identifiers = identifiers;
    expr_struct->functions   = functions;


/*
    printf("\n---------------\nexpr = %s\n",expr_struct->expr);
    printf("identifiers = %d\n",identifiers);
    printf("functions   = %d\n",functions);
*/

    return(expr_struct);
}
