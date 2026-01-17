/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : getSpaceDimension.cpp
 *  Date     : 2001/04/06
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "feelfuncs.hpp"
#include "Object.hpp"

int getSpaceDimension(void)
{
  return(feelfemobj.GetSpaceDimension());
}
