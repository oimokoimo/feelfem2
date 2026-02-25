/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSLOCelem.cpp
 *  Date     : 2000/03/30
 *  Modified : 2000/03/30
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Element assembly routine for model P2/CRSLOC
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


void MT_P2CRSLOC::DoElemRoutineHeaderMT(SolveElement *sePtr)
{
  doElemArgumentSequenceMT(sePtr);
  doElemStarters();                // just call SourceStarters();

  doElemDeclareArgumentVariablesPM( sePtr );

  doElemVariableDefinitionsMT(); 

  return;
}

void MT_P2CRSLOC::doElemArgumentSequenceMT(SolveElement *sePtr)
{
  int fem_exchange_variables;
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  pushSource("      subroutine ");
  pushElemRoutineName(sePtr->GetSolveNo());
  pushSource("(mypeid,nprocs,");
  flushSource();

  writeSource("     $  isumup,myeqfrom,myeqto,neqtotal,");
  writeSource("     $  enptr,con,nelem,");
  writeSource("     $  x,y,ipf,ipd,npmax,");

  itr.init();  if(!itr) {
  pushSource ("     $  ");
  for(itr.init(); !itr;++itr) {
    string a;
    NameVariableInCalled(itr(),a);
    pushSource(a);
    pushSource(",");
  }
  flushSource();
  }

  writeSource("     $  enptr_ex,con_ex,nelem_ex,");
  writeSource("     $  nouter,ndno,peno,x_ex,y_ex,ipfex,ipdex,");
  
  if(fem_exchange_variables >0) {
    pushSource("     $     ");
    for(itr.init(); !itr;++itr) {
      if(itr()->GetType() == VAR_FEM) {
	pushFEMVariableExternalInCalled( itr() );
	pushSource(",");      
      }
    }
    flushSource();
  }
  
  pushSource("     $ ");
  pushMatrixArgumentsCalled();
  pushSource(",ncof)");
  flushSource();
  return;
}

void MT_P2CRSLOC::DoElemAssembleMatrix(int flag)
{
  if(flag == MY_ELEMENT) {
    writeSource("            do 1015 j=1,NDF");
    writeSource("               ip = ikp(j)");
    writeSource("               if(ip .eq. 0) goto 1015");
    com();
    writeSource("               iptf = iptrcol(ip)");
    writeSource("               iptt = iptrcol(ip+1)-1");
    writeSource("               do 1016 k=1,NDF");
    writeSource("                  jp = jkp(k)");
    writeSource("                  do 1017 L=iptf,iptt");
    writeSource("                     if(indrow(L) .eq. jp) goto 1018");
    writeSource(" 1017              continue");
    writeSource("*--- err");
    writeSource("                  write(*,*) '??? ',ip,jp,'(',mypeid,')'");
    writeSource("                  call abortexit(mypeid,'1017 indrow')");
    writeSource("*--- err");
    writeSource(" 1018              continue");
    writeSource("                  valmat(L) = valmat(L)+ea(j,k)"); // P2
    writeSource(" 1016           continue");
    writeSource(" 1015        continue");
    com();
    writeSource("            do 1019 j=1,NDF");
    writeSource("               if(ikp(j) .eq. 0) goto 1019");
    writeSource("               vfg(ikp(j)) = vfg(ikp(j)) + eb(j)");
    writeSource(" 1019       continue");
    writeSource("*****      endif");   //P2 LIMIT
  }
  else {
    writeSource("            do 2015 j=1,NDF");
    writeSource("               ip = ikp(j)");
    writeSource("               if(ip .eq. 0) goto 2015");
    writeSource("*");
    writeSource("               iptf = iptrcol(ip)");
    writeSource("               iptt = iptrcol(ip+1)-1");
    writeSource("               do 2016 k=1,NDF");
    writeSource("                  jp = jkp(k)");
    writeSource("                  do 2017 L=iptf,iptt");
    writeSource("                     if(indrow(L) .eq. jp) goto 2018");
    writeSource(" 2017              continue");
    writeSource("*--- err");
    writeSource("                  write(*,*) 'in ex',ip,jp,'(',mypeid,')'");
    writeSource("                  call abortexit(mypeid,'indrow(ex)')");
    writeSource("*--- err");
    writeSource(" 2018              continue");
    writeSource("                  valmat(L) = valmat(L)+ea(j,k)");
    writeSource(" 2016           continue");
    writeSource(" 2015        continue");
    writeSource("*---");
    writeSource("            do 2019 j=1,NDF");
    writeSource("               if(ikp(j) .eq. 0) goto 2019");
    writeSource("               vfg(ikp(j)) = vfg(ikp(j)) + eb(j)");
    writeSource(" 2019       continue");
    writeSource("*----");
    writeSource("*****     endif");   //P2 LIMIT
  }
  return;
}

