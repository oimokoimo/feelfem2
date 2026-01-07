/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelement_InfoGenerate.cpp
 *  Date     : 2001/12/25
 *  Modified : 2002/01/31
 *  
 *  Purpose  : Generate Element class from Syntax information
 *  
 */

#include <iostream.h>

#include "SNelementIntp.hpp"
#include "SNelement.hpp"

#include "feelfem.hpp"
#include "Object.hpp"
#include "Element.hpp"

int SNelement::InfoGenerate(void)
{
  Element *elemPtr = new Element;


  elemPtr->SetName(name);
  elemPtr->SetEtype(etype);
  elemPtr->SetType( -1 );                    // feelfemTEMP

  elemPtr->SetNumberOfNodes(nodes);
  elemPtr->SetNumberOfFreedom(interpolates);

  feelfemobj.StoreElement(elemPtr);

  // Copy Node Pointer information
  listIterator <Node *>itr(nodeOrderedPtrLst);
  for(itr.init();!itr ;++itr) {
    elemPtr->AddNodePtr( itr() );
  }

  // Add Interpolation information

  listIterator <SNelementIntp *>itrI(intpPtrLst);
  for(itrI.init();!itrI ;++itrI) {
    Interpolation *intpPtr;

    intpPtr = itrI()->GenerateInterpolationDat();

    elemPtr->AddInterpolationPtr(intpPtr);
  }

  return(0);
}
