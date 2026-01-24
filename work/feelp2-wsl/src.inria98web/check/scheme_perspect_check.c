/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_perspect_check.c
 *      Date:   1993/12/14
 *   
 *   Purpose:   perspect文をチェックし、要素番号を代入する
 *              
 *   Functions: 
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../scheme_comp/scheme_comp.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"
#include "../mesh_comp/mesh_comp.h"

void scheme_perspect_check()
{
    int i,j;
    int schemes;

    Scheme *scheme_ptr;

    FEM_var   *fem_var_ptr;
    FEM_type  *fem_type_ptr;

    Perspect   *p_ptr;
    Subdomain  *subdomain_ptr;

    schemes = how_many_schemes();
    
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != PERSPECT &&
	   scheme_ptr->type != PERSPECT_FILE ) continue;
	
	p_ptr = (Perspect *)scheme_ptr->ptr;


	/* subdomain 拡張 */
	if(p_ptr -> subdomain != NULL) {
	    subdomain_ptr = get_subdomain_ptr_by_name(p_ptr->subdomain);
	    if(subdomain_ptr == NULL) {
		SystemError_s("Subdomain %s specified in contour statement is not defined.",p_ptr->subdomain);
	    }
	}


	
	fem_var_ptr = get_fem_ptr_by_name( p_ptr -> var );
	if(fem_var_ptr == NULL) {
	    SystemError_yy_s("%s is not fem variable in perspect.",p_ptr->var,p_ptr->yylineno);
	    continue;
	}

	if(fem_var_ptr -> basis_types != 1) {
	    SystemError_s("multi-fem variable %s is not supported in perspect",p_ptr->var);
	    continue;
	}

	fem_type_ptr = fem_var_ptr -> fem_type_ptr[0];

	p_ptr -> domain_name = fem_type_ptr -> domain_name;
	p_ptr -> etype       = fem_type_ptr -> etype;

	if(p_ptr -> etype != TRI && p_ptr -> etype != RECT) {
	    SystemError_yy("PERSPECT variable is not on 2d element.",p_ptr->yylineno);
	}

    }
    return;
}

