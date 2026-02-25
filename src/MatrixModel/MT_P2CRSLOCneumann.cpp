/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSLOCneumann.cpp
 *  Date     : 2000/05/25
 *  Modified : 2000/05/25
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : FEEL P2 program model/CRSLOC storage neumann condition
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

#include "MT_P2CRSLOC.hpp"
#include "Neumann.hpp"


void MT_P2CRSLOC::DoNeumannRoutineHeaderMT(Neumann *nPtr)
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

void MT_P2CRSLOC::DoNeumannArgumentSequenceMT(Neumann *nPtr)
{
  pushSource("      subroutine ");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  pushSource("(mypeid,nprocs,");
  flushSource();

  writeSource("     $   nbedatno,nbelem,benptr,bcon,bmatno,");
  writeSource("     $   isumup,myeqfrom,myeqto,neqtotal,");
  writeSource("     $   x,y,");
  writeSource("     $   ipf,ipd,npmax,");
  writeSource("     $   ndno,peno,xex,yex,");
  writeSource("     $   ipfex,ipdex,nouter,");

  pushSource("     $   ");
  pushMatrixArgumentsCalled();
  flushSource();

  /* Additional variables */
  pushSource("     $ ");
  orderedPtrList   <Variable *>varPtrLst = nPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  /* Domain variables */
  for(itr.init(); !itr; ++itr ){
    string a;
    pushSource(",");
    NameVariableInCalled(itr(),a);
    pushSource(a);
  }

  /* _ex variables for FEM variable */
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;

    pushSource(",");
    pushFEMVariableExternalInCalled(itr());
  }

  pushSource(")");
  flushSource();

  return;
}

void MT_P2CRSLOC::DoNeumannApplyMatrixMT(Neumann *nPtr)
{

  if(nPtr->GetMatNonZero() != 0) {
    writeSource("*-----------------");
    writeSource("* Loop for ba(*,*)");
    writeSource("*-----------------");
    writeSource("      do 600 j=1,NDF");
    writeSource("       ip   = ikp(j)");
    writeSource("       if(ip .eq. 0) goto 600");
    com();
    
    writeSource("       iptf = iptrcol(ip)");
    writeSource("       iptt = iptrcol(ip+1)-1");
    com();

    writeSource("       do 605 k=1,NDF");
    writeSource("        jp = jkp(k)");
    writeSource("        do 607 L=iptf,iptt");
    writeSource("          if(indrow(L) .EQ. jp) goto 608");
    writeSource(" 607    continue");
    writeSource("*--- err");
    writeSource("        write(*,*) '???',ip,jp,'(',mypeid,')'");
    writeSource("        call abortexit(mypeid,'607 ncond err')");
    writeSource("*--- err");
    com();
    writeSource(" 608    continue");
    writeSource("        valmat(L)=valmat(L)+ba(j,k)");
    com();
    writeSource(" 605   continue");
    writeSource(" 600  continue");
  }
  com();
  
  writeSource("      do 700 j=1,NDF");
  writeSource("       if(ikp(j) .eq. 0) goto 700");
  writeSource("       vfg(ikp(j))=vfg(ikp(j))+bb(j)");
  writeSource(" 700  continue");
  comment();

  return;
}


