/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90PAMGCRSneumann.cpp
 *  Date     : 2000/10/25
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelfem90 program model/PAMG-CRS storage neumann condition
 *  
 */

#include "MT_ff90PAMGCRS.hpp"
#include "Neumann.hpp"

void MT_ff90PAMGCRS::DoNeumannRoutineHeaderMT(Neumann *nPtr)
{
  DoNeumannArgumentSequenceMT( nPtr );
  SourceStarters();

  F90useNeumannPM();

  fortImplicit();
  com();

  DoNeumannArgumentVariableDefinitionsPM(nPtr);
  com();
  writeMatrixDeclarations();
  com();
  
  return;
}


void MT_ff90PAMGCRS::DoNeumannArgumentSequenceMT(Neumann *nPtr)
{
  pushSource("module mod_");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  flushSource();
  
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushNeumannRoutineName(nPtr->GetSolveNo(),nPtr->GetNcondNo());
  pushSource("(mypeid,nprocs,                     &");
  flushSource();

  writeSource("   nbedatno,firstDramaEdatPtr,isumup, &");

  pushSource("   npmax,");
  pushCoordinateSource();
  pushSource(",ipf,ipd, &");
  flushSource();
  
  pushSource("   nouter,ndno,peno,ipf_ex,ipd_ex,");
  pushCoordinateExternalSource();
  pushSource(" &");
  flushSource();

  pushSource("   ");

  /* Additional variables */
  orderedPtrList   <Variable *>varPtrLst = nPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  /* Domain variables */
  pushVariableAndFEMExternalListInCalled( varPtrLst );

  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");

  flushSource();

  return;
}

void MT_ff90PAMGCRS::DoNeumannApplyMatrixMT(Neumann *nPtr)
{

  /* Prepare ikp,jkp (Formerly in PM)*/
  writeSource("      do 400 j=1,NDF");

  writeSource("       ind = bcon(1,ipos_from + ienp(j)-1)");
  writeSource("       ipe = bcon(2,ipos_from + ienp(j)-1)");
  com();
  writeSource("       if(ipe .NE. mypeid) then");
  com();
  writeSource("        nd = ndsearch_ex2(ind,ipe,ndno,peno,nouter)");
  writeSource("        if(nd .LT. 1) then");
  writeSource("          write(*,*) 'Cannot find ndex(ncond)'");
  writeSource("          call abortexit(mypeid)");
  writeSource("        endif");
  writeSource("        ikp(j) = 0");
  writeSource("        jkp(j) = ipd_halo(nd)+iedp(j)+neq   ! PAMG/CRS");
  com();
  writeSource("       else");
  com();
  writeSource("        ikp(j) = ipd(ind)+iedp(j)");
  writeSource("        jkp(j) = ikp(j)                     ! PAMG/CRS");
  writeSource("       endif");
  com();

  writeSource(" 400  continue");
  com();

  if(nPtr->GetMatNonZero() != 0) {
    writeSource("!-----------------");
    writeSource("! Loop for ba(*,*)");
    writeSource("!-----------------");
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
    writeSource("!--- err");
    writeSource("        write(*,*) '???(ncond 607)',ip,jp,'(',mypeid,')'");
    writeSource("        call abortexit(mypeid)");
    writeSource("!--- err");
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
