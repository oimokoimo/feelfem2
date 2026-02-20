/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerm_WEAKEQ.cpp
 *  Date     : 2002/01/30
 *  Modified : 2002/03/27 (add boundary part)
 *  
 *  Purpose  :
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
 */

#include <assert.h>
#include "SNweqTerm.hpp"

#include "feelfuncs.hpp"  // for setting boundary quadrature here from name
#include "Object.hpp" 

#include "IntegrandSet.hpp"  // for setting boundary quadrature here

// Region part
void SNweqTerm::WriteRegionWeqEqStrByQuad(int flag,string &quadName,
					  char *exprBUF,int &exprBUFptr,
					  int maxBUFlen)
{
  int  len;
  char buf[MAX_EXPRPRINT_BUF];
  buf[0] = '\0';


  if(integralType == TYPE_BOUNDARY_INTEGRAND) return;
  
  if(quadratureType == TYPE_QUADRATURE_SPECIFIED) {
    
    if(quadName == quadratureMethod) {

      integrandExprPtr->exprPrint(buf,EXPRPRINT_NORMAL, 0, 0);
      len = stringLength(buf);
      assert(exprBUFptr+len+2+1+2<maxBUFlen);

      if(flag == 1) {

	sprintf(exprBUF+exprBUFptr,"+(%s)%c",buf,'\0');
	exprBUFptr = exprBUFptr + len + 1 + 2;   // 1 for + 2 for ( and )
      }
      else {
	assert(flag == -1);
	sprintf(exprBUF+exprBUFptr,"-(%s)%c",buf,'\0');
	exprBUFptr = exprBUFptr + len + 1 + 2;   // 1 for - 2 for ( and )
	
      }
    }

    return;
  }

  // default integrand
  if(quadName != DEFAULT_STRING) return;

  integrandExprPtr->exprPrint(buf,EXPRPRINT_NORMAL, 0, 0);
  len = stringLength(buf);
  assert(exprBUFptr+len+2+1+2<maxBUFlen);
  
  if(flag == 1) {

    sprintf(exprBUF+exprBUFptr,"+(%s)%c",buf,'\0');
    exprBUFptr = exprBUFptr + len + 1 + 2;   // 1 for + 2 for ( and )
  }
  else {
    assert(flag == -1);
    sprintf(exprBUF+exprBUFptr,"-(%s)%c",buf,'\0');
    exprBUFptr = exprBUFptr + len + 1 + 2;   // 1 for - 2 for ( and )
  }

  return;
}


void SNweqTerm::MakeRegionIntegrandSetInfoByQuad( string &quadName,
						  IntegrandSet *isetPtr,
						  list <string> &tLst    )
{
  if(integralType == TYPE_BOUNDARY_INTEGRAND) return;
  
  if(quadratureType == TYPE_QUADRATURE_SPECIFIED) {
    
    if(quadName == quadratureMethod) {
      integrandExprPtr->MakeIntegrandSetInfo( isetPtr ,tLst);
    }

    return;
  }

  // default integrand
  if(quadName != DEFAULT_STRING) return;


  integrandExprPtr->MakeIntegrandSetInfo( isetPtr ,tLst);

  return;
}


// Boundary part
void SNweqTerm::WriteBoundaryWeqEqStr(int flag,
				      char *exprBUF,int &exprBUFptr,
				      int maxBUFlen)
{
  int  len;
  char buf[MAX_EXPRPRINT_BUF];
  buf[0] = '\0';


  if(integralType == TYPE_REGIONAL_INTEGRAND) return;
  
  integrandExprPtr->exprPrint(buf,EXPRPRINT_NORMAL, 0, 0);
  len = stringLength(buf);
  assert(exprBUFptr+len+2+1+2<maxBUFlen);

  if(flag == 1) {
    sprintf(exprBUF+exprBUFptr,"+(%s)%c",buf,'\0');
    exprBUFptr = exprBUFptr + len + 1 + 2;   // 1 for + 2 for ( and )
  }
  else {
    assert(flag == -1);
    sprintf(exprBUF+exprBUFptr,"-(%s)%c",buf,'\0');
    exprBUFptr = exprBUFptr + len + 1 + 2;   // 1 for - 2 for ( and )
    
  }
  return;
}

void SNweqTerm::MakeBoundaryIntegrandSetInfo( BoundaryIntegrandSet *bisetPtr,
					      list <string> &tLst    )
{
  if(integralType == TYPE_REGIONAL_INTEGRAND) return;
  
  if(quadratureType == TYPE_QUADRATURE_SPECIFIED) {
    Quadrature *qPtr;
    qPtr = feelfemobj.GetQuadraturePtrByName( quadratureMethod );
    assert(qPtr != 0);
    bisetPtr->SetQuadraturePtr(qPtr);
  }

  // Here, Neumann data in nbc: block are not stored
  integrandExprPtr->MakeIntegrandSetInfoBoundary( bisetPtr ,tLst);

  return;
}
