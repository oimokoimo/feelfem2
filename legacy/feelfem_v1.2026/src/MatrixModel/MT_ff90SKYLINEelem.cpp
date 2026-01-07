/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90SKYLINEelem.cpp
 *  Date     : 2002/03/06  (copied from MT_ff90AMGCRS.cpp)
 *  Modified : 
 *  
 *  Purpose  : Element assembly routine for model feelfem90/SKYLINE
 *  
 */
#include <stdio.h>
#include "feelfuncs.hpp"
#include "MT_ff90SKYLINE.hpp"

void MT_ff90SKYLINE::DoElemRoutineHeaderMT(SolveElement *sePtr)
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

void MT_ff90SKYLINE::doElemArgumentSequenceMT(SolveElement *sePtr)
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
  pushSource(")");
  flushSource();
  return;
}

void MT_ff90SKYLINE::DoElemAssembleMatrix(int flag)
{
  if(flag == MY_ELEMENT) {

    writeSource("   do 300 j=1,NDF");
    writeSource("     jp = ikp(j)");
    com();

    writeSource("     do 400 k=1,NDF");
    writeSource("       kp= ikp(k)");
    com();

    writeSource("       if(kp .EQ. jp) goto 405");
    writeSource("       if(kp .GT. jp) goto 410");
    com();

    writeSource("       lp = KLD(jp+1)-jp+kp");
    writeSource("       VKGI(lp) = VKGI(lp) + ea(j,k)");
    writeSource("       goto 400");
    com();

    writeSource(" 405   VKGD(jp) = VKGD(jp) + ea(j,j)");
    writeSource("       VFG(jp)  = VFG(jp)  + eb(j)");
    writeSource("       goto 400");
    com();

    writeSource(" 410   kp = ikp(k)");
    writeSource("       lp = KLD(kp+1)-kp+jp");
    writeSource("        VKGS(lp) = VKGS(lp) + ea(j,k)");
    com();

    writeSource(" 400   continue");
    com();

    writeSource(" 300  continue");
    com();

  }
  else {

    fprintf(stderr,"Illegal flag in MT_ff90SKYLINEelem\n");
    abortExit(1);

  }
  return;
}

//  elem routine matrix dependent parts
void MT_ff90SKYLINE::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();

  writeInteger4sc("ip,jp,kp,lp");
  return;
}
