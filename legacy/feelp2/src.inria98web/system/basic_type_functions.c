/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   basic_type_functions.c
 *      Date:   1993/09/10
 *   
 *   Purpose:   基本的な構造体の比較などの関数群
 *              
 *   Functions: frac_neq(r,s) Frac r,sが等しくなければTRUE、等しければ FALSE
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


frac_neq( a , b)
     Frac a,b;
{
    if(a.bunsi * b.bunbo  != b.bunsi * a.bunbo ) {
	return(YES);
    }
    else {
	return(NO);
    }
}
