/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_norm_check.c
 *      Date:   1994/12/20
 *   
 *   Purpose:   norm文に関する検査を実行する
 *   Functions: 
 *              norm_ptr -> xyz_vars,x_flag,ew_vars等の処理を行う
 *              
 *              norm文の種別   L2,MAX
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"
#include "../scheme_comp/scheme_comp.h"
#include "../mesh_comp/mesh_comp.h"

void scheme_norm_check()
{
    int i,j;
    int schemes;

    int int_vars,dbl_vars;          /* int,doubleを区別する為 */
    int sc_vars,fem_vars,ew_vars;   /* 右辺に現れる変数の種類 */
    int xyz_vars;
    int fort_funcs;
    int diff_ops;  
    int user_funcs;
    int var_type;

    int domains;

    char *fem_name_buf[MAX_VARIABLES];
    char *ew_name_buf[MAX_VARIABLES];
    char *int_name_buf[MAX_VARIABLES];
    char *dbl_name_buf[MAX_VARIABLES];

    Scheme *scheme_ptr;
    Norm    *norm_ptr;
    char  **region_name;
    int     regions;

    EWISE_var  *ewise_var_ptr;
    EWISE_type *ewise_type_ptr;
    FEM_var    *fem_var_ptr;
    FEM_type   *fem_type_ptr;
    Expression *expr_ptr;

    char *var_name;

    int  identifiers,functions;
    char **identifier,**function;

    schemes = how_many_schemes();
    domains = how_many_domains();

    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != NORM ) continue;
	
	norm_ptr  = (Norm *)scheme_ptr->ptr;

	var_name = norm_ptr->var_name;

	var_type = get_var_kind( var_name );
	switch(var_type) {
	  case SYSTEM_VAR:
	  case TEST_VAR:
	    if(english_mesg) {
		SystemError_yy_s("Cannot use norm with %s.",
				  var_name,norm_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("normを変数%sに代入はできない",var_name,
				 norm_ptr->yylineno);
	    }
	    continue;

	  case NO:
	    if(english_mesg) {
		SystemError_yy_s("Variable %s is not defined.",
				 var_name,norm_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("変数%sは宣言されていない",var_name,
				 norm_ptr->yylineno);
	    }
	    continue;

    /* 各変数の場合には、それぞれのポインタをガメル */
	  case FEM:
	  case EWISE:
	    SystemError_yy("Try to assigen scalar value to vector variable.",
			     norm_ptr->yylineno);
	  case DOUBLE:
	    break;

	  case CONST:
	    SystemError_yy_s("%s is a constant variable.",var_name,
			   norm_ptr->yylineno);
	    continue;

	  case INT:
	    SystemError_yy_s("%s is an INTEGER variable.",var_name,
			   norm_ptr->yylineno);
	    break;

	  default:
	    SystemAbort("INNER ERROR XX1(scheme_norm_check)");
	    break;

	}

	expr_ptr = norm_ptr -> expr;
	
	/* PRE_TO_INFに積む */
	pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));

	int_vars = 0;
	dbl_vars = 0;
	sc_vars  = 0;
	fem_vars = 0;
	ew_vars  = 0;
	xyz_vars = 0;
	fort_funcs = 0;
	user_funcs = 0;
	diff_ops   = 0;

	norm_ptr -> x_flag = NO;
	norm_ptr -> y_flag = NO;
	norm_ptr -> z_flag = NO;


	identifiers = expr_ptr -> identifiers;
	identifier  = expr_ptr -> identifier;

	functions   = expr_ptr -> functions;
	function    = expr_ptr -> function;

	for(j=0;j<identifiers;j++) {

	    switch( get_var_kind( *(identifier+j))) {
	      case FEM:
		fem_name_buf[fem_vars] = *(identifier+j);
		fem_vars++;
		break;
		
	      case EWISE:
		ew_name_buf[ew_vars] = *(identifier+j);
		ew_vars++;
		break;
		
	      case CONST:
	      case DOUBLE:
		dbl_name_buf[dbl_vars] = *(identifier + j);
		dbl_vars++;
		sc_vars++;
		break;
		
	      case INT:
		int_name_buf[int_vars] = *(identifier + j);
		int_vars++;
		sc_vars++;
		break;
		
	      case SYSTEM_VAR: /* 現在空間変数(var_check.c)ならば… */

		if(streq(*(identifier+j),"x") || streq(*(identifier+j),"X")){
		    norm_ptr->x_flag = YES;
		}
		if(streq(*(identifier+j),"y") || streq(*(identifier+j),"Y")){
		    norm_ptr->y_flag = YES;
		}
		if(streq(*(identifier+j),"z") || streq(*(identifier+j),"Z")){
		    norm_ptr->z_flag = YES;
		}

		xyz_vars++;
		break;

	      case TEST_VAR:
		SystemError_yy_s("%s is a symbol for test function.",
				 *(identifier+j),
				 norm_ptr->yylineno);
		break;

	      case NO:
		SystemError_yy_s("%s is not defined.",*(identifier+j),
				 norm_ptr->yylineno);
		break;
	    }
	}

	for(j=0;j<functions;j++) {
	    if(is_feel_user_func(*(function + j))) {
		user_funcs++;
	    }
	    else if(is_fort77_func(*(function + j))) {
		fort_funcs++;
	    }
	    else if(is_diff_op(*(function + j))) {
		diff_ops++;
	    }
	    else {
		SystemError_yy_s("Function %s is not defined.",
				 *(function + j),norm_ptr->yylineno);
	    }
	}

	if(ew_vars != 0) {
	    SystemError_yy("There are ewise variables in NORM statement.",
			   norm_ptr->yylineno);
	    continue;
	}

