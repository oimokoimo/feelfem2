/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   etype_dimension.c
 *      Date:   1993/08/23
 *   
 *   Purpose:   etype に相当する次元を返す
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

int etype_dimension( etype )
     int etype;
{

    switch(etype) {

      case LINE:
	return(1);
	
      case TRI:
      case RECT:
	return(2);

      case CUBE:
      case TETRA:
	return(3);
	
      default:
	break;
    }

    return(0);   /* これはエラーを意味する */
}
