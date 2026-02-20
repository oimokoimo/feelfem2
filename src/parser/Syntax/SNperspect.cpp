/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNperspect.cpp
 *  Date     : 2002/01/21
 *  Modified : 
 *  
 *  Purpose  : 
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "string.hpp"
#include "Expression.hpp"

#include "SNperspect.hpp"
#include "SNoption.hpp"


SNperspect::SNperspect(Expression *ePtr )
  : SNunit("perspect",SN_PERSPECT)
{
  options = 0;
  exprPtr = ePtr;

  return;
}

SNperspect::SNperspect(Expression *ePtr ,stack <SNunit *> &parseOptionStack )
  : SNunit("perspect",SN_PERSPECT)
{
  options = 0;
  exprPtr = ePtr;

  while( !parseOptionStack.isEmpty()) {
    SNunit   *unitPtr;
    SNoption *optPtr;

    unitPtr = parseOptionStack.pop();
    
    optPtr  = (SNoption *)unitPtr;

    optionLst.add(optPtr);
    options++;
  }
  
  return;
}


void SNperspect::print(std::ostream &ost)
{
  ost << "perspect [";
  exprPtr->print(ost);
  ost << "] ";

  listIterator <SNoption *>itr(optionLst);

  for(itr.init(); !itr ; ++itr) {
    itr()->print(ost);
  }
  
  ost << std::endl;

  return;
}
