/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ParametricObject.cpp
 *  Date     : 2002/07/11
 *  Modified : 
 *  
 *  Purpose  : This is for assignment sentences of quad-ewise 
 *             left hand side.  parametric element for solve
 *             is defined differently.  But DEFAULT element uses
 *             the same.
 *
 */

#include <assert.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Configure.hpp"    // looks cross reference...
#include "Object.hpp"


// This function returns 1 if the parametric element of
// same element shape is already defined.
int Object::StoreParametricElementEw(const char *name)
{
  Element *ePtr = GetElementPtrByName( name );
  assert(ePtr != 0);

  int etype = ePtr->GetEtype();

  switch(etype) {
  case ELEMENT_TYPE_POINT:
    return(1);
    
  case ELEMENT_TYPE_LINE:
    if(lineParametricElementPtr != 0) return(1);
    lineParametricElementPtr = ePtr;
    return(0);

  case ELEMENT_TYPE_TRI:
    if(triParametricElementPtr != 0) return(1);
    triParametricElementPtr = ePtr;
    return(0);

  case ELEMENT_TYPE_RECT:
    if(rectParametricElementPtr != 0) return(1);
    rectParametricElementPtr = ePtr;
    return(0);

  case ELEMENT_TYPE_TETRA:
    if(tetraParametricElementPtr != 0) return(1);
    tetraParametricElementPtr = ePtr;
    return(0);

  case ELEMENT_TYPE_CUBE:
    if(hexParametricElementPtr != 0) return(1);
    hexParametricElementPtr = ePtr;
    return(0);
  }
  assert(1==0);

}

Element *Object::GetParametricElementPtrEwByEtype(int etype)
{
  string defaultElementName;
  feelfemconf.SetParametricElementName( etype , defaultElementName );

  assert(IsDefinedElementName( defaultElementName ));  // check here....
  
  switch(etype) {
  case ELEMENT_TYPE_POINT:
    assert(1==0);

  case ELEMENT_TYPE_LINE:
    if(lineParametricElementPtr == 0) {
      Element *ePtr = GetElementPtrByName( defaultElementName );
      return(ePtr);
    }
    else {
      return(lineParametricElementPtr);
    }
    break;

  case ELEMENT_TYPE_TRI:
    if(triParametricElementPtr == 0) {
      Element *ePtr = GetElementPtrByName( defaultElementName );
      return(ePtr);
    }
    else {
      return(triParametricElementPtr);
    }
    break;

  case ELEMENT_TYPE_RECT:
    if(rectParametricElementPtr == 0) {
      Element *ePtr = GetElementPtrByName( defaultElementName );
      return(ePtr);
    }
    else {
      return(rectParametricElementPtr);
    }
    break;

  case ELEMENT_TYPE_TETRA:
    if(tetraParametricElementPtr == 0) {
      Element *ePtr = GetElementPtrByName( defaultElementName );
      return(ePtr);
    }
    else {
      return(tetraParametricElementPtr);
    }
    break;

  case ELEMENT_TYPE_CUBE:
    if(hexParametricElementPtr == 0) {
      Element *ePtr = GetElementPtrByName( defaultElementName );
      return(ePtr);
    }
    else {
      return(hexParametricElementPtr);
    }
    break;

  }
  assert(1==0);
}