/*
	fprintf(stderr,"変数名 %s\n",var_name);
	fprintf(stderr,"fem    %d\n",fem_vars);
	fprintf(stderr,"ew     %d\n",ew_vars);
	fprintf(stderr,"sc     %d\n",sc_vars);
	fprintf(stderr,"x,y,z  %d\n",xyz_vars);
	fprintf(stderr,"user   %d\n",user_funcs);
	fprintf(stderr,"fort   %d\n",fort_funcs);
	fprintf(stderr,"diff   %d\n",diff_ops);
*/


	norm_ptr -> fem_vars = fem_vars;
	norm_ptr -> ew_vars  = ew_vars;
	norm_ptr -> sc_vars  = sc_vars;
	norm_ptr -> int_vars = int_vars;
	norm_ptr -> dbl_vars = dbl_vars;
	norm_ptr -> xyz_vars = xyz_vars;
	norm_ptr -> user_funcs = user_funcs;
	norm_ptr -> fort_funcs = fort_funcs;
	norm_ptr -> diff_ops   = diff_ops;

	if(fem_vars) {
	    norm_ptr -> fem_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      fem_vars);
	    for(j=0;j<fem_vars;j++) {
		*(norm_ptr->fem_var_name + j) = fem_name_buf[j];
	    }
	}
	else {
	    norm_ptr -> fem_var_name = NULL;
	}

	if(ew_vars) {
	    norm_ptr -> ew_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      ew_vars);
	    for(j=0;j<ew_vars;j++) {
		*(norm_ptr->ew_var_name + j) = ew_name_buf[j];
	    }
	}
	else {
	    norm_ptr -> ew_var_name = NULL;
	}

	if(int_vars) {
	    norm_ptr -> int_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      int_vars);
	    for(j=0;j<int_vars;j++) {
		*(norm_ptr->int_var_name + j) = int_name_buf[j];
	    }
	}
	else {
	    norm_ptr -> int_var_name = NULL;
	}

	if(dbl_vars) {
	    norm_ptr -> dbl_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      dbl_vars);
	    for(j=0;j<dbl_vars;j++) {
		*(norm_ptr->dbl_var_name + j) = dbl_name_buf[j];
	    }
	}
	else {
	    norm_ptr -> dbl_var_name = NULL;
	}
    }

    return;
}
