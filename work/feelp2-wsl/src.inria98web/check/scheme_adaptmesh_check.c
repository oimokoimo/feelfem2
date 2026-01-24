/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_adaptmesh_check.c
 *      Date:   1997/07/25
 *   
 *   Purpose:   adaptmesh
 *   Functions: 
 *              adapt_ptr -> xyz_vars,x_flag,ew_vars等の処理を行う
 *              
 *              adapt文の種別   L2,MAX
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"
#include "../scheme_comp/scheme_comp.h"
#include "../mesh_comp/mesh_comp.h"

#include "check.h"

void scheme_adaptmesh_check()
{
    int i,j;
    int schemes;

    int int_vars,dbl_vars;          /* int,doubleを区別する為 */
    int sc_vars,fem_vars,ew_vars;   /* 右辺に現れる変数の種類 */
    int xyz_vars;
    int fort_funcs;
    int diff_ops;  
    int user_funcs;

    int domains;

    char *fem_name_buf[MAX_VARIABLES];
    char *ew_name_buf[MAX_VARIABLES];
    char *int_name_buf[MAX_VARIABLES];
    char *dbl_name_buf[MAX_VARIABLES];

    Scheme *scheme_ptr;
    Adaptmesh    *adapt_ptr;
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
    int  comeyet;

    int  adaptmeshs;

    schemes = how_many_schemes();
    domains = how_many_domains();

    comeyet = 0;

    adaptmeshs = how_many_adaptmesh();
    if(adaptmeshs>1) {
      SystemError("Only one adaptmesh is allowed.");
    }

    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != ADAPTMESH ) continue;

	if(comeyet == 0 && bamg_mode != 1) {
	  SystemError("adaptmesh statement can be used only in bamg mode.");
	}
	
	adapt_ptr  = (Adaptmesh *)scheme_ptr->ptr;


	expr_ptr = adapt_ptr -> expr;
	
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

	adapt_ptr -> x_flag = NO;
	adapt_ptr -> y_flag = NO;
	adapt_ptr -> z_flag = NO;


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
		    adapt_ptr->x_flag = YES;
		}
		if(streq(*(identifier+j),"y") || streq(*(identifier+j),"Y")){
		    adapt_ptr->y_flag = YES;
		}
		if(streq(*(identifier+j),"z") || streq(*(identifier+j),"Z")){
		    adapt_ptr->z_flag = YES;
		}

		xyz_vars++;
		break;

	      case TEST_VAR:
		SystemError_yy_s("%s is a symbol for test function.",
				 *(identifier+j),
				 adapt_ptr->yylineno);
		break;

	      case NO:
		SystemError_yy_s("%s is not defined.",*(identifier+j),
				 adapt_ptr->yylineno);
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
				 *(function + j),adapt_ptr->yylineno);
	    }
	}

	if(ew_vars != 0) {
	    SystemError_yy("There are ewise variables in ADAPT statement.",
			   adapt_ptr->yylineno);
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


	adapt_ptr -> fem_vars = fem_vars;
	adapt_ptr -> ew_vars  = ew_vars;
	adapt_ptr -> sc_vars  = sc_vars;
	adapt_ptr -> int_vars = int_vars;
	adapt_ptr -> dbl_vars = dbl_vars;
	adapt_ptr -> xyz_vars = xyz_vars;
	adapt_ptr -> user_funcs = user_funcs;
	adapt_ptr -> fort_funcs = fort_funcs;
	adapt_ptr -> diff_ops   = diff_ops;

	if(fem_vars) {
	    adapt_ptr -> fem_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      fem_vars);
	    for(j=0;j<fem_vars;j++) {
		*(adapt_ptr->fem_var_name + j) = fem_name_buf[j];
	    }
	}
	else {
	    adapt_ptr -> fem_var_name = NULL;
	}

	if(ew_vars) {
	    adapt_ptr -> ew_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      ew_vars);
	    for(j=0;j<ew_vars;j++) {
		*(adapt_ptr->ew_var_name + j) = ew_name_buf[j];
	    }
	}
	else {
	    adapt_ptr -> ew_var_name = NULL;
	}

	if(int_vars) {
	    adapt_ptr -> int_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      int_vars);
	    for(j=0;j<int_vars;j++) {
		*(adapt_ptr->int_var_name + j) = int_name_buf[j];
	    }
	}
	else {
	    adapt_ptr -> int_var_name = NULL;
	}

	if(dbl_vars) {
	    adapt_ptr -> dbl_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							      dbl_vars);
	    for(j=0;j<dbl_vars;j++) {
		*(adapt_ptr->dbl_var_name + j) = dbl_name_buf[j];
	    }
	}
	else {
	    adapt_ptr -> dbl_var_name = NULL;
	}
    }

    return;
}
