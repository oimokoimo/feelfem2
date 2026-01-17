/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveWeq.cpp
 *  Date     : 2002/04/18 (BCN)
 *  Modified : 
 *  
 *  Purpose  : int HasBounaryTerm(void)
 *  
 */

#include "feeldef.hpp"
#include "SNsolveWeq.hpp"

int SNsolveWeq::HasBoundaryTerm(void)
{
  if(  leftHandSideWeqTermsPtr->HasBoundaryTerm() == YES) return(YES);
  if( rightHandSideWeqTermsPtr->HasBoundaryTerm() == YES) return(YES);

  return(NO);
}

