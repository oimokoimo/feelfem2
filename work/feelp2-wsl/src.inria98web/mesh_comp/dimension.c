/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   dimension.c
 *      Date:   1993/07/05
 *   
 *   Purpose:   dimension文の解釈(デフォルトは２次元)
 *   Functions: 
 *              
 *              
 */
#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../feel_def/feel_msg.h"

static int dim = DEFAULT_DIMENSION;
extern int feel_dim;

what_dimension()
{

    return(dim);
}

dimension_st()
{
    dim = PopInt();

    if(dim < 1 || dim >3 ) {
	if(english_mesg) {
	    SystemError_yy("Illegal dimension definition",yylineno_info());
	}
	else {
	    SystemError_yy("空間次元の指定に誤りがあります。",yylineno_info());
	}

	return;
    }
    if(dim == 3) {
	if(english_mesg) {
	    SystemAbort("3 dimensional problem is not available now.");
	}
	else {
	    SystemAbort("三次元にはまだ対応していません");
	}

    }
    feel_dim = dim;

    return;
}
