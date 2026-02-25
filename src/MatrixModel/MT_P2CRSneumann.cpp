/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSneumann.cpp
 *  Date     : 2000/01/12
 *  Modified : 2000/01/12
 *  Modified : 2002/02/02 orderedPtrList
 *  
 *  Purpose  : FEEL P2 program model/CRS storage neumann condition
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

#include "MT_P2CRS.hpp"
#include "Neumann.hpp"

void MT_P2CRS::DoNeumannRoutineHeaderMT(Neumann *nPtr)
{
  DoNeumannArgumentSequenceMT( nPtr );
  SourceStarters();
  com();

  DoNeumannArgumentVariableDefinitionsPM(nPtr);
  com();
  writeMatrixDeclarations();
  com();
  
  return;
}

void MT_P2CRS::DoNeumannArgumentSequenceMT(Neumann *nPtr)
{
  pushSource("      subroutine ");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  pushSource("(x,y,");             // dependent on class
  flushSource();

  pushSource("     $ ");
  pushMatrixArgumentsCalled();
  pushSource(",ielem,matno,neelem,nenode,IPD"); // dependent on class
  flushSource();

  pushSource("     $ ");
  orderedPtrList   <Variable *>varPtrLst = nPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr; ++itr ){
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }
  pushSource(")");
  flushSource();

  return;
}

void MT_P2CRS::DoNeumannApplyMatrixMT(Neumann *nPtr)
{

  if(nPtr->GetMatNonZero() != 0) {  // 

    writeSource("      do 600 j=1,NDF");
    writeSource("       jp   = ikp(j)");
    writeSource("       iptf = iptrcol(jp)");
    writeSource("       iptt = iptrcol(jp+1)-1");
    writeSource("       do 650 k=1,NDF");
    writeSource("        kp = ikp(k)");
    writeSource("        do 660 L=iptf,iptt");
    writeSource("          if(indrow(L) .EQ. kp) goto 665");
    writeSource(" 660    continue");
    writeSource("*--- err");
    writeSource("        write(*,*) 'cannot find'");
    writeSource("        stop 'ncond'");
    writeSource("*--- err");
    writeSource(" 665    continue");
    com();
    writeSource("        valmat(L)=valmat(L)+ba(j,k)");
    com();
    writeSource(" 650   continue");
    writeSource(" 600  continue");
  }
  com();
  
  writeSource("      do 700 j=1,NDF");
  writeSource("       jp = ikp(j)");
  writeSource("       vfg(jp)=vfg(jp)+bb(j)");
  writeSource(" 700  continue");
  comment();

  return;
}


