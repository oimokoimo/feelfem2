/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelementDoubleVar_CHECK.cpp
 *  Date     : 2001/12/25
 *  Modified : 
 *  
 *  Purpose  : check routine.  DoubleVar part for CheckSystemVariables
 *  
 */

#include "feeldef.hpp"                // for etype definitions
#include "SNelementDoubleVar.hpp"


int isVertexVar(int, const char *);   // in check/isSystemVariable.cpp

// called from SNelement_CHECK.cpp
// return 0 if declared variable is not Vertex Variable
// return 1 if declared variable is Vertex Variable
// Vertex variables need not be declared.
int SNelementDoubleVar::CheckSystemVariables( int etype )
{
  // is system variable name is declared?
  int ret = isVertexVar(etype , name);

  if( ret == 0 || ret == -1) {

    return(0);  // name is not valid vertex var name.  no error.

  }

  return( 1 );
}


