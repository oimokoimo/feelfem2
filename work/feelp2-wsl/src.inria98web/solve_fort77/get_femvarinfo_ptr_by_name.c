/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_femvarinfo_ptr_by_name.c
 *      Date:   1994/02/07
 *   
 *   Purpose:   FEMvarinfo構造体を返す  引き数は便利だよ
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

FEMvarinfo *get_femvarinfo_ptr_by_name( name , solve_element_ptr )
     char *name;                          /* 変数名             */
     SolveElement *solve_element_ptr;     /* SolveElement構造体 */
{
    int i;
    ElementFORT77 *elem77_ptr;
    FEMvarinfo    *fem_varinfo_ptr; 
    FEMvarinfo   **fem_varinfo_ptrptr;
    
    elem77_ptr = solve_element_ptr->elem77_dat;
    fem_varinfo_ptrptr = elem77_ptr -> fem_var_info_ptrptr;
    
    for(i=0;i<elem77_ptr->fem_vars;i++) {
	fem_varinfo_ptr = *(fem_varinfo_ptrptr+i);
	
	if(streq(name, fem_varinfo_ptr->fem_var_name)) {
	    return(fem_varinfo_ptr);
	}
    }

    fprintf(stderr,"fem var %s\n",name);
    SystemAbort("Cannot find FEMvarinfo pointer");
}
