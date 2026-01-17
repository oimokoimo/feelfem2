/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   var_check.c
 *      Date:   1993/06/03 (Modified)
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 *              
 *              
 *              

 *              
 *              
 *              
 *              
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../var_comp/var_comp.h"
#include "../system/system.h"

/*----------------------------------------------------------------*/

typedef struct {      /* 変数名検査用構造体 */
    char *name;       /* ここでの名称は小文字に統一されている */
    int   type;
    int   yylineno;
} VarCheck;

static VarCheck *var_check;
static int       reg_vars ;
                     
/* ユーザ登録関数の指定 */
static char     *user_func[MAX_USERFUNCS];
int              user_funcs=0;
/*----------------------------------------------------------------*/

/* 変数としては用いることの出来ない文字列の数々 */

/* feelのキーワード */
static char *feel_key_word[] = {
    "t","T","nil","NIL",
    "dx","dy","dz","dn","lap","x","y","z",
    "l1","l2","l3","l4",
    "tri","rect","line","tetra","cube",
    NULL
  };

/* feelが常に変数として受け付けるもの */
static char *feel_system_var[] = {
    "x","y","z",
    NULL
  };

/* 微分作用素 */
static char *feel_diff_op[] = {
    "dx","dy","dz","dn",NULL
  };


static char *feel_test_var[]  = {
    "$",
    NULL
  };

/* feelのシステム関数 */
static char *feel_fem_func[] = {
    "dnorm",  NULL
  };

/* fortran の関数 */
static char *fort77_func[] = {
    "int","ifix","idint","iqint",
    "sngl","float","snglq",
    "dfloat","dbleq","dreal",
    "qfloat","qextd","qreal","quad","qext","qfloat",
    "cmplx","csngl",
    "dcmplx","cdble",
    "qcmplx",
    "ichar","char",
    "aint","dint","qint",
    "anint","dnint","qnint",
    "anint","dnint","qnint",
    "nint","idnint","iqnint",
    "iabs","abs","dabs","qabs","cabs","cdabs","cqabs",
    "mod","amod","dmod","qmod",
    "isign","sign","dsign","qsign",
    "idim","dim","ddim","qdim",
    "dprod","qprod",
    "max0","amax1","dmax1","qmax1",
    "amax0","max1",
    "min0","amin1","dmin1","qmin1",
    "amin0","min1",
    "len","index",
    "aimag","dimag","qimag",
    "conjg","dconjg","qconjg",
    "sqrt","dsqrt","qsqrt","csqrt","cdsqrt","cqsqrt",
    "exp","dexp","qexp","cexp","cdexp","cqexp",
    "alog","dlog","qlog","clog","cdlog","cqlog",
    "alog10","dlog10","qlog10",
    "alog2","dlog2","qlog2",
    "sin","dsin","qsin","csin","cdsin","cqsin",
    "cos","dcos","qcos","ccos","cdcos","cqcos",
    "tan","dtan","qtan",
    "cotan","dcotan","qcotan",
    "asin","arsin","dasin","darsin","qasin","qarsin",
    "acos","arcos","dacos","darcos","qacos","qarcos",
    "atan","datan","qatan",
    "atan2","datan2","qatan2",
    "sinh","dsinh","qsinh",
    "cosh","dcosh","qcosh",
    "tanh","dtanh","qtanh",
    "asinh","dasinh",
    "acosh","dacosh",
    "atanh","datanh",
    "erf","derf","qerf",
    "erfc","derfc","qerfc",
    "gamma","cgama","dgamma","cdgama",
    "algama","dlgama","cbrt","dcbrt","qcbrt",
    "cang","dcang","qcang",
    "lge","lgt","lle","llt",
    "ior","iand","ieor","not",
    "ishft","btest","ibset","ibclr","ibchng",
    NULL
  };

/* fortranの予約語 */
static char *fort77_word[] = {
    "program","subroutine","function",
    "common","dimension","external",
    "implicit","integer","real","double","complex",
    "data","save",
    "open","close","rewind",
    "do","continue","if","then","else","goto",
    "end","return","stop",
    NULL
  };

/* fortran の記号 */
static char fort77_mark[] = {
    '(' , ')','+','-','*','/','\0'
  };

