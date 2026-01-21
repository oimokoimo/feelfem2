/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_fem_funcs_bound.c
 *      Date:   1993/11/11
 *   
 *   Purpose:   *fem-func*に登録したシンボルをboundする
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../element/element.h"

void make_fem_funcs_bound(fp , element_name )
     FILE *fp;
     char *element_name;
{
    int i;
    int basis;

    Element     *element_ptr;
    Expression **expr_ptrptr;
    Expression  *expr_ptr;

    element_ptr = get_element_ptr_by_name( element_name );
    basis = element_ptr -> basis;
    expr_ptrptr = element_ptr -> expr;

    for(i=0;i<basis;i++) {
	expr_ptr = *(expr_ptrptr + i);

	LISP_SEND_sds(fp,"(setq %s_%d (minus-convert '%s ) )\n",element_name,i+1,expr_ptr->expr);
    }

    return;
}

void make_fem_funcs_co_bound(fp , element_name , n)
     FILE *fp;
     char *element_name;
     int n;                   /* n番目の形状関数をbound(nは０から) */
{

    Element     *element_ptr;
    Expression **expr_ptrptr;
    Expression  *expr_ptr;

    element_ptr = get_element_ptr_by_name( element_name );
    expr_ptrptr = element_ptr -> expr;

    if(n >= element_ptr->basis) {
	SystemAbort("誤った要素内基底番号が指定された");
    }

    expr_ptr = *(expr_ptrptr + n);

    LISP_SEND_sds(fp,"(setq %s_%d (minus-convert '%s ) )\n",element_name,n+1,expr_ptr->expr);

    return;
}



