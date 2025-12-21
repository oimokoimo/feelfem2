/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1993/10/14
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"

void var_const_pretoinf()
{
    int i;
    int const_vars;
    Var *var_ptr;
    Expression *expr_ptr;

    const_vars = how_many_const_vars();

    for(i=0;i<const_vars;i++) {
	var_ptr = get_nth_const_ptr(i);
	
	expr_ptr = (Expression *)(var_ptr -> val);
	
	pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
    }

    return;
}


