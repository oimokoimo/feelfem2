/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90vecCRSelem.cpp
 *  Date     : 2001/11/29 (copy from MT_ff90AMGCRSelem.cpp)
 *  Modified : 
 *  
 *  Purpose  : Element assembly routine for model feelfem90vec/CRS vector
 *  
 */
#include <stdio.h>
#include "feelfuncs.hpp"
#include "MT_ff90vecCRS.hpp"

void MT_ff90vecCRS::DoElemRoutineHeaderMT(SolveElement *sePtr)
{
  doElemArgumentSequenceMT(sePtr);
  doElemStarters();                // just call SourceStarters();

  // use sentences
  F90useAlways();
  fortImplicit();

  DoElemDeclareArgumentVariablesPM( sePtr );
  doElemVariableDefinitionsMT();                //

}

void MT_ff90vecCRS::doElemArgumentSequenceMT(SolveElement *sePtr)
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

void MT_ff90vecCRS::DoElemAssembleMatrix(int flag)
{
  // flag has no meaning.

  COMMENTlong("Vector assemble");

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

  return;
}

