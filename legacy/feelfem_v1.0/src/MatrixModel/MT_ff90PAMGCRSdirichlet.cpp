/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90PAMGCRSdirichlet.cpp
 *  Date     : 2000/04/25
 *  Modified : 2000/05/09
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : FEEL P2 program model/CRS storage dirichlet condition
 *  
 */
#define SW writeSource

#include "feelfuncs.hpp"

#include "MT_ff90PAMGCRS.hpp"
#include "Dirichlet.hpp"


void MT_ff90PAMGCRS::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
{
  DoDirichletArgumentSequence( dPtr );
  SourceStarters();

  F90useDirichletPM();

  fortImplicit();
  com();

  DoDirichletArgumentVariableDefinitionsPM(dPtr);
  com();
  writeMatrixDeclarations();
  com();

  return;
}


void MT_ff90PAMGCRS::DoDirichletArgumentSequence(Dirichlet *dPtr)
{
  // subroutine statement
  pushSource("module mod_");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());
  flushSource();

  writeSource("contains");
  com();

  
  pushSource("subroutine ");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());
  pushSource("(mypeid,nprocs,     &");
  flushSource();
  
  writeSource("  nsetno,firstDramaNsetPtr,              &");
  writeSource("  isumup,                                &");
  writeSource("  enptr,con,nelem,                       &");

  pushSource( "  ");
  pushCoordinateSource();
  pushSource(",ipf,ipd,npmax,                     &");
  flushSource();

  writeSource("  enptr_ex,con_ex,nelem_ex,              &");

  pushSource("  ndno,peno,");
  pushCoordinateExternalSource();
  pushSource(",ipf_ex,ipd_ex,nouter        &");  
  flushSource();

  /* Additional variables */
  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  pushVariableListInCalled( varPtrLst);

  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    pushSource(",");
    pushFEMVariableExternalInCalled(itr());
  }

  pushSource(",");
  pushMatrixArgumentsCalled();
  pushSource(")");
  flushSource();

  return;
}

void MT_ff90PAMGCRS::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // matrix related auto variables
  writeSource("integer                        :: iptf,iptt,iptf2,iptt2");
  writeSource("integer                        :: iptf_all,iptt_all");
  writeSource("integer                        :: irptr,irptr_local");

  return;
}

