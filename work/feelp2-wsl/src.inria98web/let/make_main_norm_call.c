/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_main_norm_call.c
 *      Date:   1994/01/11
 *   
 *   Purpose:   norm文のmainルーチンでの呼び出しを作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"

void make_main_norm_call( fp , norm_no , norm_ptr )
     FILE *fp;
     int   norm_no;
     Norm  *norm_ptr;
{
    int i;

    char  *var_name;
    char  *var_name2;
    char **name_ptrptr;
    int    vars;
    
    
    F77("      call ");
    PUT(fp,NORM_NAME,norm_no);
    F77("(feel,");
    XYZ_in_call(fp);

    /* 代入先変数を書く */
    var_name = norm_ptr->var_name;
    switch(get_var_kind(var_name)) {
      case FEM:
	F77(",feel(");
	PUT(fp,NP_FEM_VAR,var_name);
	F77(")");
	break;

      case EWISE:
	F77(",feel(");
	PUT(fp,NP_EWISE_VAR,var_name);
	F77(")");
	break;
	
      case DOUBLE:
      case INT:
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name);
	break;
	
      default:
	SystemAbort("変@make_main_norm_call.c");
    }

    /* FEM変数 */
    vars = norm_ptr -> fem_vars;
    name_ptrptr = norm_ptr -> fem_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",feel(");
	PUT(fp,NP_FEM_VAR,var_name2);
	F77(")");
    }


    /* EWISE変数 */
    vars = norm_ptr -> ew_vars;
    name_ptrptr = norm_ptr -> ew_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",feel(");
	PUT(fp,NP_EWISE_VAR,var_name2);
	F77(")");
    }

    /* int変数 */
    vars = norm_ptr -> int_vars;
    name_ptrptr = norm_ptr -> int_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
    }


    /* dbl変数 */
    vars = norm_ptr -> dbl_vars;
    name_ptrptr = norm_ptr -> dbl_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
    }

    /* おしまい */
    F77(")\n");
    return;
}


