/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90PAMGCRSelem.cpp
 *  Date     : 2000/10/25
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Element assembly routine for model feelfem90/PAMG-CRS
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
#include "MT_ff90PAMGCRS.hpp"

void MT_ff90PAMGCRS::DoElemRoutineHeaderMT(SolveElement *sePtr)
{
  doElemArgumentSequenceMT(sePtr);
  doElemStarters();                // just call SourceStarters();

  // use sentences
  com();
  writeSource("! use sentences");
  com();

  writeSource("use subSolveDrama");  // for ndsearch_ex

  F90useElemPM(sePtr);
  F90useAlways();
  fortImplicit();

  doElemDeclareArgumentVariablesPM( sePtr );
  doElemVariableDefinitionsMT();                //

}

void MT_ff90PAMGCRS::doElemArgumentSequenceMT(SolveElement *sePtr)
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
  pushSource("(mypeid,nprocs,isumup, &");
  flushSource();

  writeSource("                 enptr,con,nelem,      &");

  pushSource("                 ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax,    &");
  flushSource();

  writeSource("                 enptr_ex,con_ex,nelem_ex, &");
  
  pushSource("                 ndno,peno,");
  pushCoordinateExternalSource();
  pushSource(",ipf_ex,ipd_ex,nouter  &");
  flushSource();

  // related variables 
  pushSource( "     ");
  for(itr.init(); !itr;++itr) {
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }

  //exterior node values
  if(fem_exchange_variables >0) {
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushSource(",");
	pushFEMVariableExternalInCalled(itr());
      }
    }
  }
  pushSource(",");
  pushMatrixArgumentsAllocated();
  pushSource(",ncof)");
  flushSource();
  return;
}

void MT_ff90PAMGCRS::DoElemAssembleMatrix(int flag)
{
  if(flag == MY_ELEMENT) {
    writeSource("  do 1015 j=1,NDF");
    writeSource("   ip = ikp(j)");
    writeSource("   if(ip .eq. 0) goto 1015");
    com();

    writeSource("   iptf = iptrcol(ip)");
    writeSource("   iptt = iptrcol(ip+1)-1");
    writeSource("   do 1016 k=1,NDF");
    writeSource("     jp = jkp(k)");
    writeSource("     do 1017 L=iptf,iptt");
    writeSource("       if(indrow(L) .eq. jp) goto 1018");
    writeSource(" 1017 continue");
    writeSource("!--- err");
    writeSource("                  write(*,*) '??? ',ip,jp,'(',mypeid,')'");
    writeSource("                  call abortexit(mypeid)");
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
    writeSource("   do 2015 j=1,NDF");
    writeSource("     ip = ikp(j)");
    writeSource("     if(ip .eq. 0) goto 2015");
    com();

    writeSource("     iptf = iptrcol(ip)");
    writeSource("     iptt = iptrcol(ip+1)-1");
    writeSource("     do 2016 k=1,NDF");
    writeSource("       jp = jkp(k)");
    writeSource("       do 2017 L=iptf,iptt");
    writeSource("       if(indrow(L) .eq. jp) goto 2018");
    writeSource(" 2017 continue");
    writeSource("!--- err");
    writeSource("                  write(*,*) 'in ex',ip,jp,'(',mypeid,')'");
    writeSource("                  call abortexit(mypeid)");
    writeSource("!--- err");
    writeSource(" 2018   continue");
    writeSource("        valmat(L) = valmat(L)+ea(j,k)");
    writeSource(" 2016  continue");
    writeSource(" 2015 continue");
    com();
    writeSource("   do 2019 j=1,NDF");
    writeSource("       if(ikp(j) .eq. 0) goto 2019");
    writeSource("       vfg(ikp(j)) = vfg(ikp(j)) + eb(j)");
    writeSource(" 2019 continue");
    writeSource("!----");
    writeSource("!****     endif");   //P2 LIMIT
  }
  return;
}


