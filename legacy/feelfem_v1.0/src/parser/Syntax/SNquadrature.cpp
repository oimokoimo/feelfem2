/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadrature.cpp
 *  Date     : 2001/03/27
 *  Modified : 
 *  
 *  Purpose  : quadrature statement parser
 *  
 */

#include "SNquadrature.hpp"
#include "SNquadratureDoubleVar.hpp"
#include "SNquadratureAssignment.hpp"
#include "SNquadratureGaussP.hpp"

SNquadrature::SNquadrature( char *nm,char *elem, stack <SNunit *>&parseQuadratureStack)
  : SNunit("quadrature",SN_QUADRATURE) 
{
  // initialization
  name         = nm;
  elementShape = elem;
  etype        = 0;     // initialization
  dimension    = 0;     // initialization

  while(!parseQuadratureStack.isEmpty()) {
    SNunit *unitPtr;
    SNquadratureGaussP      *gaussPPtr;
    
    unitPtr = parseQuadratureStack.pop();

    switch( unitPtr->GetType() ) {
    case SN_QUADRATUREDOUBLEVAR:
    case SN_QUADRATUREASSIGNMENT:
      dblAndAssignPtrLst.add(unitPtr);
      break;

    case SN_QUADRATUREGAUSSP:
      gaussPPtr = (SNquadratureGaussP *)unitPtr;
      gaussPPtrLst.add(gaussPPtr);
      break;
    default:
      abortExit("Illegal SNcode in SNquadrature constructor");
    }
  }
  return;
}

void SNquadrature::print(ostream &ost) 
{
  ost << "Quadrature "<< name << "[" <<elementShape <<"]" << endl;
  listIterator <SNunit *>itr1(dblAndAssignPtrLst);
  ost << "-- dbl variable & assignments\n";
  for(itr1.init();!itr1; ++itr1) {
    itr1()->print(ost);
    ost << "\n";
  }
  ost << "-----------------------------\n";
  
  listIterator <SNquadratureGaussP *> itr2(gaussPPtrLst);
  for(itr2.init();!itr2; ++itr2) {
    itr2()->print(ost);
    ost << "\n";
  }

  return;
}


int SNquadrature::SetGaussPoints(void)
{

  gaussPoints = gaussPPtrLst.getNumberOfElements();
  if(gaussPoints == 0) {
    return(1);
  }
  else {
    return(0);
  }
}
