/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scheme_showvec_check.c
 *      Date:   1993/12/14
 *   
 *   Purpose:   showvec文をチェックし、要素番号を代入する
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

void scheme_showvec_check()
{
    int i,j;
    int schemes;

    Scheme *scheme_ptr;

    FEM_var   *fem_var_ptr;
    FEM_type  *fem_type_ptr_x;
    FEM_type  *fem_type_ptr_y;

    Showvec   *s_ptr;
    Subdomain *subdomain_ptr;

    schemes = how_many_schemes();
    
    for(i=0;i<schemes;i++) {
	scheme_ptr = get_nth_scheme_struct(i);

	if(scheme_ptr->type != SHOWVEC &&
	   scheme_ptr->type != SHOWVEC_FILE ) continue;
	
	s_ptr = (Showvec *)scheme_ptr->ptr;

	/* subdomain 拡張 */
	if(s_ptr -> subdomain != NULL) {
	    subdomain_ptr = get_subdomain_ptr_by_name(s_ptr->subdomain);
	    if(subdomain_ptr == NULL) {
		SystemError_s("Subdomain %s specified in contour statement is not defined.",s_ptr->subdomain);
	    }
	}




	
	fem_var_ptr = get_fem_ptr_by_name( s_ptr -> x );
	if(fem_var_ptr == NULL) {
	    SystemError_yy_s("%s is not fem variable(showvec)",s_ptr->x,s_ptr->yylineno);
	    continue;
	}

	if(fem_var_ptr -> basis_types != 1) {
	    SystemError_s("showvec指定のfem変数 %s は複数domain定義の為、未対応",s_ptr->x);
	    continue;
	}

	fem_type_ptr_x = fem_var_ptr -> fem_type_ptr[0];

	fem_var_ptr = get_fem_ptr_by_name( s_ptr -> y );
	if(fem_var_ptr == NULL) {
	    SystemError_yy_s("%s is not fem variable.",s_ptr->y,s_ptr->yylineno);
	    continue;
	}

	if(fem_var_ptr -> basis_types != 1) {
	    SystemError_s("showvec指定のfem変数 %s は複数domain定義の為、未対応",s_ptr->y);
	    continue;
	}
	fem_type_ptr_y = fem_var_ptr -> fem_type_ptr[0];

	s_ptr -> domain_name = fem_type_ptr_x -> domain_name;
	if( s_ptr->domain_name != NULL && 
	   !streq(s_ptr->domain_name ,fem_type_ptr_y -> domain_name)) {

	    SystemError_yy("SHOWVEC指定の２変数の定義域が相違",
			   s_ptr->yylineno);
	    /* 実は意味ナイナ、これ */
	    continue;
	}
	
	s_ptr -> etype       = fem_type_ptr_x -> etype;

	if(s_ptr -> etype != TRI && s_ptr -> etype != RECT) {
	    SystemError_yy("SHOWVEC指定の変数が２次元要素上にない",s_ptr->yylineno);
	}

    }
    return;
}

