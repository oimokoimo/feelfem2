/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_aist90PCPelem.cpp
 *  Date     : 2002/06/28 (copied from MT_ff90AMGCRSelem.cpp)
 *  Modified : 
 *  
 *  Purpose  : Element assembly routine for model aistpcp90/PCP
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
#include <cstdio>
#include "feelfuncs.hpp"
#include "MT_aist90PCP.hpp"

void MT_aist90PCP::DoElemRoutineHeaderMT(SolveElement *sePtr)
{
  doElemArgumentSequenceMT(sePtr);
  doElemStarters();                // just call SourceStarters();

  // use sentences
  F90useElemPM(sePtr);             // use for ecal routines, etc.
  F90useAlways();

  writeSource("use pcp90");
  com();

  fortImplicit();

  doElemDeclareArgumentVariablesPM( sePtr );
  doElemVariableDefinitionsMT();                //

}

void MT_aist90PCP::doElemArgumentSequenceMT(SolveElement *sePtr)
{
  int fem_exchange_variables;
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  // module s
  pushSource("module mod_");
  pushElemRoutineName(sePtr->GetSolveNo());
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushElemRoutineName(sePtr->GetSolveNo());
  //  pushSource("(myrank,nprocs,IEDOM,NPP,ielem,matno,nelem,np,&");
  pushSource("(myrank,nprocs,IEDOM,ielem,matno,nelem,np,&");
  flushSource();

  pushSource("                 ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax           &");
  flushSource();
  
  // related variables 
  pushSource( "     ");
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }

  pushSource(",");
  pushMatrixArgumentsAllocated();
  pushSource(")");
  flushSource();
  return;
}

void MT_aist90PCP::DoElemAssembleMatrix(int flag)
{
  if(flag == MY_ELEMENT) {

    writeSource(" if(iedom(i) .eq. myrank) then");
    writeSource("   call PCP_MKMATX(np,NDF_NODE,ielem(1:np,i)     , &");
    writeSource("                   ea,NELT,npmax,AMAT,ICOL0,ICPNT   )");
    com();

    // move to inside iedom(i) if block is enough for PCP (02/12/10)
    writeSource("   do j=1,NDF");
    writeSource("     vfg(ikp(j)) = vfg(ikp(j))+eb(j)");
    //    writeSource("   NPP(iedom(i)+1,ikp(j)) = 1");
    writeSource("   end do");

    writeSource(" end if");
    com();

    com();

  }
  else {

    fprintf(stderr,"Illegal flag in MT_aist90PCPelem\n");
    abortExit(1);

  }
  return;
}

//  elem routine matrix dependent parts
void MT_aist90PCP::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();
  //integer                                  :: ncof
  writeInteger4sc("ip,jp");


  return;
}
