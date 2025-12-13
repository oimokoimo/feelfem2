/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveWeq_WEAKEQ.cpp
 *  Date     : 2002/01/30
 *  Modified : 2002/03/27 (add boundary part)
 *  
 *  Purpose  :
 *  
 */

#include "SNsolveWeq.hpp"

// for regional integrands
void SNsolveWeq::WriteRegionWeakEqStrByQuad(string &quadName,
					    char *exprBUF,int &exprBUFptr,
					    int maxBUFlen)
{
  leftHandSideWeqTermsPtr->
     WriteRegionWeakEqStrByQuad( 1,quadName,exprBUF,exprBUFptr,maxBUFlen);

  rightHandSideWeqTermsPtr->
     WriteRegionWeakEqStrByQuad(-1,quadName,exprBUF,exprBUFptr,maxBUFlen);

  return;
}

void SNsolveWeq::MakeRegionIntegrandSetInfoByQuad(string &quadName,
						  IntegrandSet *isetPtr ,
						  list <string>&tLst)
{
  leftHandSideWeqTermsPtr ->
    MakeRegionIntegrandSetInfoByQuad(quadName,isetPtr,tLst);

  rightHandSideWeqTermsPtr->
    MakeRegionIntegrandSetInfoByQuad(quadName,isetPtr,tLst);

  return;
}

// for boundary integrands
void SNsolveWeq::WriteBoundaryWeakEqStr(char *exprBUF,int &exprBUFptr,
					int maxBUFlen)
{
  leftHandSideWeqTermsPtr->
     WriteBoundaryWeakEqStr( 1,exprBUF,exprBUFptr,maxBUFlen);

  rightHandSideWeqTermsPtr->
     WriteBoundaryWeakEqStr(-1,exprBUF,exprBUFptr,maxBUFlen);

  return;
}

void SNsolveWeq::MakeBoundaryIntegrandSetInfo(BoundaryIntegrandSet *bisetPtr ,
					      list <string>&tLst)
{
  leftHandSideWeqTermsPtr ->
    MakeBoundaryIntegrandSetInfo(bisetPtr,tLst);

  rightHandSideWeqTermsPtr->
    MakeBoundaryIntegrandSetInfo(bisetPtr,tLst);

  return;
}
