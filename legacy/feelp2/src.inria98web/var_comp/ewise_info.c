/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   ewise_info.c
 *      Date:   1993/10/28
 *   
 *   Purpose:   ewise変数に関する情報提供関数群
 *   Functions: int get_ewise_nodes( name , domain_name )  ewise配列の大きさ
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "var_comp.h"

/* ewise変数名、指定domain名からewise変数の要素内節点数を返す */
int get_ewise_nodes( name ,domain_name )
     char *name;
     char *domain_name;
{
    int i;
    int types;

    EWISE_var  *ewise_var_ptr;
    EWISE_type *ewise_type_ptr;

    ewise_var_ptr = get_ewise_ptr_by_name(name);
    types = ewise_var_ptr -> ewise_types;

    for(i=0;i<types;i++) {
	ewise_type_ptr = ewise_var_ptr->ewise_type_ptr[i];
	if(streq(domain_name,ewise_type_ptr ->domain_name)) {
	    return(ewise_type_ptr -> points );
	}
    }

    SystemAbort("NOT MATCH EWISE NAME AND DOMAIN (get_ewise_nodes)");
}

    
     
