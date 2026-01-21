/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   quad_check.c
 *      Date:   1993/11/15
 *   
 *   Purpose:   Quadrature構造体に対する検査
 *   Functions: 
 *    dbg: CAUTION: 注意: このルーチンは、quad内の数式をpre_to_inf
 *                        する為に作成した。
 *
 *   他に検査すべき項目(これに関するプログラムは後日作成)
 *
 *
 *
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../quadrature/quadrature.h"

quad_check()
{
    int i,j,k;
    int nodes;
    int quad_interpolates;
    int quads;
    int consts;
    int doubles;
    int quad_lets;

    Quadrature  *quad_ptr;
    QuadWeight  *qw_ptr;
    QuadInterpolate *qi_ptr;
    Expression **expr_ptrptr,*expr_ptr;

    quads = how_many_quads();

    for(i=0;i<quads;i++) {
	quad_ptr = get_nth_quad_ptr(i);

	consts    = quad_ptr-> consts;
	doubles   = quad_ptr-> doubles;
	quad_lets = quad_ptr-> quad_lets;

	/* constに関するpre_to_inf */
	expr_ptrptr = quad_ptr->const_val;
	for(j=0;j<consts;j++) {
	    expr_ptr = *(expr_ptrptr+j);
	    pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
	}

	/* doubleに関するpre_to_inf */
	expr_ptrptr = quad_ptr->double_val;
	for(j=0;j<doubles;j++) {
	    expr_ptr = *(expr_ptrptr+j);
	    pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
	}

	/* quad_letに関するpre_to_inf */
	expr_ptrptr = quad_ptr->let_val;
	for(j=0;j<quad_lets;j++) {
	    expr_ptr = *(expr_ptrptr+j);
	    pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
	}

	
	/* 各数値積分点に関する pre_to_inf */
	nodes = quad_ptr -> nodes;
	for(j=0;j<nodes;j++) {
	    qw_ptr = *(quad_ptr -> quad_weight_ptrptr + j);
	    switch(quad_ptr->dimension) {
	      case 3:
		expr_ptr = qw_ptr -> t;
		pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));

	      case 2:
		expr_ptr = qw_ptr -> s;
		pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));

	      case 1:
		expr_ptr = qw_ptr -> r;
		pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));	    

		break;

	      default:
		SystemAbort("Illegal dimension in Quadrature(quad_check.c)");
	    }
	    expr_ptr = qw_ptr -> weight;
	    pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));	    

	}

	/* QuadInterpolateに関する pre_to_inf */
	quad_interpolates = quad_ptr -> interpolates;
	for(j=0;j<quad_interpolates;j++) {
	    qi_ptr = *(quad_ptr -> quad_interpolate_ptr + j);
	    nodes = qi_ptr -> nodes;
	    
	    expr_ptrptr = qi_ptr -> interpolate_expr;

	    for(k=0;k<nodes;k++) {
		expr_ptr = *(expr_ptrptr + k);
		pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
	    }
	} /* interpolateの終わり */

    }  /* quads ループの終わり */

    return;
}
