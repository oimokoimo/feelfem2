/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_chk_shape_function.c
 *      Date:   1993/10/28
 *   
 *   Purpose:   形状変換関数の定義
 *
 *   Functions: 形状変換関数と基本要素形状との整合性がとれているか検査
 *              現在、形状変換関数が未設定の場合、
 *                    三角形ならばP1,四辺形ならQ1に設定
 *                    一次元要素ならばL1に設定
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../element/element.h"

solve_chk_shape_function()
{
    int i,j;
    int solves;
    int solve_elements;
    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    Element *element_ptr;

    solves = how_many_solves();
    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);
	solve_elements =  solve_ptr -> solve_elements;

	for(j=0;j<solve_elements;j++) {

	    solve_element_ptr = *(solve_ptr->solve_elem_dat + j);
	    
	    if(solve_element_ptr->shape_func == NULL) {
		/* 形状変換関数が指定されていない場合 */

		switch(solve_element_ptr -> etype) {
		  case TRI:
		    solve_element_ptr-> shape_func
		      = DEFAULT_TRI_SHAPE_FUNCTION;
		    break;
		    
		  case RECT:
		    solve_element_ptr -> shape_func
		      = DEFAULT_RECT_SHAPE_FUNCTION;
		    break;

		  case LINE:
		    solve_element_ptr -> shape_func
		      = DEFAULT_LINE_SHAPE_FUNCTION;
		    break;
		    
		  default:
		    SystemAbort("solve_chk_shape_function:基本形状に誤り");
		}
	    }
	    else {
		/* 形状変換関数が指定されている場合は、
		   要素形状と整合性がとれているか検査する */
		
		element_ptr = 
		  get_element_ptr_by_name( solve_element_ptr->shape_func );

		if(element_ptr == NULL) {
		    if(english_mesg) {
			SystemError_yy_s("Isoparametric type %s is not defined.",
					 solve_element_ptr->shape_func,
					 solve_element_ptr->yylineno);
		    }
		    else {

			SystemError_yy_s("形状関数指定の要素 %s は未定義",
					 solve_element_ptr->shape_func,
					 solve_element_ptr->yylineno);
		    }
		    continue;
		}
		
		if(element_ptr->etype != solve_element_ptr->etype) {
		    if(english_mesg) {
			SystemError_yy_s("Isoparametric type %s does not match the region element shape.",
					 solve_element_ptr->shape_func,
					 solve_element_ptr->yylineno);
		    }
		    else {

			SystemError_yy_s("形状関数指定の要素 %s は計算領域形状と一致しない",
					 solve_element_ptr->shape_func,
					 solve_element_ptr->yylineno);
		    }
		    continue;
		}
		
	    }

	}
    }
    return;
}

