/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   main_const_let.c
 *      Date:   1994/01/11
 *              1999/06/02 with initial value addition
 *   
 *   Purpose:   mainルーチンでconst変数の設定
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"

void main_const_let(fp)
     FILE *fp;
{
    int i;
    int const_vars;
    int int_vars;
    int double_vars;

    Var *var_ptr;
    Expression *expr_ptr;

    const_vars = how_many_const_vars();

    for(i=0;i<const_vars;i++) {
	var_ptr = get_nth_const_ptr(i);
	
	expr_ptr = (Expression *)(var_ptr -> val);

	F77("      ");
	PUT(fp,SCALAR_VAR_NAME77,var_ptr -> name );
	F77(" = ");
	PUT(fp,"%s",expr_ptr -> expr_inf);
	F77("\n");
    }
    COM;

    int_vars = how_many_int_vars();
    for(i=0;i<int_vars;i++) {
        var_ptr = get_nth_int_ptr(i);
        if(var_ptr->initial == YES && var_ptr->avsmode != 1) {
  	  F77("      ") ;
	  PUT(fp,SCALAR_VAR_NAME77,var_ptr -> name );
	  F77(" = ");
	  PUT(fp,"%s",var_ptr->val);
	  F77("\n");
        }
    }
       

    double_vars = how_many_double_vars();
    for(i=0;i<double_vars;i++) {
        var_ptr = get_nth_double_ptr(i);
        if(var_ptr->initial == YES && var_ptr->avsmode != 1) {
  	  F77("      ") ;
	  PUT(fp,SCALAR_VAR_NAME77,var_ptr -> name );
	  F77(" = ");
	  PUT(fp,"%s",var_ptr->val);
	  F77("\n");
        }
    }

    return;
}


