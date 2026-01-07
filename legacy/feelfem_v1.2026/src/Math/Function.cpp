/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Function.cpp
 *  Date     : 2002/09/12
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "Function.hpp"

#include "Object.hpp"
#include "feelfuncs.hpp"

Function::Function(char *nm, int n)
{

  name      = nm;
  arguments = n;

  tcno = feelfemobj.GetUserFunctionTCno(arguments);
  return;
}

Function::~Function()
{
  // do nothing
}

int Function::GetFunctionTCno(void)
{
  return tcno;
}
