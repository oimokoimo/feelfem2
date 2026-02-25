/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90AMGCRSelem.cpp
 *  Date     : 2000/12/27
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Element assembly routine for model feelfem90/AMG-CRS
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
#include "MT_ff90AMGCRS.hpp"

void MT_ff90AMGCRS::DoElemRoutineHeaderMT(SolveElement *sePtr)
{
  doElemArgumentSequenceMT(sePtr);
  doElemStarters();                // just call SourceStarters();

  // use sentences
  F90useElemPM(sePtr);             // use for ecal routines, etc.
  F90useAlways();
  fortImplicit();

  doElemDeclareArgumentVariablesPM( sePtr );
  doElemVariableDefinitionsMT();                //

}

void MT_ff90AMGCRS::doElemArgumentSequenceMT(SolveElement *sePtr)
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
  pushSource("(ielem,matno,nelem,np,        &");
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
  pushSource(",ncof)");
  flushSource();
  return;
}

void MT_ff90AMGCRS::DoElemAssembleMatrix(int flag)
{
  if(flag == MY_ELEMENT) {
    writeSource("  do 1015 j=1,NDF");
    writeSource("   ip = ikp(j)");
    com();

    writeSource("   iptf = iptrcol(ip)");
    writeSource("   iptt = iptrcol(ip+1)-1");
    writeSource("   do 1016 k=1,NDF");
    writeSource("     jp = ikp(k)");
    writeSource("     do 1017 L=iptf,iptt");
    writeSource("       if(indrow(L) .eq. jp) goto 1018");
    writeSource(" 1017 continue");
    writeSource("!--- err");
    writeSource("                  write(*,*) '??? ',ip,jp");
    writeSource("                  call abortexit('elem/loop/1017')");
    writeSource("!--- err");
    writeSource(" 1018           continue");
    writeSource("          valmat(L) = valmat(L)+ea(j,k)"); // feelfem90
    writeSource(" 1016  continue");
    writeSource(" 1015 continue");
    com();
    writeSource("   do 1019 j=1,NDF");
    writeSource("     if(ikp(j) .eq. 0) goto 1019");
    writeSource("     vfg(ikp(j)) = vfg(ikp(j)) + eb(j)");
    writeSource(" 1019   continue");
    writeSource("!****      endif");   //P2 LIMIT
  }
  else {

    fprintf(stderr,"Illegal flag in MT_ff90AMGCRSelem\n");
    abortExit(1);

  }
  return;
}

//  elem routine matrix dependent parts
void MT_ff90AMGCRS::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();
  //integer                                  :: ncof
  writeInteger4sc("ncof");
  writeInteger4sc("ip,jp");
  writeInteger4sc("iptf,iptt");

  return;
}
