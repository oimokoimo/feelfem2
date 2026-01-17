/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : OutputObject.cpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  : Objects on output statements
 *  
 */

#include "list.hpp"
#include "Object.hpp"

#include "Output.hpp"

int Object::HowManyOutputs()   // used in main generator
{
  return outputs;
}

void Object::StoreOutput( Output *outputPtr )
{
  outputs++;
  
  outputPtrLst.addlast(outputPtr);

  return;
}

