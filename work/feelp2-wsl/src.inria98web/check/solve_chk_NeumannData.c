/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_NeumannData.c
 *      Date:   1994/02/03
 *   
 *   Purpose:   ノイマン条件に関するデータチェック、及び諸変数代入
 *   Functions: 
 *           
 *        注意: ノイマン条件に関してはboundary_var系でも調べている
 *              境界名等は
 *
 *        境界積分項<...>に指定される変数についてもNeumannData内に登録する
 *                                                        (debug 94/02/08)
 *
 *        Gauss points wo shitei dekiru you ni shita
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void solve_chk_NeumannData()
{
    int i,j,k,l;
    int solves;
    int nconds;

    int err_flag;

    Solve        *solve_ptr;
    SolveElement *solve_element_ptr;
    NeumannData **n_ptrptr, *n_ptr;
    int exprs;
    Equation    **eq_ptrptr,*eq_ptr;
    Expression **expr_ptrptr,*expr_ptr;
    
    
    int identifiers;
    char **identifier,*name;
    
    int unknown_vars,fem_vars,scalar_vars;
    char **name_ptrptr;

    solves = how_many_solves();
    
    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);

	
	nconds   = solve_ptr -> n_conditions;
	n_ptrptr = solve_ptr -> n_dat;

	for(j=0;j<nconds;j++) {

	    /* 例によって、ここで関連するSolveElementを算出する */
	    if(solve_ptr-> solve_elements !=1) {
		SystemAbort("複数domain未対応@solve_chk_NeumannData ");
	    }

	    solve_element_ptr = *(solve_ptr->solve_elem_dat + 0 );
	    /*                                               ^^^  */

	    n_ptr = *(n_ptrptr + j);

	    /*======================*/
	    /* ガウス積分点の初期化 */
	    /*======================*/
	    n_ptr -> gauss_points = solve_ptr->boundary_gauss_points;

	    /*============================*/
	    /* nbc:文に含まれる変数のpush */
	    /*   MAKE UNIQ LIST           */
	    /*============================*/
	    expr_ptrptr = n_ptr -> expr_right; 
	    exprs       = n_ptr -> args;
	    
	    uniq_list_init();

	    for(k=0;k<exprs;k++) {
		expr_ptr = *(expr_ptrptr + k);
		identifiers = expr_ptr -> identifiers;
		identifier  = expr_ptr -> identifier;
		for(l=0;l<identifiers;l++) {
		    put_uniq_name( *(identifier + l) );
		}
	    }

	    /*==============================*/
	    /* 境界積分項に含まれる項のpush */
	    /*     MAKE UNIQ LIST           */
	    /*==============================*/
	    /* 未知関数に関しては無条件にpushしよう */
	    for(k=0;k<solve_element_ptr->unknowns;k++) {
		put_uniq_name(*(solve_element_ptr->unknown_name+k));
	    }
	    
	    for(k=0;k<solve_element_ptr->bd_fem_knowns;k++) {
		put_uniq_name(*(solve_element_ptr->bd_fem_known_name+k));
	    }

	    for(k=0;k<solve_element_ptr->bd_scalar_knowns;k++) {
		put_uniq_name(*(solve_element_ptr->bd_scalar_known_name+k));
	    }
		
	    identifiers  = how_many_uniq_items();
	    unknown_vars = 0;
	    fem_vars     = 0;
	    scalar_vars  = 0;
	    err_flag     =NO;

	    /* 変数のカウント(領域割り付けのため) */
	    for(k=0;k<identifiers;k++) {
		name = get_nth_uniq_item(k);
		
		switch(get_var_kind(name)) {
		  case FEM:
		    if(is_member(name,solve_ptr->unknown_name,
				 solve_ptr->unknowns)) {
			unknown_vars ++;
		    }
		    else {
			fem_vars++;
		    }
		    break;
		    
		  case EWISE:
		    if(english_mesg) {
			SystemError_yy_s("Ewise variable %s in boundary term.",
					 name,n_ptr->yylineno);
		    }
		    else {
			SystemError_yy_s("ノイマン条件定義式内にEWISE変数%sが現れた",
					 name,n_ptr -> yylineno);
		    }
		    err_flag = YES;
		    break;

		  case INT:
		  case DOUBLE:
		  case CONST:
		    scalar_vars++;

		  case SYSTEM_VAR:
		    break;

		  default:
		    SystemError_yy_s("%s is not defined.",
				   name,n_ptr -> yylineno);
		    err_flag = YES;
		    break;
		}
	    }
		    
	    if(err_flag == YES) continue;  /* 次の nbc:へ */

	    /* 領域割り当て */
	    n_ptr->unknown_name = (char **)FEEL_GetMemory(sizeof(char *) *
							  unknown_vars);
	    n_ptr->fem_var_name = (char **)FEEL_GetMemory(sizeof(char *) *
							  fem_vars);
	    n_ptr->scalar_var_name =(char **)FEEL_GetMemory(sizeof(char *) *
							    scalar_vars);
	    n_ptr->unknown_vars = unknown_vars;
	    n_ptr->fem_vars     = fem_vars;
	    n_ptr->scalar_vars  = scalar_vars;

	    unknown_vars = 0;
	    fem_vars     = 0;
	    scalar_vars  = 0;

	    /*==============*/
	    /* 変数名の代入 */
	    /*==============*/
	    for(k=0;k<identifiers;k++) {
		name = get_nth_uniq_item(k);
		
		switch(get_var_kind(name)) {
		  case FEM:
		    if(is_member(name,solve_ptr->unknown_name,
				 solve_ptr->unknowns)) {
			*(n_ptr->unknown_name + unknown_vars ) = name;
			unknown_vars++;
		    }
		    else {
			*(n_ptr->fem_var_name + fem_vars ) = name;
			fem_vars++;
		    }
		    break;
		    
		  case INT:
		  case DOUBLE:
		  case CONST:
		    *(n_ptr->scalar_var_name + scalar_vars ) = name;
		    scalar_vars++;

		  case SYSTEM_VAR:
		    break;

		  default:
		    SystemError_yy_s("%s is not defined (boundary term)",
				   name,n_ptr -> yylineno);
		    err_flag = YES;
		    break;
		}
	    } /* 変数名代入のループ */

	}/* nconds のループ */

    } /* solvesのループ */

    return;
}
