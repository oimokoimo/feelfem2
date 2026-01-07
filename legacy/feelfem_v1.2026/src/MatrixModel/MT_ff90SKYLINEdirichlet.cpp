/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90SKYLINEdirichlet.cpp
 *  Date     : 2002/03/06 (Copied from MT_ff90AMGCRS.cpp)
 *  Modified : 
 *  
 *  Purpose  : Feelfem90 program model for dirichlet routine
 *            (derived from drama model)
 */
#define SW writeSource

#include "feelfuncs.hpp"

#include "MT_ff90SKYLINE.hpp"
#include "Dirichlet.hpp"


void MT_ff90SKYLINE::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
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


void MT_ff90SKYLINE::DoDirichletArgumentSequence(Dirichlet *dPtr)
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

void MT_ff90SKYLINE::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  writeInteger4sc("i,j,lp");
  return;
}

void MT_ff90SKYLINE::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{
  com();

  writeSource("        do 110 j=1,neq");
  com();

  writeSource("          if(ieq         .eq.   j) goto 110");
  writeSource("          if(j           .gt. ieq) goto 105");
  writeSource("          if(ieq-KH(ieq) .gt.   j) goto 110");
  com();

  writeSource("          lp     = KLD(ieq+1) - ieq + j");
  writeSource("          vfg(j) = vfg(j)     - u   * vkgs(lp)");
  writeSource("          vkgs(lp)= 0.0d0");
  writeSource("          goto 110");
  com();

  writeSource(" 105      if(j - KH(j) .gt. ieq) goto 110");
  writeSource("          lp     = KLD(j+1)   - j + ieq");
  writeSource("          vfg(j) = vfg(j)     - u * vkgi(lp)");
  writeSource("          vkgi(lp)= 0.0d0");
  com();

  writeSource(" 110    continue");
  com();

  writeSource("        do 120 j=1,neq");
  writeSource("          if(ieq .eq. j) goto 121");
  writeSource("          if(ieq .gt. j) goto 125");
  com();

  writeSource("          if(j - KH(j) .gt. ieq) goto 120");
  writeSource("          lp = KLD(j+1)-j+ieq");
  writeSource("          vkgs(lp) = 0.0d0");
  writeSource("          goto 120");
  com();

  writeSource(" 121      vkgd(ieq)  = 1.0d0");
  writeSource("          vfg(ieq) = u");
  writeSource("          goto 120");
  com();

  writeSource(" 125      if(ieq - KH(ieq) .gt. j) goto 120");
  writeSource("          lp = KLD(ieq+1) - ieq + j");
  writeSource("          vkgi(lp) = 0.0d0");
  writeSource(" 120    continue");


  //  com();
  //  SW("end do ! (node loop)");
  //
  //  comment();

  return;
}

