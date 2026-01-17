/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNexpr.cpp
 *  Date     : 2002/11/22
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNexpr.hpp"
#include "SNunit.hpp"

SNexpr::SNexpr(Expression *ptr) :
  SNunit("expr",SN_EXPR) 
{
  exprPtr=ptr;
  return;
}

SNexpr::~SNexpr()
{
  // do nothing now
  return;
}
