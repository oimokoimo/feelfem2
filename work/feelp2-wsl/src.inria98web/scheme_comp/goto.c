/*
 * FEEL system Prototype Version 2
 * 
 * File     goto.c
 * Made     1992/09/21
 * Modified 
 * Version  0.0
 *
 * Purpose: goto statement
 *
 */

#include "../feel_def/feel_msg.h"
#include "../system/system.h"
#include "scheme_comp.h"

void Goto_st() 
{
    Goto *goto_struct;

    goto_struct = (Goto *)FEEL_GetMemory( sizeof(Goto) );
    

    goto_struct -> line_no = 0;
    goto_struct -> label   = PopString();

    goto_struct -> yylineno   = yylineno_info();

    store_scheme( GOTO , goto_struct );

    return;

}

