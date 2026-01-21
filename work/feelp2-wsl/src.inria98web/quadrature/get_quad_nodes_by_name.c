/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_quad_nodes_by_name.c
 *      Date:   1993/10/28
 *   
 *   Purpose:   数値積分法の名前から積分点数を返す
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "quadrature.h"

int get_quad_nodes_by_name( name )
     char *name;
{
    Quadrature *quad_ptr;

    quad_ptr = get_quadrature_ptr_by_name ( name );

    return( quad_ptr -> nodes);
}
