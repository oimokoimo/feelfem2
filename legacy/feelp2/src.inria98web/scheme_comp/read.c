/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   read.c
 *      Date:   1993/06/28
 *   
 *   Purpose:   read文の処理
 *   Functions: 
 *              
 *              
 */

#include "../system/system.h"
#include "scheme_comp.h"
                                  
static int   read_args;       /* 一つのread文に現れる引き数の数 */

static Expression *read_expr[MAX_RW_ARGS];

Read_st(parameters)
     int parameters;
{
    int i;
    Read  *read_struct;
    char **var_name;

    read_struct = (Read *)FEEL_GetMemory(sizeof(Read));
    
    read_struct ->args = parameters;;

    var_name = (char **)FEEL_GetMemory(sizeof(char *)* parameters);
    
    for(i=0;i<parameters;i++) {
	*(var_name+parameters-i-1) = PopString();
    }

    read_struct ->var_name= var_name;

    read_struct ->yylineno = yylineno_info();

    store_scheme( READ , read_struct);

    return;

}
