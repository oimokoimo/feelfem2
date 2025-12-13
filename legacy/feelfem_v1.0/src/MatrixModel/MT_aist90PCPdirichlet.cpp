/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_aist90PCPdirichlet.cpp
 *  Date     : 2002/06/28
 *  Modified :
 *  
 *  Purpose  : Feelfem90 program model for dirichlet routine
 *            (derived from drama model)
 */
#define SW writeSource

#include "feelfuncs.hpp"

#include "MT_aist90PCP.hpp"
#include "Dirichlet.hpp"


void MT_aist90PCP::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
{
  DoDirichletArgumentSequence( dPtr );
  SourceStarters();

  F90useDirichletPM();

  writeSource("use pcp90");
  com();

  fortImplicit();
  com();

  DoDirichletArgumentVariableDefinitionsPM(dPtr);
  com();
  writeMatrixDeclarations();
  com();

  return;
}


void MT_aist90PCP::DoDirichletArgumentSequence(Dirichlet *dPtr)
{
  // subroutine statement
  pushSource("module mod_");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());
  flushSource();

  writeSource("contains");
  com();

  
  pushSource("subroutine ");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());

  pushSource("(NDF_PCP,nsetno,          &");
  flushSource();
  
  writeSource("  firstNsetPtr,              &");

  pushSource( "  ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,ipd_");    // ipdinfo
  
  Variable *vPtr = dPtr->GetDcondVariablePtr();
  pushSource(vPtr->GetName());

  pushSource(",npmax           &");
  flushSource();


  /* Additional variables */
  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  pushVariableListInCalled( varPtrLst);

  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");
  flushSource();

  return;
}

void MT_aist90PCP::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // matrix oriented auto variables
  writeInteger4sc("i,j,k");
  writeInteger4sc("iptf,iptt,iptf2,iptt2");
  writeInteger4sc("irptr");
  com();
  writeInteger4Ptr1("INDB1,INDB2");
  writeReal8Ptr1("BNDVAL");

  return;
}


void MT_aist90PCP::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{
  com();

  SW("!---------------------------");
  SW("! ieq dirichlet equation number");
  SW("!---------------------------");
  com();
 
  writeSource("  if(i .eq. 1) then");
  writeSource("    allocate(INDB1 (nodes))");
  writeSource("    allocate(INDB2 (nodes))");
  writeSource("    allocate(BNDVAL(nodes))");
  writeSource("  endif");
  com();

  writeSource("  INDB1(i) = nd");

  pushSource ("  INDB2(i) = ipd_");
  Variable *dvarPtr = dPtr->GetDcondVariablePtr();
  pushSource(dvarPtr->GetName());
  pushSource("(nd)+1");
  flushSource();
  
  com();
  writeSource("  BNDVAL(i) = u");
  com();


  //  comment();
  //  there will be a loop
  return;
}

