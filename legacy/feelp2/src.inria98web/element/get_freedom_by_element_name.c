/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_freedom_by_element_name.c
 *      Date:   1993/10/26
 *   
 *   Purpose:   与えられた要素の名前から自由度を返す
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "element.h"

int get_freedom_by_element_name( name )
     char *name;
{
    Element *elem_ptr;

    elem_ptr = get_element_ptr_by_name( name );
    
    /* 基底関数の数が自由度の数 */
    return( elem_ptr -> basis );
}

