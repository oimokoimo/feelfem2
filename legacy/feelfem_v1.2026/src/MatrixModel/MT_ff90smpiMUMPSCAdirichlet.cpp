/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90smpiMUMPSCAdirichlet.cpp
 *  Date     : 2003/01/01 (Copied from MT_ff90AMGCRSdirichlet.cpp)
 *  Modified : 2003/01/04  
 *  
 *  Purpose  : Feelfem90 program model for dirichlet routine
 *            (derived from drama model)
 */
#define SW writeSource

#include "feelfuncs.hpp"

#include "MT_ff90smpiMUMPSCA.hpp"
#include "Dirichlet.hpp"


void MT_ff90smpiMUMPSCA::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
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


void MT_ff90smpiMUMPSCA::DoDirichletArgumentSequence(Dirichlet *dPtr)
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

void MT_ff90smpiMUMPSCA::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // matrix oriented auto variables
  writeInteger4sc("i,j,k");
  writeInteger4sc("iptf,iptt,iptf2,iptt2");
  writeInteger4sc("irptr");

  return;
}


void MT_ff90smpiMUMPSCA::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
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
  SW("     if(mumps_par%JCN(j) .eq. ieq) then");
  SW("       mumps_par%A(j) = 1.0d0");
  SW("     else");
  SW("       mumps_par%A(j) = 0.0d0");
  SW("     endif");
  SW("   end do   ! j=iptf,iptt");

  SW("   mumps_par%RHS(ieq) = u");
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
  SW("    irptr = mumps_par%JCN(j)");
  SW("    if(irptr .EQ. ieq ) goto 160");
  com();

  SW("    iptf2 = iptrcol(irptr  )");
  SW("    iptt2 = iptrcol(irptr+1)-1");
  SW("    do k=iptf2,iptt2");
  SW("      if(mumps_par%JCN(k) .eq. ieq) goto 170");
  SW("    end do");
  com();
  
  SW("!");
  SW("      write(*,*) 'cannot find in dcond'");
  SW("      call abortexit('Cannot find in dcond column')");
  SW("!");

  SW(" 170   continue");
  SW("      mumps_par%RHS(irptr)=mumps_par%RHS(irptr)-mumps_par%A(k)*u");
  SW("      mumps_par%A(k) = 0.0d0");
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

