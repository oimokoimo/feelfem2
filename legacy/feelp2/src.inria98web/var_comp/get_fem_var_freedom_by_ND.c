/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_fem_var_freedom_by_ND.c
 *      Date:   1993/11/08
 *   
 *   Purpose:   fem変数の名前、domain名から要素内自由度を返す
 *   
 *   使用場所   make_ecalルーチン
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "var_comp.h"
#include "../element/element.h"

int get_fem_var_freedom_by_ND( var_name , domain_name )
     char *var_name;
     char *domain_name;
{
    char *element_name;
    
    element_name = get_elem_name_by_ND( var_name, domain_name );

    return(get_freedom_by_element_name( element_name ));
}




