/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_elem_name_by_ND.c
 *      Date:   1993/10/26
 *   
 *   Purpose:   名前と領域名から、基底関数名を返す
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "var_comp.h"

char *get_elem_name_by_ND( name , domain_name)
     char *name;  /* fem変数名 */
     char *domain_name;  /* 領域名 */
{
    int i,types;
    
    FEM_var   *fem_var_ptr;
    FEM_type  *fem_type_ptr;

    fem_var_ptr = get_fem_ptr_by_name( name );

    types = fem_var_ptr -> basis_types;

    if(types != 1) SystemAbort("Oh my god in get_elem_name_by_ND");
    fem_type_ptr = fem_var_ptr -> fem_type_ptr[0];
    return(fem_type_ptr -> type);

    /* dbg: CAUTION: 現在 doamin_nameによるチェックなし！！！！！

    for(i=0;i<types;i++) {
	fem_type_ptr = fem_var_ptr -> fem_type_ptr[i];

	if(streq(domain_name, fem_type_ptr->domain_name)) {
	    return( fem_type_ptr -> type );
	}
    }

    SystemAbort("NOT FOUND error (get_elem_name_by_ND(make_elem_lisp))");

    */

}
