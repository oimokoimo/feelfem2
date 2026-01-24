 /*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   fem_var_element_check.c
 *      Date:   1993/06/29
 *   
 *   Purpose:   各FEM_type構造体のelementタイプのdefined or notの確認と
 *              shape番号への代入
 */

#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../var_comp/var_comp.h"
#include "../element/element.h"
#include "../system/system.h"


/*  tree図
 *
 *  |-feel_data_check  [check.c]
 *  |      |
 *  |      |-fem_var_element_check()
 *
 *  FEM_type 構造体の完成
 *
 *    check:  FEM_type->type(内挿関数名が定義されていなければerror)
 *    FEM_type -> etype の代入
 *
 */

fem_var_element_check()
{
    int i,j;
    int types;
    int domains;

    Element *element_ptr;
    FEM_type *fem_type_ptr;

    types = how_many_fem_types();
    domains = how_many_domains();

    for(i=0;i<types;i++) {
	fem_type_ptr = get_nth_fem_type_ptr(i);

	element_ptr = get_element_ptr_by_name( fem_type_ptr -> type );

	if(element_ptr == NULL) { /* NOT DEFINED */
	    
	    if(english_mesg) {
		SystemError_ss("element type %s for fem variable %s is not defined.",fem_type_ptr->type,fem_type_ptr->name);
	    }
	    else {
		SystemError_ss("FEM変数%sに指定されている要素%sは未定義",
			       fem_type_ptr->name,fem_type_ptr->type);
	    }

	    fem_type_ptr -> etype = UNDEFINED;

	    continue;
	}

	/* 複数domain時に定義domainが指定されていない */
	if(domains != 1 && fem_type_ptr->domain_name == NULL) {

	    if(english_mesg) {
		SystemError_yy_s("No domain name is not spcified for FEM variable %s.",fem_type_ptr->name,fem_type_ptr->yylineno);
	    }
	    else {
		SystemError_yy_s("fem変数 %s に対するdomainが陽に指定されていない",
				 fem_type_ptr->name,fem_type_ptr->yylineno);
	    }

	}

	fem_type_ptr -> etype = element_ptr -> etype;
    }

    return;
}







