/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSLOCdirichlet.cpp
 *  Date     : 2000/04/25
 *  Modified : 2000/05/09
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : FEEL P2 program model/CRS storage dirichlet condition
 *  
 */
#define SW writeSource

#include "MT_P2CRSLOC.hpp"
#include "Dirichlet.hpp"

void MT_P2CRSLOC::DoDirichletRoutineHeaderMT(Dirichlet *dPtr)
{
  DoDirichletArgumentSequence( dPtr );
  SourceStarters();

  //  fortImplicit();    // f77 version in SourceStarters();
  com();

  DoDirichletArgumentVariableDefinitionsPM(dPtr);
  com();
  writeMatrixDeclarations();
  com();

  return;
}

void MT_P2CRSLOC::DoDirichletArgumentSequence(Dirichlet *dPtr)
{
  pushSource("      subroutine ");
  pushDirichletRoutineName(dPtr->GetSolveNo(),dPtr->GetDcondNo());
  pushSource("(mypeid,nprocs,");
  flushSource();
  
  writeSource("     $     nsetno,nsetnodes,nsetnp,dcon,dinfo,");
  writeSource("     $     isumup,myeqfrom,myeqto,neqtotal,");
  writeSource("     $     enptr,con,nelem,");
  writeSource("     $     x,y,ipf,ipd,npmax,");
  writeSource("     $     enptr_ex,con_ex,nelem_ex,");
  writeSource("     $     ndno,peno,x_ex,y_ex,ipfex,ipdex,nouter,");
  writeSource("     $     iptrcol,indrow,valmat,vfg,neq,ncof");

  /* Additional variables */
  pushSource("     $ ");
  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
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

void MT_P2CRSLOC::doDirichletAutoVariableDefinitionsMT(Dirichlet *dPtr)
{
  // auto variables for matrix 
  // do nothing, because of Fortran 77
  return;
}


void MT_P2CRSLOC::DoDirichletApplyMatrixMT(Dirichlet *dPtr)
{
  orderedPtrList   <Variable *>varPtrLst = dPtr->GetVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  writeSource("*--------------------");
  writeSource("* Confirm nsetnp is 1");
  writeSource("*--------------------");
  writeSource("      if(nsetnp .NE. 1) then");
  writeSource("        write(*,*) 'nsetnp is not 1'");
  writeSource("        call abortexit(mypeid,'nsetnp error in dcond')");
  writeSource("      endif");

  comment();
  writeSource("      do 100 i=1,nsetnodes");
  com();
  writeSource("       ind = dcon(1,i)");
  writeSource("       ipe = dcon(2,i)");
  comment();
  writeSource("* If the Dirichlet node is in my PE region, row and column");
  writeSource("* If the Dirichlet node is NOT in my PE region,");
  writeSource("* and it relates my region, column");
  comment();

  writeSource("       if(ipe .NE. mypeid) then");
  writeSource("        nd = ndsearch_ex2(ind,ipe,ndno,peno,nouter)");
  writeSource("        if(nd .LT. 1) goto 100");
  com();

  writeSource("        ieq = 0");
  writeSource("        jeq = ipdex(nd)+dinfo(1,i)+isumup(ipe+1)");
  com();

  writeSource("        x_dpt = x_ex(nd)");
  writeSource("        y_dpt = y_ex(nd)");

  /* External FEM Variable */
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    
    pushSource("        fem_");
    pushSource(itr()->GetName());
    pushSource("_dpt = ");
    pushFEMVariableExternalInCalled(itr());
    pushSource("(nd)");
    flushSource();
  }

  com();
  writeSource("       else");
  com();

  writeSource("        ieq = ipd(ind)+dinfo(1,i)");
  writeSource("        jeq = ieq                +isumup(ipe+1)");
  com();

  writeSource("        x_dpt = x(ind)");
  writeSource("        y_dpt = y(ind)");
  for(itr.init(); !itr; ++itr ){
    if(itr()->GetType() != VAR_FEM) continue;
    
    pushSource("        fem_");
    pushSource(itr()->GetName());
    pushSource("_dpt = ");
    pushFEMVariableInCalled(itr());    
    pushSource("(ind)");
    flushSource();
  }
  com();

  writeSource("       endif");
  com();  


  pushSource( "       u   = ");
  pushSource( dirichletP2DOTEMP(dPtr->testGetTestExpression()) );
  flushSource();
  com();
  

  SW("*---------------------------");
  SW("* ieq local  equation number");
  SW("* jeq global equation number");
  SW("*---------------------------");
  com();
  SW("**********");
  SW("* row ieq");
  SW("**********");
  SW("         if(ieq .eq. 0) goto  150");
  com();
  SW("         iptf = iptrcol(ieq  )");
  SW("         iptt = iptrcol(ieq+1)-1");
  com();

  SW("         do 110 j=iptf,iptt");
  SW("            if(indrow(j) .eq. jeq) then");
  SW("               valmat(j) = 1.0d0");
  SW("            else");
  SW("               valmat(j) = 0.0d0");
  SW("            endif");
  SW(" 110     continue");
  SW("         vfg(ieq) = u");
  SW("");
  SW("***********");
  SW("* column");
  SW("***********");
  SW(" 150     continue");
  SW("");
  SW("**");
  SW("         if( ieq  .ne. 0) then");
  SW("*");
  SW("* Assume non-zero element is symmetric");
  SW("*");
  SW("            iptf = iptrcol(ieq  )");
  SW("            iptt = iptrcol(ieq+1)-1");
  SW("");
  SW("            do 160 j=iptf,iptt");
  SW("               irptr = indrow(j)");
  SW("               if(irptr .LT. myeqfrom .OR. irptr .GT. myeqto) goto 160");
  SW("               if(irptr .EQ. jeq ) goto 160");
  SW("");
  SW("               irptr_local = irptr - myeqfrom+1");
  SW("               if(irptr_local .LT. 1 .OR. irptr_local .GT. neq) then");
  SW("                  write(*,*) 'irptr_local ERROR ',irptr_local");
  SW("                  call abortexit(mypeid,'dcond irptr_local error')");
  SW("               endif");
  SW("");
  SW("               iptf2 = iptrcol(irptr_local)");
  SW("               iptt2 = iptrcol(irptr_local+1)-1");
  SW("               do 165 k=iptf2,iptt2");
  SW("                  if(indrow(k) .eq. jeq) goto 170");
  SW(" 165           continue");
  SW("*");
  SW("               write(*,*) 'cannot find in dcond'");
  SW("               call abortexit(mypeid,'Cannot find dcond in my region')");
  SW("*");
  SW(" 170           continue");
  SW("               vfg(irptr_local)=vfg(irptr_local)-valmat(k)*u");
  SW("               valmat(k) = 0.0d0");
  SW(" 160        continue");
  SW("");
  SW("*");
  SW("* end of my case");
  SW("*");
  SW("         else");
  SW("*");
  SW("* now search all!!!!!!!!!!!!!");
  SW("*");
  SW("            do 200 j=1,neq");
  SW("               iptf_all = iptrcol(j)");
  SW("               iptt_all = iptrcol(j+1)-1");
  SW("               do 210 k=iptf_all,iptt_all");
  SW("                  if(indrow(k) .eq. jeq ) then");
  SW("                     vfg(j) = vfg(j) - valmat(k)*u");
  SW("                     valmat(k) =0.0d0");
  SW("                     goto 200");
  SW("                  endif");
  SW(" 210           continue");
  SW(" 200        continue");
  SW("         endif");
  SW("*");
  SW("* end of column");
  SW("*");
  SW(" 100  continue");

  comment();

  return;
}
