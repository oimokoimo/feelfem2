/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : isSystemVariable.cpp
 *  Date     : 2001/12/25
 *  Modified : 
 *  
 *  Purpose  : Judge system variables or not.  (SYSTEM inner use)
 *  
 *  vertex node       :  format  "x_%d" "y_%d" "z_%d"
 *  normal vector     :  NAME_NORMAL_X,...
 *  tangential vector : NAME_TANGENTIAL_X_2D, ...
 *                      NAME_TANGENTIAL_X_3D1, ...
 *  
 *  
 *  
 *  int isVertexVar(int etype,const char *nm)  
 *  -----------------------------------------
 *  if no  : return 0
 *         : return -1 (out of range)
 *  if yes : return %d (Node number)
 *  -----------------------------------------
 *                                             
 *                                             
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 *  
 */
#include <iostream>
#include "feeldef.hpp"


// 0 NO  -1 ERR  1-19 YES...
int isVertexVar(int etype, const char *varName)
{
  // starting with neither x nor y nor z
  if(*varName != 'x' && *varName != 'y' && *varName != 'z') {
    return (0);
  }

  // second character is not '_'
  if(*(varName+1) != '_') {
    return(0);
  }

  // with one digit, second character is not digit
  // currently, x0,y0,z0 are not used.
  if(*(varName+2) < '1' || *(varName+2) > '9') {
    return(0);
  }

  // with one digit variable
  if(*(varName+3) == '\0') {
    switch( etype ) {

    case ELEMENT_TYPE_LINE:
      // dimension check
      if( *varName == 'y' || *varName == 'z') {
	return(-1);
      }

      // line has x1,y1,x2,y2
      if( *(varName+1) != '1' && *(varName+1) != '2' ) {
	return(-1);
      }
      
      return(*(varName+1) - '0');
      

    case ELEMENT_TYPE_TRI:
      // dimension check
      if( *varName == 'z') {
	return(-1);
      }

      // line has x1,y1,x2,y2,x3,y3
      if( *(varName+2) != '1' && *(varName+2) != '2'  &&
	  *(varName+2) != '3'                            ) {
	return(-1);
      }
      
      return(*(varName+1) - '0');
      break;

    case ELEMENT_TYPE_RECT:
      // dimension check
      if( *varName == 'z') {
	return(-1);
      }

      // line has x1,y1,x2,y2,x3,y3
      if( *(varName+2) != '1' && *(varName+2) != '2'  &&
	  *(varName+2) != '3' && *(varName+2) != '4'     ) {
	return(-1);
      }
      
      return(*(varName+2) - '0');
      break;


    case ELEMENT_TYPE_TETRA:
      // line has x1,y1,z1,... x4,y4,z4
      if( *(varName+2) != '1' && *(varName+2) != '2'  &&
	  *(varName+2) != '3' && *(varName+2) != '4'     ) {
	return(-1);
      }
      
      return(*(varName+2) - '0');
      break;      

    case ELEMENT_TYPE_CUBE:
      // line has x1,y1,x2,y2,x3,y3,... x8,y8,z8
      if( *(varName+2) - '0' < 1 || *(varName+2) - '0' >8 ){
	return(-1);
      }
      return(*(varName+2) - '0');
      break;      


    default:
      std::cerr << "Illegal etype in isVertexVar(int etype, const char *varName)\n";
      break;
    }
  }
  // now, two digits or more are not vertex system variable.

  return(0);
}
