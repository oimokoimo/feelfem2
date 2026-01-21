/*
 * FEEL system Prototype Version 2
 * 
 * File     scheme_block.c
 * Made     1992/09/18
 * Modified 
 * Version  0.0
 *
 * Purpose:
 *
 */

#include "../feel_def/feel_def.h"
#include "scheme_comp.h"

static int   schemes = 0;

static Scheme scheme[MAX_SCHEMES];


/*  schemeブロックの各情報をストアする */
 
void store_scheme( type , ptr )
     int   type;                   /* スキームタイプ */
     char *ptr;                    /* 構造体へのポインタ */
{

    if(schemes == MAX_SCHEMES -1 ) {
	SystemError("Too many FEEL scheme schemes.");
	return;
    }

    scheme[schemes].type = type;
    scheme[schemes].ptr  =  ptr;

    schemes++;

    return;
}


int how_many_schemes()
{
    return(schemes);
}


Scheme *get_nth_scheme_struct( n )
     int n;
{

    if(n < 0 || n >= schemes ) {
	SystemAbort("INNER ERROR : Illegal scheme number(get_nth_scheme_struct)");
    }
    
    return( &(scheme[n]) );
}

    

