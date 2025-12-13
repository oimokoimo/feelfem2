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
 */

#include <assert.h>
#include <iostream.h>

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
  cerr << "No specified label pointer. " << nm << endl;
  assert(1==0);
}
