/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoutput.cpp
 *  Date     : 2002/04/17 (BCN)  (copy of SNperspect.cpp)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "string.hpp"
#include "Expression.hpp"

#include "SNoutput.hpp"
#include "SNexprlist.hpp"
#include "SNoption.hpp"


SNoutput::SNoutput(SNidentifierlist *ptr )   // no option version
  : SNunit("output",SN_OUTPUT)
{
  outputPtr = 0;

  options = 0;
  snIdentifierlistPtr = ptr;

  return;
}

SNoutput::SNoutput(SNidentifierlist *ptr ,stack <SNunit *> &parseOptionStack )
  : SNunit("output",SN_OUTPUT)
{
  outputPtr = 0;
  snIdentifierlistPtr = ptr;

  // options
  options = 0;

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


void SNoutput::print(ostream &ost)
{
  ost << "output [";
  snIdentifierlistPtr->print(ost);
  ost << "] ";

  listIterator <SNoption *>itr(optionLst);

  for(itr.init(); !itr ; ++itr) {
    itr()->print(ost);
  }
  ost << endl;

  return;
}
