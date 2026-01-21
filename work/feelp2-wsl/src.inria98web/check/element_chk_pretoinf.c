/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   element_chk_pretoinf.c
 *      Date:   1993/11/19
 *   
 *   Purpose:   element構造体内のpre_to_infを実行
 *              
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../element/element.h"

void element_chk_pretoinf()
{
    int i,j;
    int elements;
    int scalars;
    int element_lets;
    Element *element_ptr;
    Expression *expr_ptr;
    Scalar *sc_ptr;

    elements = how_many_elements();
    
    for(i=0;i<elements;i++) {

	element_ptr = get_nth_element_ptr(i);

	scalars      = element_ptr -> scalar_vars;
	element_lets = element_ptr -> element_lets;
	
	sc_ptr = element_ptr -> scalar_var; /* ptrptrでない事に注意 */

	for(j=0;j<scalars;j++) {
	    if( (sc_ptr+j)->expr != NULL) {
		/* double変数で宣言のみの場合NULL */
		expr_ptr = (sc_ptr+j)->expr;
		pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
	    }
	}

	for(j=0;j<element_lets;j++) {
	    expr_ptr = *(element_ptr->let_expr + j);
	    pre_to_inf_push(expr_ptr->expr,&(expr_ptr->expr_inf));
	}
    }

    return;
}
