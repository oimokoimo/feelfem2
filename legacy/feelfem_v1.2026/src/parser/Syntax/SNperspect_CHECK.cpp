/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNperspect_CHECK.cpp
 *  Date     : 2002/01/21
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include "SNperspect.hpp"
#include "Expression.hpp"

int SNperspect::checkExprWellDefined(void)
{
  int ret;

  SNunit *suPtr = this;

  ret = exprPtr->checkDefinedFEMObjectSN(suPtr);

  return(ret);

}
