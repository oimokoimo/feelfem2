/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNwrite.cpp
 *  Date     : 2002/11/22 (copy from output)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "string.hpp"
#include "Expression.hpp"

#include "SNwrite.hpp"
#include "SNexpr.hpp"
#include "SNstring.hpp"


SNwrite::SNwrite(stack <SNunit *>&parseWriteStack )   // no option version
  : SNunit("write",SN_WRITE)
{

  items = 0;

  while( !parseWriteStack.isEmpty()) {
    SNunit   *unitPtr;
    unitPtr = parseWriteStack.pop();
    writeSNunitPtrLst.add(unitPtr);
    items++;
  }

  return;
}

void SNwrite::print(ostream &ost)
{
  ost << "write [";
  ost << "NOT IMPLEMENTED YET";
  ost << "] ";

  ost << endl;

  return;
}
