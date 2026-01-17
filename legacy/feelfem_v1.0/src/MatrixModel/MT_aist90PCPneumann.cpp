/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_aist90PCPneumann.cpp
 *  Date     : 2002/06/28   (copy from MT_ff90AMGCRSneumann.cpp)XS
 *  Modified : 
 *  
 *  Purpose  : feelfem90 program model/AMGCRS storage neumann condition
 *            (derived from PAMG data model)
 *  
 */

#include "MT_aist90PCP.hpp"
#include "Neumann.hpp"

void MT_aist90PCP::DoNeumannRoutineHeaderMT(Neumann *nPtr)
{
  DoNeumannArgumentSequenceMT( nPtr );
  SourceStarters();

  F90useNeumannPM();

  writeSource("use pcp90");
  com();

  fortImplicit();
  com();

  DoNeumannArgumentVariableDefinitionsPM(nPtr);
  com();

  doNeumannVariableDefinitionsMT();
  com();
  
  return;
}


void MT_aist90PCP::DoNeumannArgumentSequenceMT(Neumann *nPtr)
{
  pushSource("module mod_");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  flushSource();
  
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  pushSource("(myrank,nprocs,nbedatno,IEDOM,NDF_PCP,firstEdatPtr, &");
  flushSource();

  pushSource("   npmax,");
  pushCoordinateSource();
  pushSource(",ipf,ipd &");
  flushSource();
  
  pushSource("   ");

  /* Additional variables */
  orderedPtrList <Variable *>varPtrLst = nPtr->GetVariablePtrLst();
  //  listIterator <Variable *>itr(varPtrLst);

  /* Domain variables */
  pushVariableListInCalled( varPtrLst );

  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");

  flushSource();

  return;
}

void MT_aist90PCP::DoNeumannApplyMatrixMT(Neumann *nPtr)
{

  /* Prepare ikp (Prepared in PM dependent section)*/
  writeSource("  do j=1,NDF");

  writeSource("    nd     = bielem(ienp(j),i)");
  writeSource("    ikp(j) = ipd(nd)+iedp(j)");
  writeSource("  end do");
  com();

  if(nPtr->GetMatNonZero() != 0) {  
    writeSource("!----------------------------");
    writeSource("! Assemble for ba(*,*) in PCP");
    writeSource("!----------------------------");

    writeSource("  call PCP_MKMATX(nbp,NDF_PCP,bielem(1:nbp,i), &");
    writeSource("                  ba,NELT,npmax,AMAT,ICOL0,ICPNT )");
  }  
  com();
  
  writeSource("  do j=1,NDF");
  writeSource("    vfg(ikp(j))=vfg(ikp(j))+bb(j)");
  writeSource("  end do");
  comment();

  return;
}

// neumann routine matrix dependent parts
void MT_aist90PCP::doNeumannVariableDefinitionsMT(void)
{
  writeMatrixDeclarations();
  writeInteger4sc("iptf,iptt");
  return;
}