void MT_ff90PAMGCRS::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{

  //  writeSource("myeqfrom = 1   ! AMG/CRS Global number for my equation");
  //  writeSource("myeqto   = neq ! AMG/CRS Global number for my equation");
  //  com();
  //  writeSource("call setdramanset(nsetno,firstDramaNsetPtr,nodes,np,dcon,dinfo)");


  //  comment();
  //  writeSource("do 100 i=1,nodes");
  //  com();
  //
  //  writeSource("  ind = dcon(1,i)");
  //  writeSource("  ipe = dcon(2,i)");
  //
  //  comment();
  //  writeSource("! If the Dirichlet node is in my PE region, row and column");
  //  writeSource("! If the Dirichlet node is NOT in my PE region,");
  //  writeSource("! and it relates my region, column");
  //  comment();
  //
  //  writeSource("  if(ipe .NE. mypeid) then");
  //  writeSource("    nd = ndsearch_ex2(ind,ipe,ndno,peno,nouter)");
  //  writeSource("    if(nd .LT. 1) goto 100");
  //  com();
  //
  //  writeSource("    ieq = 0");
  //  writeSource("    jeq = ipd_halo(nd)+dinfo(1,i)+neq      ! PAMG/CRS");
  //  com();
  //
  //  switch(getSpaceDimension()) {
  //  case 1:
  //    writeSource("    x_dpt = x_ex(nd)");
  //    break;
  //
  //  case 2:
  //    writeSource("    x_dpt = x_ex(nd)");
  //    writeSource("    y_dpt = y_ex(nd)");
  //    break;
  //
  //  case 3:
  //    writeSource("    x_dpt = x_ex(nd)");
  //    writeSource("    y_dpt = y_ex(nd)");
  //    writeSource("    z_dpt = z_ex(nd)");
  //    break;
  //  }
  //
  //  /* External FEM Variable */
  //  orderedPtrList <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  //  listIterator <Variable *>itr(varPtrLst);
  //
  //  for(itr.init(); !itr; ++itr ){
  //    if(itr()->GetType() != VAR_FEM) continue;
  //
  //    pushSource("    ");
  //    pushFEMVariableInCalled(itr());
  //    pushSource("_dpt = ");
  //    pushFEMVariableExternalInCalled(itr());      // external variable
  //    pushSource("(nd)");
  //    flushSource();
  //  }
  //
  //  com();
  //  writeSource("   else");
  //  com();
  //
  //  writeSource("    ieq = ipd(ind)+dinfo(1,i)");
  //  writeSource("    jeq = ieq                   ! AMG/CRS local eq number for my own");
  //  com();
  //
  //  switch(getSpaceDimension()) {
  //  case 1:
  //    writeSource("    x_dpt = x(ind)");
  //    break;
  //
  //  case 2:
  //    writeSource("    x_dpt = x(ind)");
  //    writeSource("    y_dpt = y(ind)");
  //    break;
  //
  //  case 3:
  //    writeSource("    x_dpt = x(ind)");
  //    writeSource("    y_dpt = y(ind)");
  //    writeSource("    z_dpt = z(ind)");
  //    break;
  //  }
  //
  //
  //  for(itr.init(); !itr; ++itr ){
  //    if(itr()->GetType() != VAR_FEM) continue;
  //    
  //    pushSource("        ");
  //    pushFEMVariableInCalled(itr());
  //    pushSource("_dpt = ");
  //    pushFEMVariableInCalled(itr());              // own variable
  //    pushSource("(ind)");
  //    flushSource();
  //  }
  //  com();
  //
  //  writeSource("  endif");
  //  com();  
  //
  //
  //  doSetDirichletValue(dPtr);
  //  

  com();
  SW("!---------------------------");
  SW("! ieq local  equation number");
  SW("! jeq global equation number");
  SW("!---------------------------");
  com();

  SW("!*********");
  SW("! row ieq");
  SW("!*********");
  SW("   if(ieq .eq. 0) goto  150");
  com();

  SW("   iptf = iptrcol(ieq  )");
  SW("   iptt = iptrcol(ieq+1)-1");
  com();

  SW("   do j=iptf,iptt");
  SW("     if(indrow(j) .eq. jeq) then");
  SW("       valmat(j) = 1.0d0");
  SW("     else");
  SW("       valmat(j) = 0.0d0");
  SW("     endif");
  SW("   end do   ! j=iptf,iptt");

  SW("   vfg(ieq) = u");
  com();

  SW("!**********");
  SW("! column");
  SW("!**********");
  SW(" 150 continue");
  com();


  SW("  if( ieq  .ne. 0) then");

  SW("!");
  SW("! Assume non-zero element is symmetric");
  SW("!");

  SW("    iptf = iptrcol(ieq  )");
  SW("    iptt = iptrcol(ieq+1)-1");
  com();

  SW("    do 160 j=iptf,iptt");
  SW("      irptr = indrow(j)");
  SW("      if(irptr .LT. myeqfrom .OR. irptr .GT. myeqto) goto 160");
  SW("      if(irptr .EQ. jeq ) goto 160");
  com();

  SW("      irptr_local = irptr - myeqfrom+1");
  SW("      if(irptr_local .LT. 1 .OR. irptr_local .GT. neq) then");
  SW("        write(*,*) 'irptr_local ERROR ',irptr_local");
  SW("        call abortexit(mypeid)");
  SW("      endif");
  com();

  SW("      iptf2 = iptrcol(irptr_local)");
  SW("      iptt2 = iptrcol(irptr_local+1)-1");
  SW("      do 165 k=iptf2,iptt2");
  SW("        if(indrow(k) .eq. jeq) goto 170");
  SW(" 165  continue");
  com();
  
  SW("!");
  SW("      write(*,*) 'cannot find in dcond'");
  SW("      call abortexit(mypeid)");
  SW("!");

  SW(" 170   continue");
  SW("      vfg(irptr_local)=vfg(irptr_local)-valmat(k)*u");
  SW("      valmat(k) = 0.0d0");
  SW(" 160 continue");
  com();

  SW("!");
  SW("! end of my case");
  SW("!");

  SW("    else");
  SW("!");
  SW("! now search all!!!!!!!!!!!!!");
  SW("!");
  SW("    do 200 j=1,neq");
  SW("     iptf_all = iptrcol(j)");
  SW("     iptt_all = iptrcol(j+1)-1");
  SW("     do 210 k=iptf_all,iptt_all");
  SW("       if(indrow(k) .eq. jeq ) then");
  SW("        vfg(j) = vfg(j) - valmat(k)*u");
  SW("        valmat(k) =0.0d0");
  SW("        goto 200");
  SW("       endif");
  SW(" 210 continue");
  SW(" 200 continue");
  SW("    endif");

  SW("!");
  SW("! end of column");
  SW("!");

  //  SW(" 100  continue");
  //  comment();

  return;
}
