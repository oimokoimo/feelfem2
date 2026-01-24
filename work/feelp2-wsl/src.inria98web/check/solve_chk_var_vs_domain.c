/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_var_vs_domain.c
 *      Date:   1993/07/16
 *   
 *   Purpose:   各solve_element内の配列変数(fem,ewise)の型整合性
 *              と、solve_element_ptr->etype の代入
 *                  ewise_type_ptr->etype も代入します。
 *              
 */
#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"

solve_chk_var_vs_domain()
{
    int i,j,k;
    
    int solves;
    int solve_elements;
    int equations;
    int identifiers;

    int etype;
    
    Solve *solve_ptr;
    SolveElement *solve_element_ptr;

    FEM_type *fem_type_ptr;
    EWISE_type *ewise_type_ptr;

    char **identifier;
    char *domain_name;
    char *name;
    
    solves = how_many_solves();

    for(i=0;i<solves;i++) {
	
	solve_ptr = get_nth_solve_ptr(i);
	solve_elements = solve_ptr->solve_elements;

	for(j=0;j<solve_elements;j++) {
	    
	    solve_element_ptr = *(solve_ptr->solve_elem_dat + j);
	    domain_name = solve_element_ptr->domain_name;

	    /* 領域名が確定しない場合は処置無し(この前のcheckルーチン群で
	       エラー出力済み                                            */

	    if(domain_name == NULL) {
		continue;
	    }

	    /* solve_elementのetype の代入処理 */
	    solve_element_ptr->etype = get_domain_etype_by_name( domain_name );
	    
	    /* 対応するdomain名のetypeが確定しなければ処置なし */
	    if(solve_element_ptr->etype == NO) {
		continue;
	    }

	    /* fem変数のチェック */
	    identifiers = solve_element_ptr->unknowns;
	    if(identifiers == 0) {  
		SystemAbort("Internal Error. No unknowns in solve_element");
	    }

	    /* 未知fem変数の定義が有効かどうかの検査 */
	    identifier = solve_element_ptr->unknown_name;
	    
	    for(k=0;k<identifiers;k++) {
		name = *(identifier + k);
		fem_type_ptr = get_fem_type_ptr_by_2name(name,domain_name);

		if(fem_type_ptr == NULL) {
		    if(english_mesg) {
			SystemError_yy_ss("FEM variable %s cannot be used in domain %s.",name,domain_name,solve_ptr->yylineno);
		    }
		    else {
			SystemError_yy_ss("fem変数 %s はdomain %s では指定不可",name,domain_name,solve_ptr->yylineno);
		    }
		    continue;
		}
	    }

	    /* 既知fem変数の定義が有効かどうかの検査 */
	    identifiers = solve_element_ptr->fem_knowns;
	    identifier = solve_element_ptr->fem_known_name;
	    
	    for(k=0;k<identifiers;k++) {
		name = *(identifier + k);
		fem_type_ptr = get_fem_type_ptr_by_2name(name,domain_name);

		if(fem_type_ptr == NULL) {
		    if(english_mesg) {
			SystemError_yy_ss("fem variable %s cannot be used in domain %s.",name,domain_name,solve_ptr->yylineno);
		    }
		    else {
			SystemError_yy_ss("fem変数 %s はdomain %s では指定不可",name,domain_name,solve_ptr->yylineno);
		    }
		    continue;
		}
	    }

	    /* ewise変数が同一のdomainかどうかの検査 */
	    identifiers = solve_element_ptr->ewise_knowns;
 	    identifier = solve_element_ptr->ewise_known_name;

	    for(k=0;k<identifiers;k++) {
		name = *(identifier + k);
		ewise_type_ptr = get_ewise_type_ptr_by_2name(name,domain_name);

		if(ewise_type_ptr == NULL) {
		    if(english_mesg) {
			SystemError_yy_ss("ewise variable %s cannot be used in domain %s.",name,domain_name,solve_ptr->yylineno);
		    }
		    else {
			SystemError_yy_ss("ewise変数 %s はdomain %s の変数として指定不可",name,domain_name,solve_ptr->yylineno);
		    }
		}
	    }

	}

    }

    return;
}



