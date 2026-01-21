/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   if文処理
 *      Date:   1994/02/08
 *   
 *   Purpose:   if文の処理を行う
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "scheme_comp.h"

/*===================*/
/* if(.... ) then 文 */
/*===================*/
void p_if_then( left_expr_ptr, type )  
     Expression *left_expr_ptr;
     int type;
{
    IFblock *if_struct;

    if_struct = (IFblock *)FEEL_GetMemory( sizeof(IFblock) );

    if_struct->iftype = IF_THEN;
    if_struct->condition_type = type;

    if_struct -> right   = get_expr_structure();
    if_struct -> left    = left_expr_ptr;
    
    if_struct -> yylineno  = yylineno_info();

    store_scheme( IF_THEN , if_struct );

    return;

}


/*===================*/
/* if(.... ) goto 文 */
/*===================*/
void p_if_goto( left_expr_ptr,type )  
     Expression *left_expr_ptr;
     int type;
{
    IFblock *if_struct;

    if_struct = (IFblock *)FEEL_GetMemory( sizeof(IFblock) );

    if_struct->iftype = IF_GOTO;
    if_struct->condition_type = type;

    if_struct -> label   = PopString();
    if_struct -> right   = get_expr_structure();
    if_struct -> left    = left_expr_ptr;

    if_struct -> yylineno  = yylineno_info();

    store_scheme( IF_GOTO , if_struct );

/*    fprintf(stderr,"if_goto %s %d %s  goto %s\n",if_struct->left,type,if_struct->right,if_struct->label); */

    return;

}

/*===================*/
/* else 文           */
/*===================*/
void p_else(  )  
{
    IFblock *if_struct;

    if_struct = (IFblock *)FEEL_GetMemory( sizeof(IFblock) );

    if_struct->iftype = ELSE;

    if_struct -> yylineno  = yylineno_info();

    store_scheme( ELSE , if_struct );

    return;

}


/*===================*/
/* endif文           */
/*===================*/
void p_endif( )  
{
    IFblock *if_struct;

    if_struct = (IFblock *)FEEL_GetMemory( sizeof(IFblock) );

    if_struct->iftype = ENDIF;
    if_struct -> yylineno  = yylineno_info();

    store_scheme( ENDIF , if_struct );

    return;

}

