/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90SKYLINEneumann.cpp
 *  Date     : 2000/12/11
 *  Modified : 2000/12/11
 *  
 *  Purpose  : feelfem90 program model/SKYLINE storage neumann condition
 *            (derived from PAMG data model)
 *  
 */

#include "MT_ff90SKYLINE.hpp"
#include "Neumann.hpp"

void MT_ff90SKYLINE::DoNeumannRoutineHeaderMT(Neumann *nPtr)
{
  DoNeumannArgumentSequenceMT( nPtr );
  SourceStarters();

  F90useNeumannPM();

  fortImplicit();
  com();

  DoNeumannArgumentVariableDefinitionsPM(nPtr);
  com();

  doNeumannVariableDefinitionsMT();
  com();
  
  return;
}


void MT_ff90SKYLINE::DoNeumannArgumentSequenceMT(Neumann *nPtr)
{
  pushSource("module mod_");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  flushSource();
  
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  pushSource("(   nbedatno,firstEdatPtr, &");
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


void MT_ff90SKYLINE::DoNeumannApplyMatrixMT(Neumann *nPtr)
{

  /* Prepare ikp (Prepared in PM dependent section)*/
  writeSource("  do j=1,NDF");

  writeSource("    nd     = bielem(ienp(j),i)");
  writeSource("    ikp(j) = ipd(nd)+iedp(j)");
  writeSource("  end do");
  com();

  if(nPtr->GetMatNonZero() != 0) {  
    writeSource("  do j=1,NDF");
    writeSource("    jp = ikp(j)");
    com();
    
    writeSource("    do k=1,NDF");
    writeSource("      kp = ikp(k)");
    com();

    writeSource("      if(kp .EQ. jp) goto 705");
    writeSource("      if(kp .GT. jp) goto 710");
    com();

    writeSource("      lp = KLD(jp+1)-jp+kp");
    writeSource("      VKGI(lp) = VKGI(lp) + ba(j,k)");
    writeSource("      goto 700");
    com();
    
    writeSource("705   VKGD(jp) = VKGD(jp) + ba(j,j)");
    writeSource("      goto 700");
    com();

    writeSource("710   lp = KLD(kp+1)-kp+jp");
    writeSource("      VKGS(lp) = VKGS(lp) + ba(j,k)");
    com();

    writeSource("700 continue");
    writeSource("    end do");  // former 700
    com();    
    
    writeSource("  end do");  // former 600

    com();
  }// end of ba block

  writeSource("  do j=1,NDF");
  writeSource("    vfg(ikp(j))=vfg(ikp(j))+bb(j)");
  writeSource("  end do");
  comment();

  return;
}

// neumann routine matrix dependent parts
void MT_ff90SKYLINE::doNeumannVariableDefinitionsMT(void)
{
  writeMatrixDeclarations();
  writeInteger4sc("kp,lp");
  return;
}
