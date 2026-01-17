/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalEvalPair.cpp
 *  Date     : 2002/03/05
 *  Modified : 2002/04/10   type->diffType
 *  
 *  Purpose  :
 *  
 */

#include "list.hpp"
#include "EcalInfo.hpp"

EcalEvalPair::EcalEvalPair( Element *ptr, int t)
{
  elemPtr = ptr;
  diffType    = t;

  return;
}

EcalEvalPair::~EcalEvalPair()
{
  return;
}

int operator ==(const EcalEvalPair &left,const EcalEvalPair &right)
{
  return( left.diffType == right.diffType && left.elemPtr == right.elemPtr );
}
