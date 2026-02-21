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

