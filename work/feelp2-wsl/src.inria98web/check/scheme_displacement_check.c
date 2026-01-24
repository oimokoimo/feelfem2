/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_displacement_check.c
 *      Date:   1993/12/14
 *   
 *   Purpose:   displacement文をチェックし、要素番号を代入する
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

void scheme_displacement_check()
{
    int i,j;
    int schemes;

    Scheme *scheme_ptr;

    FEM_var   *fem_var_ptr;
    FEM_type  *fem_type_ptr;

    Displacement   *c_ptr;
    Subdomain *subdomain_ptr;

    schemes = how_many_schemes();
    
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != DISPLACEMENT &&
	   scheme_ptr->type != DISPLACEMENT_FILE ) continue;
	
	c_ptr = (Displacement *)scheme_ptr->ptr;
	
	/* subdomain 拡張 */
	if(c_ptr -> subdomain != NULL) {
	    subdomain_ptr = get_subdomain_ptr_by_name(c_ptr->subdomain);
	    if(subdomain_ptr == NULL) {
		SystemError_s("Subdomain %s specified in contour statement is not defined.",c_ptr->subdomain);
	    }
	}


	/* u_var の検査 */
	fem_var_ptr = get_fem_ptr_by_name( c_ptr -> u_var );
	if(fem_var_ptr == NULL) {

	    if(english_mesg) {
		SystemError_yy_s("%s is not a FEM variable in displacement sentence.",c_ptr->u_var,c_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("displacement指定の変数 %s はfem変数ではない",c_ptr->u_var,c_ptr->yylineno);
	    }

	    continue;
	}
	if(fem_var_ptr -> basis_types != 1) {

	    if(english_mesg) {
		SystemError_s("FEM variable %s with many domains is future function for displacement sentence.",c_ptr->u_var);
	    }
	    else {
		SystemError_s("displacement指定のfem変数 %s は複数domain定義の為、未対応",c_ptr->u_var);
	    }

	    continue;
	}

	/* v_var の検査 */
	fem_var_ptr = get_fem_ptr_by_name( c_ptr -> v_var );

	if(fem_var_ptr == NULL) {

	    if(english_mesg) {
		SystemError_yy_s("%s is not a FEM variable in displacement sentence.",c_ptr->v_var,c_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("displacement指定の変数 %s はfem変数ではない",c_ptr->v_var,c_ptr->yylineno);
	    }

	    continue;
	}
	if(fem_var_ptr -> basis_types != 1) {

	    if(english_mesg) {
		SystemError_s("FEM variable %s with many domains is future function for displacement sentence.",c_ptr->v_var);
	    }
	    else {
		SystemError_s("displacement指定のfem変数 %s は複数domain定義の為、未対応",c_ptr->v_var);
	    }

	    continue;
	}

	/* p_var の検査 */
	if(c_ptr->p_var != NULL) {
	    fem_var_ptr = get_fem_ptr_by_name( c_ptr -> p_var );
	    if(fem_var_ptr == NULL) {

		if(english_mesg) {
		    SystemError_yy_s("%s is not a FEM variable in displacement sentence.",c_ptr->p_var,c_ptr->yylineno);
		}
		else {
		    SystemError_yy_s("displacement指定の変数 %s はfem変数ではない",c_ptr->p_var,c_ptr->yylineno);
		}

		continue;
	    }

	    if(fem_var_ptr -> basis_types != 1) {
		
		if(english_mesg) {
		    SystemError_s("FEM variable %s with many domains is future function for displacement.",c_ptr->p_var);
		}
		else {
		    SystemError_s("displacement指定のfem変数 %s は複数domain定義の為、未対応",c_ptr->p_var);
		}

		continue;
	    }
        }

	fem_type_ptr = fem_var_ptr -> fem_type_ptr[0];

	c_ptr -> domain_name = fem_type_ptr -> domain_name;
	c_ptr -> etype       = fem_type_ptr -> etype;

	if(c_ptr -> etype != TRI && c_ptr -> etype != RECT) {
	    if(english_mesg) {
		SystemError_yy("Variables in displacement sentence is not 2-dimensional.",c_ptr->yylineno);
	    }
	    else {
		SystemError_yy("DISPLACEMENT指定の変数が２次元要素上にない",c_ptr->yylineno);
	    }

	}

    }
    return;
}

