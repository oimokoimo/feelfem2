/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveWeq_CHECK.cpp
 *  Date     : 2002/01/29
 *  Modified : 
 *  
 *  Purpose  : list up undef variable in weak formulation
 *  
 *  int VariableDefinedCheck(..)   returns number of undef variables
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

#include "list.hpp"
#include "string.hpp"
#include "SNsolveWeq.hpp"

// only checks regional integrand.  
int SNsolveWeq::VariableDefinedCheck_Regional( list<string>&testFuncLst)
{
  int ret;
  ret = 0;

  ret =  leftHandSideWeqTermsPtr->VariableDefinedCheck_Regional( testFuncLst);
  ret+= rightHandSideWeqTermsPtr->VariableDefinedCheck_Regional( testFuncLst);
  
  return(ret);
}

// boundary portion check
int SNsolveWeq::VariableDefinedCheck_Boundary( list<string>&tLst,
					       SNsolveNeumann *snSNPtr,
					       list<string>&apLst)
{
  int ret;
  ret = 0;

  ret =  leftHandSideWeqTermsPtr->VariableDefinedCheck_Boundary(tLst,
								snSNPtr,
								apLst);

  ret+= rightHandSideWeqTermsPtr->VariableDefinedCheck_Boundary(tLst,
								snSNPtr,
								apLst);
  
  return(ret);
}

int SNsolveWeq::EtypeConsistencyCheck(int refEtype,
				      list<string>&testFuncLst,
				      list<string>&nVarLst)
{
  int ret;
  ret = 0;

  ret =  leftHandSideWeqTermsPtr->EtypeConsistencyCheck(refEtype,
							testFuncLst,
							nVarLst);

  ret+= rightHandSideWeqTermsPtr->EtypeConsistencyCheck(refEtype,
							testFuncLst,
							nVarLst);
  return(ret);
}


int SNsolveWeq::QuadratureConsistencyCheck( int refEtype ,
					    list <string>&tLst,
					    Quadrature *qPtr)
{
  int ret;
  ret = 0;

  ret =  leftHandSideWeqTermsPtr->QuadratureConsistencyCheck(refEtype,
							     tLst,
							     qPtr);
  ret+= rightHandSideWeqTermsPtr->QuadratureConsistencyCheck(refEtype,
							     tLst,
							     qPtr);
  
  return(ret);
}
  
