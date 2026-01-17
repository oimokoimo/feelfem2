/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   is_expr_eq.c
 *      Date:   1993/08/23
 *   
 *   Purpose:   Expression の数式の内容が文字列として同一かどうかを
 *              判定する。
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

is_expr_eq( a , b )
     Expression *a,*b;
{
    if(streq(a->expr , b->expr)) return(YES);
    else                         return( NO);
}

