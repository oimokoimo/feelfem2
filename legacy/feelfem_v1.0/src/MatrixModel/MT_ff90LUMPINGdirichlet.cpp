/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90LUMPINGdirichlet.cpp
 *  Date     : 2002/10/07 (Copy from MT_ff90SKYLINEdirichlet.cpp)
 *  Modified : 
 *  
 *  Purpose  : Feelfem90 program model for dirichlet routine
 *            (derived from drama model)
 */
#define SW writeSource

#include "feelfuncs.hpp"

#include "MT_ff90LUMPING.hpp"
#include "Dirichlet.hpp"


void MT_ff90LUMPING::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
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


void MT_ff90LUMPING::DoDirichletArgumentSequence(Dirichlet *dPtr)
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

void MT_ff90LUMPING::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  writeInteger4sc("i,j,lp");
  return;
}

void MT_ff90LUMPING::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{

  //   ieq has the dirichlet data equation Number
  com();
  writeSource("   vkgd(ieq)  = 1.0d0");
  writeSource("   vfg(ieq) = u");
  com();


  return;
}

