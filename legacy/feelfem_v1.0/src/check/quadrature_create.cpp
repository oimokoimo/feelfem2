/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : quadrature_create.cpp
 *  Date     : 2001/03/28
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>

#include "feelfem.hpp"   // extern for dispDebugFlag

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNquadrature.hpp"
#include "../parser/Syntax/SNquadratureDoubleVar.hpp"
#include "../parser/Syntax/SNquadratureAssignment.hpp"
#include "../parser/Syntax/SNquadratureGaussP.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Quadrature.hpp"

int quadrature_create(list <void *>&parseQuadratureLst)
{
  int i;
  i = 0;

  listIterator <void *>itr(parseQuadratureLst);

  for(itr.init(); !itr ; ++itr) {
    SNquadrature *snqPtr = (SNquadrature*)itr();

    snqPtr->InfoGenerate();  // int value, but not used return value

    // X-Window display debug
    if(dispDebugFlag == YES) {
      snqPtr->dbgXDisplay();
    }
    
  }


  return(0);
}

