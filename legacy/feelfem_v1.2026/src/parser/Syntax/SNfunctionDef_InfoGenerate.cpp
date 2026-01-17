/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNfunctionDef_InfoGenerate.cpp
 *  Date     : 2002/09/13
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "SNfunctionDef.hpp"
#include "feelfuncs.hpp"
#include "Function.hpp"
#include "Object.hpp"

    
int SNfunctionDef::InfoGenerate(void)
{
  int args = identifierLst->GetNumberOfElements();

  Function *funcPtr = new Function( name , args );

  feelfemobj.StoreUserFunction( funcPtr );

  return(0);
}
