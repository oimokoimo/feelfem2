/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementObject.cpp
 *  Date     : 1999/11/29
 *  Modified : 2000/12/27   abortExit
 *  
 *  Purpose  : Object record for Elements
 *  
 */

#include "feelfuncs.hpp"
#include "Object.hpp"

int streq(const char*,const char *);

void Object::StoreElement(Element *ePtr)
{
  elements++;

  elementPtrLst.add(ePtr);

  return;
}

Element * Object::GetElementPtrByName(const char *name)
{
  listIterator <Element *> itr(elementPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(name)) {
      Element *ret = itr();

      //      ret -> print(cerr); debug;
      
      return(ret);
    }       
  }
  return(NULL);
}


int Object::IsDefinedElementName(const char *name)
{
  listIterator <Element *> itr(elementPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(name)) {
      return(YES);
    }       
  }
  return(NO);
}

int Object::IsDefinedElementName(string &nameStr )
{
  listIterator <Element *> itr(elementPtrLst);
  for(itr.init(); !itr ; ++itr) {
    if(itr()->isNameIs(nameStr)) {
      return(YES);
    }       
  }
  return(NO);
}
