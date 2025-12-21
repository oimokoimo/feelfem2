/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_main_adapt_call.c
 *      Date:   1997/07/25
 *   
 *   Purpose:   adapt calling sequence in main routine
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"

void make_main_adapt_call( fp , adapt_no , adapt_ptr )
     FILE *fp;
     int   adapt_no;
     Adaptmesh  *adapt_ptr;
{
    int i;

    char  *var_name2;
    char **name_ptrptr;
    int    vars;
    
    
    F77("      call ");
    PUT(fp,ADAPTMESH_NAME,adapt_no);
    F77("(feel,");
    XYZ_in_call(fp);


    /* FEM変数 */
    vars = adapt_ptr -> fem_vars;
    name_ptrptr = adapt_ptr -> fem_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);


	F77(",feel(");
	PUT(fp,NP_FEM_VAR,var_name2);
	F77(")");
    }


    /* EWISE変数 */
    vars = adapt_ptr -> ew_vars;
    name_ptrptr = adapt_ptr -> ew_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);


	F77(",feel(");
	PUT(fp,NP_EWISE_VAR,var_name2);
	F77(")");
    }

    /* int変数 */
    vars = adapt_ptr -> int_vars;
    name_ptrptr = adapt_ptr -> int_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);


	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
    }


    /* dbl変数 */
    vars = adapt_ptr -> dbl_vars;
    name_ptrptr = adapt_ptr -> dbl_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);


	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
    }

    /* おしまい */
    F77(")\n");
    return;
}

