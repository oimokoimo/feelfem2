/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LabelObject.cpp
 *  Date     : 2002/07/18
 *  Modified : 2002/07/22  LabelPtr
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

#include <cassert>
#include <iostream>

#include "Object.hpp"

#include "string.hpp"
#include "list.hpp"
#include "Label.hpp"

void Object::StoreLabelPtr(Label *labelPtr)
{
  labelPtrLst.addlast(labelPtr);
  return;
}

Label *Object::GetLabelPtrByName(const char *nm)
{
  listIterator <Label *>itr(labelPtrLst);
  for(itr.init(); !itr ;++itr) {
    if(itr()->isNameIs(nm)) {
      Label *ret = itr();
      return(ret);
    }
  }
  std::cerr << "No specified label pointer. " << nm << std::endl;
  assert(1==0);
}
