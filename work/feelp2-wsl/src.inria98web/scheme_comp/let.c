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

void Let_st()
{
    Let *let_ptr;

    let_ptr = (Let *)FEEL_GetMemory(sizeof(Let));

    let_ptr -> expr = get_expr_structure();
    let_ptr -> var_name  = PopString();

    let_ptr -> let_place = NORMAL_LET;
    let_ptr -> regions   = 0;
    let_ptr -> yylineno  = yylineno_info();
    
    store_scheme( LET , let_ptr );

/*    fprintf(stderr,"LET %s = %s\n",let_ptr -> var_name, let_ptr -> expr -> expr);
*/

    return;
}


void Let_at_st(parameters)
     int parameters;
{
    int i;
    char **region_name;

    Let *let_ptr;

    region_name = (char **)FEEL_GetMemory(sizeof(char *) * parameters);
    let_ptr = (Let *)FEEL_GetMemory(sizeof(Let));
    
    for(i=0;i<parameters;i++) {
	*(region_name+i) = PopString();
    }
    
    let_ptr -> regions     = parameters;
    let_ptr -> region_name = region_name;
    let_ptr -> expr = get_expr_structure();
    let_ptr -> var_name  = PopString();

    let_ptr -> let_place = LET_AT;
    let_ptr -> yylineno  = yylineno_info();

    /* DBG */
/*    fprintf(stderr,"LET %s = %s ",let_ptr -> var_name, let_ptr -> expr -> expr);

    fprintf(stderr,"at %s",*region_name);
    for(i=1;i<parameters;i++) {
	fprintf(stderr,",%s",*(region_name + i));
    }
    fprintf(stderr,"\n");
*/
	
    
    store_scheme( LET , let_ptr );

    return;
}

void Let_on_st(parameters)
     int parameters;
{
    int i;
    char **region_name;

    Let *let_ptr;

    region_name = (char **)FEEL_GetMemory(sizeof(char *) * parameters);
   let_ptr = (Let *)FEEL_GetMemory(sizeof(Let));

    for(i=0;i<parameters;i++) {
	*(region_name+i) = PopString();
    }
    
    let_ptr -> regions     = parameters;
    let_ptr -> region_name = region_name;
    let_ptr -> expr = get_expr_structure();
    let_ptr -> var_name  = PopString();

    let_ptr -> let_place = LET_ON;
    let_ptr -> yylineno  = yylineno_info();

    /* DBG */
/*
    fprintf(stderr,"LET %s = %s ",let_ptr -> var_name,let_ptr -> expr -> expr);
    fprintf(stderr,"on %s",*region_name);
    for(i=1;i<parameters;i++) {
	fprintf(stderr,",%s",*(region_name + i));
    }
    fprintf(stderr,"\n");
*/

	
    
    store_scheme( LET , let_ptr );

    return;
}

void Let_in_st(parameters)
     int parameters;
{
    int i;
    char **region_name;

    Let *let_ptr;

    region_name = (char **)FEEL_GetMemory(sizeof(char *) * parameters);
   let_ptr = (Let *)FEEL_GetMemory(sizeof(Let));

    for(i=0;i<parameters;i++) {
	*(region_name+i) = PopString();
    }
    
    let_ptr -> regions     = parameters;
    let_ptr -> region_name = region_name;
    let_ptr -> expr = get_expr_structure();
    let_ptr -> var_name  = PopString();

    let_ptr -> let_place = LET_IN;
    let_ptr -> yylineno  = yylineno_info();

    /* DBG */
/*    fprintf(stderr,"LET %s = %s ",let_ptr -> var_name,let_ptr -> expr -> expr);
    fprintf(stderr,"in %s",*region_name);
    for(i=1;i<parameters;i++) {
	fprintf(stderr,",%s",*(region_name + i));
    }
    fprintf(stderr,"\n");
*/

    
    store_scheme( LET , let_ptr );

    return;
}

