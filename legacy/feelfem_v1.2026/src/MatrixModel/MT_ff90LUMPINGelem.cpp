/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90LUMPINGelem.cpp
 *  Date     : 2002/10/07 (copy from MT_ff90SKYLINEelem.cpp)
 *  Modified : 
 *  
 *  Purpose  : Element assembly routine for model feelfem90/LUMPING
 *  
 */
#include <stdio.h>
#include "feelfuncs.hpp"
#include "MT_ff90LUMPING.hpp"

void MT_ff90LUMPING::DoElemRoutineHeaderMT(SolveElement *sePtr)
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

void MT_ff90LUMPING::doElemArgumentSequenceMT(SolveElement *sePtr)
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

void MT_ff90LUMPING::DoElemAssembleMatrix(int flag)
{
  if(flag == MY_ELEMENT) {

    writeSource("   do j=1,NDF");
    writeSource("     jp = ikp(j)");
    com();
    writeSource("     VFG(jp)  = VFG(jp)  + eb(j)");
    com();

    writeSource("     do k=1,NDF");
    writeSource("       kp= ikp(k)");
    com();


    writeSource("! lumping");
    writeSource("       VKGD(jp) = VKGD(jp) + ea(j,k)");


    writeSource("     end do ! for k loop");
    com();
    writeSource("   end do   ! for j loop");
    com();

  }
  else {

    fprintf(stderr,"Illegal flag in MT_ff90LUMPINGelem\n");
    abortExit(1);

  }
  return;
}

//  elem routine matrix dependent parts
void MT_ff90LUMPING::doElemVariableDefinitionsMT()
{
  writeMatrixDeclarations();

  writeInteger4sc("jp,kp");
  return;
}
