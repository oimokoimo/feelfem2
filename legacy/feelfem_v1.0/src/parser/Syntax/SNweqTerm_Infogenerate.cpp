/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerm_Infogenerate.cpp
 *  Date     : 2002/01/31
 *  Modified : 
 *  
 *  Purpose  : make SolveElement
 *  
 */

#include "SNweqTerm.hpp"

void SNweqTerm::AddVariablePtr_Regional(SolveElement *sePtr,
				       list <string>&testFuncLst)
{
  if(integralType ==TYPE_BOUNDARY_INTEGRAND) {
    return;
  }

  integrandExprPtr->AddVariablePtr_Regional(sePtr,
					    testFuncLst);
  return;
}

void SNweqTerm::ListUpQuadrature_Regional( list <string> &quadNameLst )
{
  if(integralType ==TYPE_BOUNDARY_INTEGRAND) {
    return;
  }
  
  if( quadratureType == TYPE_QUADRATURE_DEFAULT) return;

  if( quadNameLst.includes( quadratureMethod ) ) return;
  
  quadNameLst.addlast(quadratureMethod );

  return;
}

void SNweqTerm::AddVariablePtr_Boundary(Neumann *nPtr,
					list <string>&testFuncLst,
					list <string>&nTVarLst)
{
  if(integralType != TYPE_BOUNDARY_INTEGRAND) {
    return;
  }

  integrandExprPtr->AddVariablePtr_Boundary(nPtr,
					    testFuncLst,
					    nTVarLst);
  return;
}

