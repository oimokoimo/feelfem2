/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Object.cpp
 *  Date     : 1999/11/29
 *  Modified : 1999/11/29
 *  
 *  Purpose  : Object class constructor/destructor
 *  
 */

#include "feeldef.hpp"
#include "Object.hpp"

Object::Object()
{
  // mesh
  spaceDimension   = 0;
  used_mesher_code = 0;

  // vars
  variables        = 0;
  
  // elements
  elements         = 0;
  
  // quadratures
  quadratures      = 0;

  // schemes
  solves           = 0;
  assigns          = 0;
  outputs          = 0;

  initialDoubles   = 0;
  initialIntegers  = 0;
  numberOfMaterialVars = 0;

  numberOfUserFunctions = 0;

  fileObjects      = 0;
  tmpFileObjects   = 0;

  // set in StoreParametricElementEw(const char *);
  lineParametricElementPtr  = 0;
  triParametricElementPtr   = 0;
  rectParametricElementPtr  = 0;
  tetraParametricElementPtr = 0;
  hexParametricElementPtr   = 0;

  // ginac require function symbols (02/09/16)
  arg1Functions=0;
  arg2Functions=0;
  arg3Functions=0;

  return;
}

Object::~Object()
{
  return;
}
