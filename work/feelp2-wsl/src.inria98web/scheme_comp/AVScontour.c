/*
 * FEEL system Prototype Version 2
 * 
 * File     AVScontour.c
 * Made     1992/09/21
 * Modified 
 * Version  0.0
 *
 * Purpose: avs_contour statement
 *
 */

#include "../system/system.h"
#include "scheme_comp.h"
#include "../feel_def/feel_msg.h"


void AVScontour_st() 
{
    char    *var;
    AVScontour *AVScontour_struct;

    var = PopString();


    if(get_var_kind(var) != FEM) {
	SystemError_yy_s("[AVScontour] %s is not a fem variable.",var,yylineno_info());
	FEEL_FreeMemory(var);
	return;
    }

    AVScontour_struct = (AVScontour *)FEEL_GetMemory( sizeof(AVScontour) );

    AVScontour_struct -> var  = var;

    AVScontour_struct -> yylineno  = yylineno_info();

    store_scheme( AVS_CONTOUR , AVScontour_struct);

    return;

}
