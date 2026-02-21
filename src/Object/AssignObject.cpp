/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : AssignObject.cpp
 *  Date     : 2002/04/17 (BCN)
 *  Modified : 
 *  
 *  Purpose  : Objects on assignment statements
 *
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

#include "Assign.hpp"

int Object::HowManyAssigns()   // used in main generator
{
  return assigns;
}

void Object::StoreAssign( Assign *assignPtr )
{
  assigns++;
  
  assignPtrLst.addlast(assignPtr);

  return;
}

