/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   let.c
 *      Date:   1993/12/17
 *   
 *   Purpose:   代入文のparser
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

void L2_norm() 
{
    Parse_norm(L2NORM);
    return;
}


void MAX_norm()
{
    Parse_norm(MAXNORM);
    return;
}


void Parse_norm( norm_type)
     int norm_type;
{
    Norm *norm_ptr;

    norm_ptr = (Norm *)FEEL_GetMemory(sizeof(Norm));

    norm_ptr -> expr      = get_expr_structure();
    norm_ptr -> var_name  = PopString();

    norm_ptr -> norm_type = norm_type;
    norm_ptr -> yylineno  = yylineno_info();
    
    store_scheme( NORM , norm_ptr );

    return;
}
