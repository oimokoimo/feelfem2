/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_quad_method.c
 *      Date:   1993/07/15
 *   
 *   Purpose:   指定されている数値積分法が定義されているか調べる
 *              また、domainと整合しているかどうか調べる  etype検査(93/12/27)
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"
#include "../quadrature/quadrature.h"

solve_chk_quad_method()
{
    int i,j,k,l;
    
    int solves;
    int solve_elements;
    int equations;
    int terms;

    int solve_element_etype;
    
    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    Quadrature   *quad_ptr;
    Equation *eq_ptr;
    char **method_ptr;
    char *method;

    
    solves = how_many_solves();

    for(i=0;i<solves;i++) {
	
	solve_ptr = get_nth_solve_ptr(i);
	solve_elements = solve_ptr->solve_elements;

	for(j=0;j<solve_elements;j++) {
	    
	    solve_element_ptr = *(solve_ptr->solve_elem_dat + j);

	    /* 領域形状を得る(check_var_vs_domainで設定) */
	    solve_element_etype = solve_element_ptr->etype;

	    equations = solve_element_ptr -> equations;

	    for(k=0;k<equations;k++) {

		eq_ptr = *(solve_element_ptr->eq_data + k);
		terms  = eq_ptr->equation_terms;
		method_ptr = eq_ptr->eq_method;

		for(l=0;l<terms;l++) {
		    method = *(method_ptr + l);
		    if(method != NULL) {
			/* 解析的積分法を示す名前はANALYTIC_QUADに定義 */
			if( streq(method , ANALYTIC_QUAD) ) continue;
			if(is_defined_quadrature(method) == NO) {
			    if(english_mesg) {
				SystemError_yy_s("Quadrature method %s is not defined.",method,eq_ptr->yylineno);
			    }
			    else {
				SystemError_yy_s("数値積分法 %s は定義されていません。",method,eq_ptr->yylineno);
			    }
			    continue;
			}
			else {
			    quad_ptr = get_quadrature_ptr_by_name( method );

			    if(quad_ptr -> etype != solve_element_etype) {
				if(english_mesg) {
				    SystemError_yy_s("Quadrature method %s is not match the current element shape.",method,eq_ptr->yylineno);
				}
				else {
				    SystemError_yy_s("数値積分法 %s は指定の要素に不適合",method,eq_ptr->yylineno);
				}
				continue;
			    }
			}
		    }
		}
	    }
	}
    }
    return;
}

