/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfunctionObject.cpp
 *  Date     : 2002/09/17
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "../parser/Syntax/SNfunction.hpp"

#include "Object.hpp"
#include "list.hpp"

void Object::StoreSNfunctionPtr(SNfunction *ptr)
{
  snUserFunctionPtrLst.add(ptr);
  
  return;
}
