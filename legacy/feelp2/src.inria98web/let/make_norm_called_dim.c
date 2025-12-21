/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_norm_called_dimension.c
 *      Date:   1994/01/11
 *   
 *   Purpose:   norm文のsubroutineでの呼び出されルーチンでのdimension文
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../var_comp/var_comp.h"

void make_norm_called_dimension( fp , norm_no , norm_ptr )
     FILE *fp;
     int   norm_no;
     Norm  *norm_ptr;
{
    int i;

    char  *var_name;
    char  *var_name2;
    char **name_ptrptr;

    EWISE_type *ewise_type_ptr;
    int    vars;
    
    COM;

    F77("      real*4 feel(*)\n");
    
    XYZ_dimension(fp);

    /* 代入先変数dimensionを書く */
    var_name = norm_ptr->var_name;
    switch(get_var_kind(var_name)) {
      case FEM:
	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,var_name);
	F77("(*)\n");
	break;

      case EWISE:
	ewise_type_ptr = get_ewise_type_ptr_by_name(var_name);
	F77("      dimension ");
	PUT(fp,EWISE_VAR_NAME77,var_name);
	if(ewise_type_ptr -> points == 1) {
	    F77("(*)\n");
	}
	else {
	    PUT(fp,"(%d,*)\n",ewise_type_ptr->points);
	}
	break;
	
      case INT:
	F77("      integer ");
	PUT(fp,SCALAR_VAR_NAME77,var_name);
	F77("\n");
	break;
	
      default:
	break;
    }

    /* FEM変数 */
    vars = norm_ptr -> fem_vars;
    name_ptrptr = norm_ptr -> fem_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,var_name2);
	F77("(*)\n");
    }


    /* EWISE変数 */
    vars = norm_ptr -> ew_vars;
    name_ptrptr = norm_ptr -> ew_var_name;
    for(i=0;i< vars ;i++) {
	var_name2 = *(name_ptrptr+i);
	ewise_type_ptr = get_ewise_type_ptr_by_name(var_name2);

	if(streq(var_name,var_name2)) continue;  /* パス */

	F77("      dimension ");
	PUT(fp,EWISE_VAR_NAME77,var_name2);
	if(ewise_type_ptr->points == 1) {
	    F77("(*)\n");
	}
	else {
	    PUT(fp,"(%d,*)\n",ewise_type_ptr->points);
	}
    }

    /* int変数 */
    vars = norm_ptr -> int_vars;
    name_ptrptr = norm_ptr -> int_var_name;
    for(i=0;i < vars;i++) {
	var_name2 = *(name_ptrptr+i);

	if(streq(var_name,var_name2)) continue;  /* パス */
	F77("      integer ");
	PUT(fp,SCALAR_VAR_NAME77,var_name2);
	F77("\n");
    }

    return;
}


