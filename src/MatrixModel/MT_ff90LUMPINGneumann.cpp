/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90LUMPINGneumann.cpp
 *  Date     : 2002/10/07 (Copy from MT_ff90SKYLINEneumann.cpp)
 *  Modified : 
 *  
 *  Purpose  : feelfem90 program model/LUMPING storage neumann condition
 *            (derived from PAMG data model)
 *
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

#include "MT_ff90LUMPING.hpp"
#include "Neumann.hpp"

void MT_ff90LUMPING::DoNeumannRoutineHeaderMT(Neumann *nPtr)
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


void MT_ff90LUMPING::DoNeumannArgumentSequenceMT(Neumann *nPtr)
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


void MT_ff90LUMPING::DoNeumannApplyMatrixMT(Neumann *nPtr)
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

    writeSource("      VKGI(jp) = VKGI(jp) + ba(j,k)");
    com();
    writeSource("    end do  ! k loop");  // former 700
    com();    
    
    writeSource("  end do    ! j loop");  // former 600

    com();
  }// end of ba block

  writeSource("  do j=1,NDF");
  writeSource("    vfg(ikp(j))=vfg(ikp(j))+bb(j)");
  writeSource("  end do");
  comment();

  return;
}

// neumann routine matrix dependent parts
void MT_ff90LUMPING::doNeumannVariableDefinitionsMT(void)
{
  writeMatrixDeclarations();
  writeInteger4sc("kp,lp");
  return;
}
