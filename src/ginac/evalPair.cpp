/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : evalPair.cpp
 *  Date     : 2001/03/15
 *  Modified : 
 *  
 *  Purpose  : evaluation pair
 *  
 */

#include "evalPair.hpp"
#include "string.hpp"



int operator ==(const evalPair &left, const evalPair &right)
{
  return( left.varName == right.varName);     // used in ptrList->includes()
}