/*  tree図
 *
 *  |-feel_data_check
 *  |      |
 *  |      |-var_register
 *
 *  var_check構造体配列に変数名、種別を登録し、多重定義を発見する
 */

var_register()
{
    int i,j,k;
    int max;
    Var *var_ptr;

    /* 領域var_checkの確保 */
    max = how_many_int_vars();
    max = max + how_many_double_vars();
    max = max + how_many_const_vars();
    max = max + how_many_fem_vars();
    max = max + how_many_ewise_vars();
    max = max + how_many_material_vars();

    var_check = (VarCheck *)FEEL_GetMemory( max * (sizeof(VarCheck)));
    reg_vars = 0;

    /* 整数変数の登録 */
    max = how_many_int_vars();
    for(i=0;i<max;i++) {
	var_ptr = get_nth_int_ptr(i);
	if(register_var_name(var_ptr)) {
	    if(english_mesg) {
		SystemError_s("Variable %s is multiply declared.",var_ptr->name);
	    }
	    else {
		SystemError_s("変数 %s は多重定義している",var_ptr->name);
	    }
	}
    }

    /* 定数変数の登録 */
    max = how_many_const_vars();
    for(i=0;i<max;i++) {
	var_ptr = get_nth_const_ptr(i);
	if(register_var_name(var_ptr)) {
	    if(english_mesg) {
		SystemError_s("Variable %s is multiply declared.",var_ptr->name);
	    }
	    else {
		SystemError_s("変数 %s は多重定義している",var_ptr->name);
	    }
	}
    }


    /* 実数変数の登録 */
    max = how_many_double_vars();
    for(i=0;i<max;i++) {
	var_ptr = get_nth_double_ptr(i);
	if(register_var_name(var_ptr)) {
	    if(english_mesg) {
		SystemError_s("Variable %s is multiply declared.",var_ptr->name);
	    }
	    else {
		SystemError_s("変数 %s は多重定義している",var_ptr->name);
	    }
	}
    }


    /* fem変数の登録 */
    max = how_many_fem_vars();
    for(i=0;i<max;i++) {
	var_ptr = get_nth_fem_ptr(i);
	if(register_var_name(var_ptr)) {
	    if(english_mesg) {
		SystemError_s("Variable %s is multiply declared.",
			      var_ptr->name);
	    }
	    else {
		SystemError_s("変数 %s は多重定義している",var_ptr->name);
	    }
	}
    }


    /* ewise変数の登録 */
    max = how_many_ewise_vars();
    for(i=0;i<max;i++) {
	var_ptr = get_nth_ewise_ptr(i);
	if(register_var_name(var_ptr)) {
	    if(english_mesg) {
		SystemError_s("Variable %s is multiply declared.");
	    }
	    else {
		SystemError_s("変数 %s は多重定義している",var_ptr->name);
	    }
	}
    }

}

/*  tree図----------------------------
 *
 *  |-feel_data_check
 *  |      |
 *  |      |-var_register
 *  |      |    |
 *  |      |    |-register_var_name
 *
 *  名称を小文字に変換して記録する
 *------------------------------------*/
register_var_name(var_ptr)
     Var *var_ptr;
{
    int i;
    char *name;
    char *name2;

    name = MakeStringCopy( var_ptr -> name );
    name2 = name;

    while(*name2) {
	if(*name2 >= 'A' && *name2 <= 'Z') *name2 = *name2 - 'A' + 'a';
	name2++;
    }
    

    for(i=0;i<reg_vars;i++) {
	if(streq( name, (var_check+i)->name)) {
	    FEEL_FreeMemory(name);
	    return(YES);  /* Error return は 0以外 */
	}
    }

    (var_check+reg_vars)->name = name;
    (var_check+reg_vars)->type = var_ptr->type;
    (var_check+reg_vars)->yylineno = var_ptr->yylineno;

    reg_vars++;

    return(NO);
}


/*  tree図
 *
 *  |-feel_data_check()
 *  |      |
 *  |      |-var_reserved_check()
 *
 *  変数名がfeel,fortranの予約語になっていないかどうかを調べる。
 */

