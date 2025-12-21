/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_femvarinfo.c
 *      Date:   1993/11/23(祝)
 *   
 *   Purpose:   FEMvarinfo構造体を変数名から返すルーチン
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "solve_comp.h"

FEMvarinfo *get_femvarinfo( fem_var_name , fem_varinfo_ptrptr, fem_vars )
     char *fem_var_name;
     FEMvarinfo **fem_varinfo_ptrptr;
     int   fem_vars;
{
    int i;
    int find_flag;
    FEMvarinfo *fem_varinfo_ptr;

    find_flag = NO;

    for(i=0;i<fem_vars;i++) {
	
	fem_varinfo_ptr = *(fem_varinfo_ptrptr + i);

	if(streq(fem_varinfo_ptr->fem_var_name , fem_var_name)) {
	    return(fem_varinfo_ptr);
	}
    }

    SystemAbort("No specified fem_varinfo in ptrptr(get_femvarinfo)");
}
