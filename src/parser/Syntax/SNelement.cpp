/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNelement.cpp
 *  Date     : 2001/03/05
 *  Modified : 2002/01/08
 *  
 *  Purpose  : element statement parser
 *  
 *       
 *             setIntpEtype()   // 2002/01/08
 *
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

#include "SNelement.hpp"
#include "SNelementDoubleVar.hpp"
#include "SNelementAssignment.hpp"
#include "SNelementIntp.hpp"

#include "Node.hpp"

SNelement::SNelement( char *nm,char *elem, stack <SNunit *>&parseElementStack)
  : SNunit("element",SN_ELEMENT) 
{
  // initialization
  name         = nm;
  elementShape = elem;    
  etype        = 0;
  dimension    = -1;

  doubles      = 0;
  assignments  = 0;
  nodes        = 0;
  interpolates = 0;

  elemPtr      = 0;  // NULL initialize

  while(!parseElementStack.isEmpty()) {
    SNunit *unitPtr;
    SNelementIntp      *intpPtr;
    
    unitPtr = parseElementStack.pop();

    switch( unitPtr->GetType() ) {
    case SN_ELEMENTDOUBLEVAR:
      dblAndAssignPtrLst.add(unitPtr);
      doubles++;
      break;

    case SN_ELEMENTASSIGNMENT:
      dblAndAssignPtrLst.add(unitPtr);
      assignments++;
      break;

    case SN_ELEMENTINTP:
      intpPtr = (SNelementIntp *)unitPtr;
      intpPtrLst.add(intpPtr);
      interpolates++;

      break;
    default:
      abortExit("Illegal SNcode in SNelement constructor");
    }
  }
  return;
}

void SNelement::print(std::ostream &ost) 
{
  ost << "Element "<< name << "[" <<elementShape <<"]" << std::endl;
  listIterator <SNunit *>itr1(dblAndAssignPtrLst);
  ost << "-- dbl variable & assignments\n";
  for(itr1.init();!itr1; ++itr1) {
    itr1()->print(ost);
    ost << "\n";
  }
  ost << "-----------------------------\n";
  
  listIterator <SNelementIntp *> itr2(intpPtrLst);
  for(itr2.init();!itr2; ++itr2) {
    itr2()->print(ost);
    ost << "\n";
  }

  return;
}

//  set etype for SNelementIntp  , called from SNelement::setEtype(void) {}
//                                 in SNelement_CHECK.cpp
void SNelement::setIntpEtype(void)
{
  listIterator <SNelementIntp *>itr(intpPtrLst);

  // set Etype
  for(itr.init(); !itr ; ++itr ) {

    itr()->setEtype(etype);
  }
  
  return;
}



//
//  information functions
//
int SNelement::GetNumberOfInterpolates(void)
{
  return(interpolates);
}

int SNelement::GetNumberOfNodes(void)
{
  return(nodes);
}

