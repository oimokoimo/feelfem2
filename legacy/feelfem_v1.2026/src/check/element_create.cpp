/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : element_create.cpp
 *  Date     : 2001/03/28
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */
#include <iostream.h>

#include "../parser/Syntax/SNunit.hpp"
#include "../parser/Syntax/SNelement.hpp"
#include "../parser/Syntax/SNelementDoubleVar.hpp"
#include "../parser/Syntax/SNelementAssignment.hpp"
#include "../parser/Syntax/SNelementIntp.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"
#include "Element.hpp"

int element_create(list <void *>&parseElementLst)
{
  int i;
  i = 0;

  listIterator <void *>itr(parseElementLst);
  for(itr.init(); !itr ; ++itr) {
    SNelement *snePtr = (SNelement*)itr();

    snePtr->InfoGenerate();
  }
  return(0);
}
