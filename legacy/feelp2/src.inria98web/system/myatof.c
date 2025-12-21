/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   myatof.c
 *      Date:   1994/02/03
 *   
 *   Purpose:   atof¤Î¼«²ÈÀ½
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

double myatof( string )
     char *string;
{
    double ret;

    sscanf(string,"%lf",&ret);

    return(ret);
}
