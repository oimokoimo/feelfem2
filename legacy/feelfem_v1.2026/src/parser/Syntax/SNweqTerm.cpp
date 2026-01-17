/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerm.cpp
 *  Date     : 2002/04/18 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feeldef.hpp"
#include "SNweqTerm.hpp"

int SNweqTerm::IsBoundaryTerm(void)
{
  if(integralType == TYPE_BOUNDARY_INTEGRAND) {
    return(YES);
  }
  else {
    return(NO);
  }
}
