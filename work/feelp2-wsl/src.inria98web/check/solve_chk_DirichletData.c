/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_DirichletData.c
 *      Date:   1993/12/7
 *   
 *   Purpose:   Dirichlet条件に関するデータ処理
 *   Functions: pre_to_inf の実行
 *              DirichletData構造体の完成
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void solve_chk_DirichletData()
{
    int i,j,k;
    int solves;
    int dconds;

    Solve *solve_ptr;
    DirichletData **d_ptrptr,*d_ptr;
    Expression *expr_ptr;

    int    identifiers;
    char **identifier,*name;

    int    fem_vars,scalar_vars;
    char **name_ptrptr;

    solves = how_many_solves();

    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr( i );
	
	dconds   = solve_ptr -> d_conditions;
	d_ptrptr = solve_ptr -> d_dat;
	
	for(j=0;j<dconds;j++) {
	    d_ptr = *(d_ptrptr + j);

	    expr_ptr = d_ptr -> expr;
	    
	    /*=================*
	     * pre_to_inf_push *
	     *=================*/
	    pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));

	    /*==================================
	      境界条件に使用の変数名の検査と登録
	      ================================== */
	    identifiers = expr_ptr -> identifiers;
	    identifier  = expr_ptr -> identifier;
	   
	    fem_vars    = 0;
	    scalar_vars = 0;
 
	    for(k=0;k<identifiers;k++) {
		name = *(identifier + k);

		if(is_member(name,
			     solve_ptr->unknown_name,
			     solve_ptr->unknowns)     ){
		    if(english_mesg) {
			SystemError_yy("There are unknown variables in Dirichlet data.",d_ptr->yylineno);
		    }
		    else {
			SystemError_yy("未知変数がDirichlet条件右辺に出現",
				   d_ptr->yylineno);
		    }
		    continue;
		}

		switch(get_var_kind( name )) {
		  case FEM:
		    fem_vars++;
		    break;

		  case EWISE:
		    if(english_mesg) {
			SystemError_yy("There are ewise variables in Dirichlet data.",d_ptr->yylineno);
		    }
		    else {
			SystemError_yy("ewise変数がDirichlet条件右辺に出現",
				       d_ptr->yylineno);
		    }
		    break;
		    
		  case DOUBLE:
		  case CONST:
		    scalar_vars++;
		    break;

		  case INT:
		    if(english_mesg) {
			SystemError_yy("There are integer variable in Dirichlet data.",d_ptr->yylineno);
		    }
		    else {
			SystemError_yy("integer変数がDirichlet条件右辺に出現",
				       d_ptr->yylineno);
		    }
		    break;

		  case SYSTEM_VAR:  /* 空間変数 x,y,z */
		    break;          

		  case TEST_VAR:
		    SystemError_yy("Test function symbol in Dirichlet data",
				   d_ptr->yylineno);
		    break;
		    
		  case NO:
		    SystemError_yy_s("Undefined name %s in Dirichlet data",
				     name,
				     d_ptr->yylineno);
		    break;
		    
		  default:
		    SystemAbort("おーまぁいがぁ＠solve_chk_DirichletData");
		}
	    }

	    /* 領域確保 */
	    d_ptr -> fem_vars    = fem_vars;
	    d_ptr -> scalar_vars = scalar_vars;

	    if(fem_vars) {
		d_ptr ->fem_var_name = 
		  (char **)FEEL_GetMemory(sizeof(char *) * fem_vars);
	    }

	    if(scalar_vars) {
		d_ptr ->scalar_var_name = 
		  (char **)FEEL_GetMemory(sizeof(char *) * scalar_vars);
	    }

	    /* 代入PHASE */
	    fem_vars    = 0;
	    scalar_vars = 0;

	    for(k=0;k<identifiers;k++) {
		name = *(identifier + k);

		if(is_member(name,
			     solve_ptr->unknown_name,
			     solve_ptr->unknowns)     ){
		    continue;
		}

		switch(get_var_kind( name )) {
		  case FEM:
		    *(d_ptr->fem_var_name + fem_vars) = name;
		    fem_vars++;
		    break;

		  case EWISE:
		    break;
		    
		  case DOUBLE:
		  case CONST:
		    *(d_ptr->scalar_var_name + scalar_vars) = name;
		    scalar_vars++;
		    break;

		  case INT:
		    break;

		  case SYSTEM_VAR:  /* 空間変数 x,y,z */
		    break;          

		  case TEST_VAR:
		    break;
		    
		  case NO:
		    break;
		    
		  default:
		    SystemAbort("おーまぁいがぁ＠solve_chk_DirichletData");
		}
	    }
	    
	}
    }
    return;
}


