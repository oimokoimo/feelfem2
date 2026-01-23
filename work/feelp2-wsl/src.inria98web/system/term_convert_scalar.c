/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   scalar_term_convert.c
 *      Date:   1994/01/27
 *   
 *   Purpose:   スカラー変数に関するterm_convertを作成する
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../var_comp/var_comp.h"

static int     scalars;
static char  **sc_from;
static char  **sc_to;

void init_scalar_term_convert()
{
    int i,ptr;
    Var *var_ptr;

    char buf[BUFSIZ];    /* bug fixed on 2026/01/23 */

    scalars  = how_many_int_vars();
    scalars += how_many_double_vars();
    scalars += how_many_const_vars();

    if(scalars == 0) return;

    sc_from = (char **)FEEL_GetMemory(sizeof(char *) * scalars);
    sc_to   = (char **)FEEL_GetMemory(sizeof(char *) * scalars);


    ptr = 0;

    /* int 型 */
    for(i=0;i<how_many_int_vars();i++) {
	var_ptr = get_nth_int_ptr(i);

	sprintf(buf,SCALAR_VAR_NAME77,var_ptr -> name);
	*(sc_from+ptr) = var_ptr -> name;
	*(sc_to  +ptr) = MakeStringCopy(buf);

	ptr++;
    }

    /* double 型 */
    for(i=0;i<how_many_double_vars();i++) {
	var_ptr = get_nth_double_ptr(i);

	sprintf(buf,SCALAR_VAR_NAME77,var_ptr -> name);
	*(sc_from+ptr) = var_ptr -> name;
	*(sc_to  +ptr) = MakeStringCopy(buf);

	ptr++;
    }

    /* const型 */
    for(i=0;i<how_many_const_vars();i++) {
	var_ptr = get_nth_const_ptr(i);

	sprintf(buf,SCALAR_VAR_NAME77,var_ptr -> name);
	*(sc_from+ptr) = var_ptr -> name;
	*(sc_to  +ptr) = MakeStringCopy(buf);
	ptr++;
    }
    
/*    for(i=0;i<scalars;i++) {
	fprintf(stderr,"%s -> %s\n",*(sc_from+i),*(sc_to+i));
    }
*/

    return;
}

char *term_convert_scalar( expr )
     char *expr;
{

    if(scalars == 0) return(expr);

    return(term_convert( expr , sc_from, sc_to , scalars));
}


    

