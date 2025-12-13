/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann_CodeGenerateSub.cpp
 *  Date     : 2002/04/10
 *  Modified : 
 *  
 *  Purpose  : Utility functions while code generation
 *  
 */

#include "Neumann.hpp"
#include "BoundaryElementNodePattern.hpp"

int *Neumann::GetNodePatternForEcal(Variable *vPtr)
{
  int *ret;

  ret = nBENPPtr->MakeNodeInfoForFEMvar( vPtr );

  return(ret);
}

// this is for parametric element
int *Neumann::GetNodePatternForEcal(Element *ePtr)
{
  int *ret;

  ret = nBENPPtr->MakeNodeInfoForFEMvar( ePtr );

  return(ret);
}
