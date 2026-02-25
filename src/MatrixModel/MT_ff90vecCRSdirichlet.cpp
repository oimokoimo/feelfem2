/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90vecCRSdirichlet.cpp
 *  Date     : 2001/11/29 (copy from MT_ff90AMGCRSdirichlet.cpp)
 *  Modified : 
 *  
 *  Purpose  : feelfem90vec program model for dirichlet routine
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
#define SW writeSource

#include "feelfuncs.hpp"

#include "MT_ff90vecCRS.hpp"
#include "Dirichlet.hpp"


void MT_ff90vecCRS::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
{
  DoDirichletArgumentSequence( dPtr );
  SourceStarters();

  F90useDirichletPM();

  fortImplicit();
  com();

  DoDirichletArgumentVariableDefinitionsPM(dPtr);
  com();
  writeMatrixDeclarations();
  com();

  return;
}


void MT_ff90vecCRS::DoDirichletArgumentSequence(Dirichlet *dPtr)
{
  // subroutine statement
  pushSource("module mod_");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());
  flushSource();

  writeSource("contains");
  com();

  
  pushSource("subroutine ");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());


  doDirichletArgumentSequencePM(dPtr);

  //  pushSource("(nsetno,              &");
  //  flushSource();
  //  
  //  writeSource("  firstNsetPtr,              &");

  //  pushSource( "  ");
  //  pushCoordinateSource();
  //  pushSource(",ipf,ipd,npmax                     &");
  //  flushSource();

  /* Additional variables */
  //  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  //  listIterator <Variable *>itr(varPtrLst);

  //  pushVariableListInCalled( varPtrLst);

  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");
  flushSource();

  return;
}

void MT_ff90vecCRS::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  com();
  writeSource("! MT_ff90vecCRS::doDirichletAutoVariableDefinitionsMT");
  writeSource("integer                        :: iptf,iptt,iptf2,iptt2");
  writeSource("integer                        :: irptr");
  com();
  
  return;
}


void MT_ff90vecCRS::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{
  orderedPtrList <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  com();
  
  writeSource("call setP2nset(nsetno,firstNsetPtr,nodes,np,inset)");
  comment();

  writeSource("do 100 i=1,nodes");
  com();
  writeSource("   nd  = inset(1,i)");
  writeSource("   ieq = ipd(nd)+inset(2,i)");

  switch(getSpaceDimension()) {
  case 1:
    writeSource("    x_dpt = x(nd)");
    break;

  case 2:
    writeSource("    x_dpt = x(nd)");
    writeSource("    y_dpt = y(nd)");
    break;

  case 3:
    writeSource("    x_dpt = x(nd)");
    writeSource("    y_dpt = y(nd)");
    writeSource("    z_dpt = z(nd)");
    break;
  }


  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    
    pushSource("        ");
    pushFEMVariableInCalled(itr());
    pushSource("_dpt = ");
    pushFEMVariableInCalled(itr());              // own variable
    pushSource("(nd)");
    flushSource();
  }
  com();

  pushSource( "   u = ");
  pushSource( dirichletP2DOTEMP(dPtr->testGetTestExpression()) );
  flushSource();
  com();
  

  SW("!---------------------------");
  SW("! ieq dirichlet equation number");
  SW("!---------------------------");
  com();

  SW("!*********");
  SW("! row ieq");
  SW("!*********");

  SW("   iptf = iptrcol(ieq  )");
  SW("   iptt = iptrcol(ieq+1)-1");
  com();

  SW("   do j=iptf,iptt");
  SW("     if(indrow(j) .eq. ieq) then");
  SW("       valmat(j) = 1.0d0");
  SW("     else");
  SW("       valmat(j) = 0.0d0");
  SW("     endif");
  SW("   end do   ! j=iptf,iptt");

  SW("   vfg(ieq) = u");
  com();

  SW("!**********");
  SW("! column");
  SW("!**********");



  SW("!");
  SW("! Assume non-zero element is symmetric");
  SW("!");

  SW("  iptf = iptrcol(ieq  )");
  SW("  iptt = iptrcol(ieq+1)-1");
  com();

  SW("  do 160 j=iptf,iptt");
  SW("    irptr = indrow(j)");
  SW("    if(irptr .EQ. ieq ) goto 160");
  com();

  SW("    iptf2 = iptrcol(irptr  )");
  SW("    iptt2 = iptrcol(irptr+1)-1");
  SW("    do k=iptf2,iptt2");
  SW("      if(indrow(k) .eq. ieq) goto 170");
  SW("    end do");
  com();
  
  SW("!");
  SW("      write(*,*) 'cannot find in dcond'");
  SW("      call abortexit('Cannot find in dcond column')");
  SW("!");

  SW(" 170   continue");
  SW("      vfg(irptr)=vfg(irptr)-valmat(k)*u");
  SW("      valmat(k) = 0.0d0");
  SW(" 160 continue");
  com();

  SW("!");
  SW("! end of column");
  SW("!");

  SW(" 100  continue");

  comment();

  return;
}

