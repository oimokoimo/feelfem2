/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Configure_Parametric.cpp
 *  Date     : 2002/02/19
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <assert.h>
#include <iostream.h>

#include "feeldef.hpp"
#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Configure.hpp"
#include "string.hpp"

void Configure::SetParametricElementName(int etype, string &paraElementName)
{
  switch( etype ) {
    
  case ELEMENT_TYPE_POINT:
    assert(1==0);
    break;

  case ELEMENT_TYPE_LINE:
    paraElementName = DEFAULT_PARAMETRIC_ELEMENT_LINE;
    break;
    
  case ELEMENT_TYPE_TRI:
    paraElementName = DEFAULT_PARAMETRIC_ELEMENT_TRI;
    break;
    
  case ELEMENT_TYPE_RECT:
    paraElementName = DEFAULT_PARAMETRIC_ELEMENT_RECT;
    break;

  case ELEMENT_TYPE_TETRA:
    paraElementName = DEFAULT_PARAMETRIC_ELEMENT_TETRA;
    break;

  case ELEMENT_TYPE_CUBE:
    paraElementName = DEFAULT_PARAMETRIC_ELEMENT_CUBE;
    break;

  default:
    assert(1==0);

  }
  return;
}
