/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Output.cpp
 *  Date     : 2002/04/23 (BCN)
 *  Modified : 
 *  
 *  Purpose  : Output class constructor, etc.
 *  
 */

#include "Output.hpp"

int Output::outputs = 0;

Output::Output(void)
{
  outputs++;
  outputNo = outputs;

  components    = 0;
  quadraturePtr = 0;

  options       = 0;

  return;
}

Output::~Output()
{
  // do nothing now
  return;
}

int Output::GetOutputNo(void)
{
  return(outputNo);
}

void Output::AddIdentifier(string &str)
{
  components++;
  identifierStrLst.addlast(str);
  return;
}

void Output::AddVariablePtr(Variable *vPtr)
{
  if(varPtrLst.includes(vPtr)) return;
  varPtrLst.add(vPtr);
  
  return;
}

void Output::SetQuadraturePtr(Quadrature *qPtr)
{
  quadraturePtr = qPtr;
  return;
}

void Output::AddOption(char *key,char *val)
{
  options++;
  optionKeyStrLst.addlast(key);
  optionValStrLst.addlast(val);
  return;
}

int Output::HasOption(const char *key)
{
  listIterator<string>itr(optionKeyStrLst);
  for(itr.init();!itr;++itr) {
    if(itr() == key) return (YES);
  }
  return(NO);
}

void Output::GetOption(const char *key,string &val)
{
  listIterator<string>itrkey(optionKeyStrLst);
  listIterator<string>itrval(optionValStrLst);

  itrval.init();
  for(itrkey.init();!itrkey;++itrkey) {
    if(itrkey() == key) {
      val = itrval();
      return;
    }
    ++itrval;
  }
  assert(1==0);
}
  
