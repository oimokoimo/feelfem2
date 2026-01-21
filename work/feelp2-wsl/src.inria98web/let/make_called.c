/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_let_called.c
 *      Date:   1994/01/11
 *   
 *   Purpose:   let文のsubroutineでの呼び出されルーチンの記述
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"

void make_let_called( fp , let_no , let_ptr )
     FILE *fp;
     int   let_no;
     Let  *let_ptr;
{
    int i;

    char  *var_name;
    char  *var_name2;
    char **name_ptrptr;
    int    vars;
    

    F77("      subroutine ");
    PUT(fp,LET_NAME,let_no);
    F77("(feel,");
    XYZ_in_subroutine(fp);

    /* 代入先変数を書く */
    var_name = let_ptr->var_name;
    switch(get_var_kind(var_name)) {
      case FEM:
	F77(",");
	PUT(fp,FEM_VAR_NAME77,var_name);
	break;

      case EWISE:
	F77(",");
	PUT(fp,EWISE_VAR_NAME77,var_name);
	break;
	
      case DOUBLE:
      case INT:
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name);
	break;
	
      default:
	SystemAbort("変@make_let_called.c");
    }

    /* FEM変数 */
    vars = let_ptr -> fem_vars;
    name_ptrptr = let_ptr -> fem_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",");
	PUT(fp,FEM_VAR_NAME77,var_name2);
    }


    /* EWISE変数 */
    vars = let_ptr -> ew_vars;
    name_ptrptr = let_ptr -> ew_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",");
	PUT(fp,EWISE_VAR_NAME77,var_name2);
    }

    /* int変数 */
    vars = let_ptr -> int_vars;
    name_ptrptr = let_ptr -> int_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
    }


    /* dbl変数 */
    vars = let_ptr -> dbl_vars;
    name_ptrptr = let_ptr -> dbl_var_name;
    for(i=0;i<vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
    }

    /* おしまい */
    F77(")\n");

    return;
}


