/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90AMGCRSdirichlet.cpp
 *  Date     : 2000/12/08
 *  Modified : 2000/12/08
 *  
 *  Purpose  : Feelfem90 program model for dirichlet routine
 *            (derived from drama model)
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

#include "MT_ff90AMGCRS.hpp"
#include "Dirichlet.hpp"


void MT_ff90AMGCRS::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
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


void MT_ff90AMGCRS::DoDirichletArgumentSequence(Dirichlet *dPtr)
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


  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");
  flushSource();

  return;
}

void MT_ff90AMGCRS::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // matrix oriented auto variables
  writeInteger4sc("i,j,k");
  writeInteger4sc("iptf,iptt,iptf2,iptt2");
  writeInteger4sc("irptr");

  return;
}


void MT_ff90AMGCRS::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{
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

  //  SW("end do ! (node loop)");
  //
  //  comment();

  return;
}

