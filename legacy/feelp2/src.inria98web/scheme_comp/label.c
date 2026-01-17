/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   label.c
 *      Date:   1993/06/22
 *   
 *   Purpose:   label文の構文解析
 *   Functions: 
 *              
 *              
 */

#include "../system/system.h"
#include "scheme_comp.h"

Label_st() 
{
    Label *label_struct;

    label_struct = (Label *)FEEL_GetMemory( sizeof(Label) );

    label_struct -> line_no = 0;
    label_struct -> label   = PopString();

    label_struct -> yylineno  = yylineno_info();

    store_scheme( LABEL , label_struct );

    return;

}

int get_label_lineno( name )
     char *name;
{
    int i,schemes;
    Scheme *scheme_ptr;
    Label  *label_ptr;

    schemes = how_many_schemes();
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);
	if(scheme_ptr->type != LABEL) continue;
	label_ptr = (Label *)scheme_ptr->ptr;
	if(streq(name,label_ptr->label)) {
	    return(label_ptr -> line_no);
	}
    }
    return(0);   /* 0 means ERROR */
}