var_reserved_check()
{
    int i,j;
    char name[BUFSIZ];
    char *cp,*cp2;

    
    for(i=0;i<reg_vars;i++) {
	
	cp  = (var_check + i)-> name;
	cp2 = name;

	/* 全て小文字ベースで比べる */

	while(*cp) {
	    if(*cp >= 'A' && *cp <='Z') {
		*cp2 = *cp - 'A' + 'a';
	    }
	    else {
		*cp2 = *cp;
	    }
	    cp++;
	    cp2++;
	}
	*cp2 = '\0';


	/* feel keyword? */
	for(j=0;feel_key_word[j]!=NULL;j++) {
	    if(streq(feel_key_word[j],name)) {
		if((var_check+i)->type == FEM ||(var_check+i)->type == EWISE ){
		    if(english_mesg) {
			SystemError_s("Name '%s' is reserved keyword.",name);
		    }
		    else {
			SystemError_s("変数名 '%s' はFEELのキーワード故使用不可",
				      name);
		    }
		}
		else {
		    if(english_mesg) {
			SystemError_yy_s("Variable '%s' is reserved keyword.",
					 name,(var_check+i)->yylineno);
		    }
		    else {
			SystemError_yy_s("変数名 '%s'はFEELのキーワード故使用不可",
					 name,(var_check+i)->yylineno);
		    }
		}
		break;
	    }
	}


	/* fortran function? */
	for(j=0;fort77_func[j]!=NULL;j++) {
	    if(streq(fort77_func[j],name)) {
		if((var_check+i)->type == FEM ||(var_check+i)->type == EWISE ){
		    SystemError_s("'%s' is FORTRAN keyword, you cannot use it.",				 
				  name);
		}
		else {
		    SystemError_yy_s("'%s' is FORTRAN keyword, you cannot use it.",				 
				     name,(var_check+i)->yylineno);
		}
		break;
	    }
	}


	/* fortran の予約語か？ */
	for(j=0;fort77_word[j]!=NULL;j++) {
	    if(streq(fort77_word[j],name)) {
		if((var_check+i)->type == FEM ||(var_check+i)->type == EWISE ){
		    SystemError_s("'%s' is FORTRAN keyword, you cannot use it.",
				     name);
		}
		else {
		    SystemError_yy_s("'%s' is FORTRAN keyword, you cannot use it.",
				     name,(var_check+i)->yylineno);
		}
		break;
	    }
	}

    }
}

/* 微分作用素かどうかの検査 */
is_diff_op( name )
     char *name;
{
    int i;
    for(i=0;feel_diff_op[i] != NULL;i++) {
	if(streq(feel_diff_op[i],name)) return(YES);
    }

    return(NO);
}


/* FORTRANの組み込み関数かどうかのチェック */

is_fort77_func( name ) 
     char *name;
{
    int j;

    for(j=0;fort77_func[j]!=NULL;j++) {
	if(streq(fort77_func[j],name)) return(YES);
    }

    return(NO);
}

/* FORTRANのキーワードかどうかのチェック */

is_fort77_keyword( name ) 
     char *name;
{
    int j;

    for(j=0;fort77_word[j]!=NULL;j++) {
	if(streq(fort77_word[j],name)) return(YES);
    }

    return(NO);
}

is_feel_system_var( name )
     char *name;
{
    int j;

    for(j=0;feel_system_var[j]!=NULL;j++) {
	if(streq(feel_system_var[j],name)) return(YES);
    }

    return(NO);
}

is_feel_test_var( name )
     char *name;
{
    int j;

    for(j=0;feel_test_var[j]!=NULL;j++) {
	if(streq(feel_test_var[j],name)) return(YES);
    }

    return(NO);
}

void register_user_func( name )
     char *name;
{

    if(user_funcs == MAX_USERFUNCS) {
	SystemError("Too many user defined functions.");
	return;
    }
    user_func[user_funcs] = name;

    user_funcs++;
    return;
}

int is_feel_user_func( name )
     char *name;
{
    int i;
    for(i=0;i<user_funcs;i++) {
	if(streq(name , user_func[i])) {
	    return(YES);
	}
    }

    return(NO);
}

