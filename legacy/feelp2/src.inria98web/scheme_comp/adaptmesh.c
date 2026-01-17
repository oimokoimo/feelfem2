/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   adaptmesh.c
 *      Date:   1997/06/26
 *              1999/03/15 how_many_adaptmesh()  for AVS version
 *   
 *   Purpose:   adaptmeth parser
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

static int adaptmesh_statements = 0;

void parse_adaptmesh()
{
    Adaptmesh *adaptmesh_ptr;

    adaptmesh_ptr = (Adaptmesh *)FEEL_GetMemory(sizeof(Adaptmesh));

    adaptmesh_ptr -> expr      = get_expr_structure();
    adaptmesh_ptr -> option    = NULL;

    adaptmesh_ptr -> yylineno  = yylineno_info();
    
    store_scheme( ADAPTMESH , adaptmesh_ptr );

    adaptmesh_statements++;

    return;
}

void parse_adaptmesh_with_option()
{
    Adaptmesh *adaptmesh_ptr;

    adaptmesh_ptr = (Adaptmesh *)FEEL_GetMemory(sizeof(Adaptmesh));

    adaptmesh_ptr -> expr      = get_expr_structure();
    adaptmesh_ptr -> option    = PopString();

    adaptmesh_ptr -> yylineno  = yylineno_info();
    
    store_scheme( ADAPTMESH , adaptmesh_ptr );

    adaptmesh_statements++;

    return;
}


int how_many_adaptmesh()
{
  return(adaptmesh_statements);
}
