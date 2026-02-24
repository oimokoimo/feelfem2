/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90DRAMA.cpp
 *  Date     : 2000/10/16
 *  Modified : 2001/01/31  LINKLEVEL_SUBSOLVE_DEPENDENT added
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : feelfem90 programming style implementation 
 *             DRAMA double index parallel version
 *
 *  1. Control routine (GenerateCoSolveRoutines)
 *  2. I/O related routines
 *  3. Make calling sequence ExtData routine in solve  [SubDoSolveMakeExtData()]
 * 
 *  5. Generator for the subrouitne mksolve#extdata.f90
 *  6. Generator subroutine EdevRoutine 
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

#include "feeldef.hpp"
#include "PM_feelfem90DRAMA.hpp"
#include "feelfuncs.hpp"            // for int getSpaceDimension();


// 1. Control routine

void PM_feelfem90DRAMA::GenerateCoSolveRoutines(Solve *solvePtr)
{
  GenerateCoSolveEdevRoutine(solvePtr);
  GenerateCoSolveExtDataRoutine(solvePtr);    //mksolve#extdata.f

  return;
}


// 2. I/O related functions

void PM_feelfem90DRAMA::pushEdevRoutineName(int solveNo, int solveElementNo)
{
  char buf[BUFSIZ];
  sprintf(buf,"edev%d_%d",solveNo,solveElementNo);
  pushSource(buf);

  return;
}

// 3. Make calling sequence ExtData routine in solve
void PM_feelfem90DRAMA::SubDoSolveMakeExtData( Solve *solvePtr)  
{
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  COMMENTlong("Make external exptr/external node information");
  pushSource( "call mksolve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("extdata(myrank,nprocs,mypeid,            &");
  flushSource();

  writeSource("                  enptr,con,matno,nelem,                &");
  writeSource("                  ipf,ipd,npmax,                        &");
  writeSource("                  neq,                                  &");
  writeSource("                  isumup,                               &");
  writeSource("                  nelem_ex,enptr_ex,con_ex,matno_ex,    &");
  writeSource("                  nouter,ndno,peno,ipf_ex,ipd_ex,       &");

  pushSource( "                 ");
  pushCoordinateSource();
  pushSource(",");
  pushCoordinateExternalSource();

  // FEM variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",");
      pushFEMVariableInSolve(itr());
    }
  }  
  // FEM External variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",");
      pushFEMVariableExternalInSolve(itr());
    }
  }  
  pushSource(")");
  flushSource();
  
  pushSource("if(myrank.eq.0) call preportmodule('mksolve");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("extdata')");
  flushSource();

  com();

  return;
}




// 5. Generator for the subrouitne mksolve#extdata.f90
void PM_feelfem90DRAMA::GenerateCoSolveExtDataRoutine(Solve *solvePtr)
{
  // make solve#mkexnode.f

  // Because of P2 ONLY version, ONLY ONE ENPTR ASSUMED!!!!!!!!!
  int fem_exchange_variables;
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED
  orderedPtrList <Variable *> varPtrLst = sePtr->GetVariablePtrLst();
  
  fem_exchange_variables = 0;
  listIterator <Variable *> itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) fem_exchange_variables++;
  }

  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;
  
  sprintf(hereRoutineName,"mksolve%dextdata",solvePtr->GetSolveNo());
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_SUBSOLVE_DEPENDENT);

  // MAKESDBUF ROUTINE
  pushSource("module mod_");
  pushSource(hereRoutineName);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushSource(hereRoutineName);
  pushSource("(myrank,nprocs,mypeid,              &");
  flushSource();
  writeSource("                    enptr,con,matno,nelem,             &");
  writeSource("                    ipf,ipd,npmax,                     &");
  writeSource("                    neq,                               &");
  writeSource("                    isumup,                            &");
  writeSource("                    nelem_ex,enptr_ex,con_ex,matno_ex, &");
  writeSource("                    nouter,ndno,peno,ipf_ex,ipd_ex,    &");

  pushSource ("                    ");
  pushCoordinateSource();
  pushSource(",");
  pushCoordinateExternalSource();

  // FEM Variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",");
      pushFEMVariableInCalled(itr());
    }
  }  
  // FEM External Variables 
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource(",");
      pushFEMVariableExternalInCalled(itr());
    }
  }  
  pushSource(")");
  flushSource();

  comment();
  writeSource("! Problem dependent subroutine Make external data");
  writeSource("!");
  writeSource("! Following arrays are allocated in this subroutine");
  writeSource("!");
  writeSource("! isumup                   : sumup degree of freedom ");
  writeSource("! enptr_ex,con_ex,matno_ex : external related element");
  writeSource("! ndno,peno,ipf_ex,ipd_ex  : related outer node index");
  writeSource("! external fem variables   : x_ex,y_ex, fem_ex,...etc.");
  comment();

  writeSource("use numeric");
  writeSource("use abortmodule");
  writeSource("use feelfem90mp      ! message passing with memory allocation");
  writeSource("use subSolveDrama");
  writeSource("use preport90");
  com();
  writeSource("implicit none");
  com();
  writeSource("include 'mpif.h'");
  com();

  writeSource("integer,intent(in)               :: myrank,nprocs,mypeid");
  writeSource("integer,dimension(:,:)           :: enptr,con");
  writeSource("integer,dimension(:)             :: matno");
  writeSource("integer,intent(in)               :: nelem,npmax");
  writeSource("integer,dimension(:)             :: ipf,ipd");
  writeSource("integer,intent(in)               :: neq");
  writeSource("integer,dimension(:),pointer     :: isumup   ! allocate here");
  com();

  writeSource("integer                          :: nelem_ex");
  writeSource("integer,dimension(:,:),pointer   :: enptr_ex,con_ex");
  writeSource("integer,dimension(:),pointer     :: matno_ex");
  writeSource("integer                          :: nouter");
  writeSource("integer,dimension(:),pointer     :: ndno,peno,ipf_ex,ipd_ex");
  com();

  CoordinateVariableDeclaration();
  CoordinateExternalVariableDeclaration();
  
  // fem variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      ArgumentVariableDeclaration(itr());
      FEMExternalVariableDeclaration(itr());
    }
  }
  com();

  writeSource("! auto variables");
  writeSource("!--------------------------------------------");
  writeSource("! Auto variables");
  writeSource("!--------------------------------------------");
  writeSource("integer                          :: i,j,k");
  writeSource("integer                          :: l,lptr");
  writeSource("integer                          :: iptr,ipos,ipos_from,ipos_to");
  writeSource("integer                          :: ierror");
  com();
  writeSource("! used in mksendlst");
  writeSource("integer, dimension(:),pointer    :: nflag,eflag");
  writeSource("integer                          :: ne2send,nconsiz,nn2send");
  com();

  writeSource("integer, parameter               :: n_of_ctrl = 4");
  writeSource("integer, dimension(n_of_ctrl)    :: ctrl_send");
  writeSource("integer, dimension(:)  ,pointer  :: ctrl_all");
  com();

  writeSource("integer                          :: nsend_enptr !  0 or ne2send+1");
  writeSource("integer, dimension(:,:),pointer  :: enptr_send,con_send");
  writeSource("integer, dimension(:,:),pointer  :: enptr_all,con_all");
  writeSource("integer, dimension(:)  ,pointer  :: enptr_counts,enptr_displs");
  writeSource("integer, dimension(:)  ,pointer  :: con_counts,  con_displs");
  com();

  writeSource("integer, dimension(:)  ,pointer  :: matno_send");
  writeSource("integer, dimension(:)  ,pointer  :: matno_all,matno_counts, &");
  writeSource("                                    matno_displs");
  com();

  writeSource("integer, dimension(:)  ,pointer  :: nd_counts,nd_displs");
  writeSource("integer                          :: nd_allcounts");
  writeSource(" ");
  writeSource("integer, dimension(:)  ,pointer  :: nodeno_send,nodeno_all");
  writeSource("integer, dimension(:)  ,pointer  :: peno_all"); 
  writeSource("integer, dimension(:)  ,pointer  :: ipf_send,ipd_send");
  writeSource("integer, dimension(:)  ,pointer  :: ipf_all,ipd_all");
  com();

  writeSource("integer                      :: nconsiz_ex    ! temporary use");
  writeSource("integer                      :: procbuf(nprocs)");
  writeSource("integer                      :: nelem_tmp");
  writeSource("integer                      :: enptr_base,con_base,matno_base");
  com();

  switch(getSpaceDimension()) {
  case 1:
    writeSource("real(kind=REAL8),dimension(:),pointer  :: x_send");    
    writeSource("real(kind=REAL8),dimension(:),pointer  :: x_all");
    break;

  case 2:
    writeSource("real(kind=REAL8),dimension(:),pointer  :: x_send,y_send");    
    writeSource("real(kind=REAL8),dimension(:),pointer  :: x_all,y_all");
    break;

  case 3:
    writeSource("real(kind=REAL8),dimension(:),pointer  :: x_send,y_send,z_send");
    writeSource("real(kind=REAL8),dimension(:),pointer  :: x_all,y_all,z_all");
    break;

  }
  // fem variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("real(kind=REAL8),dimension(:),pointer  :: ");
      pushFEMVariableInCalled(itr());
      pushSource("_send");
      flushSource();

      pushSource("real(kind=REAL8),dimension(:),pointer  :: ");
      pushFEMVariableInCalled(itr());
      pushSource("_all");
      flushSource();

    }
  }

  writeSource("!--------------------------------------------------");
  writeSource("! first, allocate isumup(nprocs+1)");
  writeSource("!--------------------------------------------------");
  writeSource("allocate(isumup(nprocs+1))");
  com();
  writeSource("!--------------------------------------------------");
  writeSource("! Make message passing list");
  writeSource("! This routine is a problem independent routine");
  writeSource("!--------------------------------------------------");
  writeSource("allocate(nflag(npmax),eflag(nelem))");
  com();

  writeSource("call mksendlst(myrank,nprocs,mypeid,enptr,con,nelem,npmax,  &");
  writeSource("               eflag,nflag,ne2send,nconsiz,nn2send          )");
  com();

  writeSource("if(myrank .eq. 0) call preport('MODULE: mksendlst')");
  com();

  COMMENTlong("! old:solve1mksdbuf");
  writeSource("ctrl_send(1) = ne2send");
  writeSource("ctrl_send(2) = nconsiz");
  writeSource("ctrl_send(3) = nn2send");
  writeSource("ctrl_send(4) = neq");
  com();

  writeSource("! Element information to send");
  writeSource("if(ne2send == 0) then");
  com();
  writeSource("  nsend_enptr = 0");
  writeSource("!  nullify(enptr_send,matno_send,con_send)");
  writeSource("  allocate(enptr_send(2,1),con_send(2,1),matno_send(2))");
  com();
  writeSource("else");
  com();

  writeSource("  nsend_enptr = ne2send+1");
  writeSource("  allocate(enptr_send(2,nsend_enptr),con_send(2,nconsiz))");
  writeSource("  allocate(matno_send(ne2send))");
  com();

  writeSource("  iptr = 0");
  writeSource("  ipos = 1");
  com();

  writeSource("  do i=1,nelem");
  writeSource("    if(eflag(i) == Oui) then");
  writeSource("      iptr = iptr + 1");
  writeSource("      enptr_send(1,iptr) = ipos");
  writeSource("      enptr_send(2,iptr) = enptr(2,i)");
  writeSource("      matno_send(  iptr) = matno(i)");
  com();

  writeSource("      ipos_from = enptr(1,i  )");
  writeSource("      ipos_to   = enptr(1,i+1)-1");
  com();

  writeSource("      do j=ipos_from,ipos_to");
  writeSource("        con_send(1,ipos) = con(1,j)");
  writeSource("        con_send(2,ipos) = con(2,j)");
  writeSource("        ipos             = ipos+1");
  writeSource("      end do");
  writeSource("    endif");
  writeSource("  end do");
  com();

  writeSource("  enptr_send(1,iptr+1) = ipos");
  writeSource("  enptr_send(2,iptr+1) = EndOfEnptr");
  com();

  writeSource("  if(iptr+1 .ne. nsend_enptr) then");
  writeSource("    write(*,*) 'iptr+1 .ne. nsend_enptr  myrank=',myrank");
  writeSource("    write(*,*) 'myrank=',myrank,'  ne2send,iptr=',ne2send,iptr");
  writeSource("    call abortexit(myrank)");
  writeSource("  endif");
  com();

  writeSource("endif ");
  com();

  writeSource("!----------------------------");
  writeSource("! node information to send");
  writeSource("!----------------------------");
  writeSource("iptr = 0");
  writeSource("if(nn2send .le. 0) then");
  writeSource("  write(*,*) 'nn2send =0 ERROR'");
  writeSource("  write(*,*) 'myrank=',myrank,'  nn2send=',nn2send");
  writeSource("  call abortexit(myrank)");
  writeSource("endif");
  com();

  writeSource("allocate(nodeno_send(nn2send))");
  writeSource("allocate(ipf_send   (nn2send))");
  writeSource("allocate(ipd_send   (nn2send))");
  com();

  switch(getSpaceDimension()) {
  case 1:
    writeSource("allocate(x_send     (nn2send))");
    break;

  case 2:
    writeSource("allocate(x_send     (nn2send))");
    writeSource("allocate(y_send     (nn2send))");
    break;

  case 3:
    writeSource("allocate(x_send     (nn2send))");
    writeSource("allocate(y_send     (nn2send))");
    writeSource("allocate(z_send     (nn2send))");
    break;
  }

  // fem variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("allocate(");
      pushFEMVariableInCalled(itr());
      pushSource("_send(nn2send))");
      flushSource();
    }
  }
  com();

  writeSource("do i=1,npmax");
  writeSource("  if(nflag(i) .eq. Oui) then");
  writeSource("    iptr = iptr + 1");
  writeSource("    nodeno_send(iptr) = i");
  writeSource("    ipf_send   (iptr) = ipf(i)");
  writeSource("    ipd_send   (iptr) = ipd(i)");

  switch(getSpaceDimension()) {
  case 1:
    writeSource("    x_send     (iptr) = x(i)");
    break;

  case 2:
    writeSource("    x_send     (iptr) = x(i)");
    writeSource("    y_send     (iptr) = y(i)");
    break;

  case 3:
    writeSource("    x_send     (iptr) = x(i)");
    writeSource("    y_send     (iptr) = y(i)");
    writeSource("    z_send     (iptr) = z(i)");
    break;

  }

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("    ");
      pushFEMVariableInCalled(itr());
      pushSource("_send(iptr) = ");
      pushFEMVariableInCalled(itr());
      pushSource("(i)");
      flushSource();
    }
  }
  writeSource("  endif");
  writeSource("end do");
  com();


  writeSource("if(iptr .ne. nn2send) then");
  writeSource("  write(*,*) '[mksolve1exdata]myrank=',myrank,' nn2send != iptr '");
  writeSource("  call abortexit(myrank)");
  writeSource("endif");
  com();

  writeSource("!-----------------------------------------------");
  writeSource("! share");
  writeSource("!-----------------------------------------------");
  writeSource("! ctrl");
  writeSource("call ff90allgather(myrank,nprocs,n_of_ctrl,ctrl_send,ctrl_all)");
  com();

  writeSource("! enptr");
  writeSource("call ff90gathervbcast2(myrank,nprocs,2,nsend_enptr,enptr_send, &");
  writeSource("                       enptr_all,enptr_counts,enptr_displs   )");
  com();

  writeSource("! con");
  writeSource("call ff90gathervbcast2(myrank,nprocs,2,nconsiz,con_send,     &");
  writeSource("                       con_all,con_counts,con_displs         )");
  writeSource("! matro");
  writeSource("call ff90gathervbcast (myrank,nprocs,ne2send,matno_send,     &");
  writeSource("                       matno_all,matno_counts,matno_displs   )");
  com();

  writeSource("!----------------------------------------------------------------");
  writeSource("! nodeno (nd_counts,nd_displs allocate here)");
  writeSource("!----------------------------------------------------------------");
  writeSource("call ff90gathervbcast (myrank,nprocs,nn2send,nodeno_send,    &");
  writeSource("                       nodeno_all,nd_counts,nd_displs        )");
  writeSource("nd_allcounts = 0");
  writeSource("do i=1,nprocs");
  writeSource("  nd_allcounts = nd_allcounts + nd_counts(i)");
  writeSource("end do");
  com();

  writeSource("! make peno_all from nd_counts(i)");
  writeSource("allocate(peno_all(nd_allcounts))");
  writeSource("iptr = 0");
  writeSource("do i=1,nprocs");
  writeSource("  do j=1,nd_counts(i)");
  writeSource("   iptr=iptr+1");
  writeSource("   peno_all(iptr) = i-1      ! RANK NO starts 0");
  writeSource("  end do");
  writeSource("end do");
  com();

  writeSource("! ipf");
  writeSource("allocate(ipf_all(nd_allcounts))");
  writeSource("call MPI_ALLGATHERV(ipf_send,nn2send,            MPI_INTEGER, &");
  writeSource("                    ipf_all ,nd_counts,nd_displs,MPI_INTEGER, &");
  writeSource("                    MPI_COMM_WORLD,ierror                       )");
  com();

  writeSource("! ipd");
  writeSource("allocate(ipd_all(nd_allcounts))");
  writeSource("call MPI_ALLGATHERV(ipd_send,nn2send,            MPI_INTEGER, &");
  writeSource("                    ipd_all ,nd_counts,nd_displs,MPI_INTEGER, &");
  writeSource("                    MPI_COMM_WORLD,ierror                       )");
  com();


  switch(getSpaceDimension()) {
  case 1:
    writeSource("! x");
    writeSource("allocate(x_all(nd_allcounts))");
    writeSource("call MPI_ALLGATHERV(x_send,nn2send,MPI_DOUBLE_PRECISION,&");
    writeSource("      x_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&");
    writeSource("                                   MPI_COMM_WORLD,ierror)");
    com();
    break;

  case 2:
    writeSource("! x");
    writeSource("allocate(x_all(nd_allcounts))");
    writeSource("call MPI_ALLGATHERV(x_send,nn2send,MPI_DOUBLE_PRECISION,&");
    writeSource("      x_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&");
    writeSource("                                   MPI_COMM_WORLD,ierror)");
    com();
    writeSource("! y");
    writeSource("allocate(y_all(nd_allcounts))");
    writeSource("call MPI_ALLGATHERV(y_send,nn2send,MPI_DOUBLE_PRECISION,&");
    writeSource("      y_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&");
    writeSource("                                   MPI_COMM_WORLD,ierror)");
    com();
    break;

  case 3:
    writeSource("! x");
    writeSource("allocate(x_all(nd_allcounts))");
    writeSource("call MPI_ALLGATHERV(x_send,nn2send,MPI_DOUBLE_PRECISION,&");
    writeSource("      x_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&");
    writeSource("                                   MPI_COMM_WORLD,ierror)");
    com();
    writeSource("! y");
    writeSource("allocate(y_all(nd_allcounts))");
    writeSource("call MPI_ALLGATHERV(y_send,nn2send,MPI_DOUBLE_PRECISION,&");
    writeSource("      y_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&");
    writeSource("                                   MPI_COMM_WORLD,ierror)");
    com();

    writeSource("! z");
    writeSource("allocate(z_all(nd_allcounts))");
    writeSource("call MPI_ALLGATHERV(z_send,nn2send,MPI_DOUBLE_PRECISION,&");
    writeSource("      z_all ,nd_counts,nd_displs,  MPI_DOUBLE_PRECISION,&");
    writeSource("                                   MPI_COMM_WORLD,ierror)");
    com();
    break;
  }


  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("! ");
      pushFEMVariableInCalled(itr());
      flushSource();

      pushSource("allocate(");
      pushFEMVariableInCalled(itr());
      pushSource("_all(nd_allcounts))");
      flushSource();

      pushSource("call MPI_ALLGATHERV(");
      pushFEMVariableInCalled(itr());
      pushSource("_send,nn2send,           MPI_DOUBLE_PRECISION,&");
      flushSource();
      
      pushSource("                    ");
      pushFEMVariableInCalled(itr());
      pushSource("_all,nd_counts,nd_displs,MPI_DOUBLE_PRECISION,&");
      flushSource();

      writeSource("                    MPI_COMM_WORLD,ierror     )");

      com();
    }
  }

  writeSource("!------------------------------------------------------");
  writeSource("! sumupdegree");
  writeSource("!------------------------------------------------------");
  writeSource("isumup(1) = 0");
  writeSource("do i=1,nprocs");
  writeSource("  isumup(i+1)=isumup(i)+ctrl_all((i-1)*n_of_ctrl + 4)");
  writeSource("end do");
  com();

  writeSource("!------------------------------------------------------");
  writeSource("! makeielemex");
  writeSource("!------------------------------------------------------");
  com();

  writeSource("! count nelem_ex");
  writeSource("nelem_ex   = 0");
  writeSource("nconsiz_ex = 0");
  com();

  writeSource("do 1 i=1,nprocs");
  writeSource("  procbuf(i) = 0");
  writeSource("  if(mypeid+1 .ne. i) then");
  writeSource("   nelem_tmp=ctrl_all( (i-1)*n_of_ctrl + 1)  ! ne2send of PE(i-1)");
  writeSource("   if(nelem_tmp .gt. 0) then");
  com();
  writeSource("    enptr_base = enptr_displs(i)");
  writeSource("    con_base   = con_displs(i)");
  com();
  writeSource("    do 2 j=1,nelem_tmp");
  writeSource("     ipos_from = enptr_all(1,enptr_base+j  )");
  writeSource("     ipos_to   = enptr_all(1,enptr_base+j+1) - 1");
  com();
  writeSource("     do 3 k=ipos_from,ipos_to");
  writeSource("       if( con_all(2,con_base+k) .eq. mypeid) then");
  writeSource("         procbuf(i) = procbuf(i)+1");
  writeSource("         nconsiz_ex = nconsiz_ex + (ipos_to-ipos_from+1)");
  writeSource("         goto 2");
  writeSource("       endif");
  writeSource("3    continue");
  writeSource("2   continue");
  com();
  writeSource("   end if ! of nelem_tmp .gt. 0");
  writeSource("  end if ! of mypeid+1  .ne. i");
  com();

  writeSource("  nelem_ex = nelem_ex + procbuf(i)");
  com();
  writeSource("1 continue");
  com();

  writeSource("! make enptr_ex,con_ex,matno_ex, ");
  com();
  writeSource("if(nelem_ex .eq. 0) then");
  com();

  writeSource("  iptr = 0");
  writeSource("!  nullify(enptr_ex,con_ex,matno_ex)  ! PGI/ABI");
  writeSource("  allocate(enptr_ex(2,1),con_ex(2,1),matno_ex(2))  ");
  com();

  writeSource("else");
  writeSource("  allocate(enptr_ex(2,nelem_ex+1),con_ex(2,nconsiz_ex))");
  writeSource("  allocate(matno_ex(nelem_ex))");
  writeSource("  enptr_ex(1,1) = 1");
  com();

  writeSource("  iptr = 0");
  writeSource("  do i=1,nprocs");
  com();
  writeSource("   if(procbuf(i) .ne. 0 .and. mypeid+1 .ne. i) then");
  writeSource("    nelem_tmp = ctrl_all((i-1)*n_of_ctrl+1) ! ne2send of PE(i-1)");
  writeSource("    enptr_base = enptr_displs(i)");
  writeSource("    con_base   = con_displs(i)");
  writeSource("    matno_base = matno_displs(i)");
  com();

  writeSource("    do 11 j=1,nelem_tmp");
  writeSource("     ipos_from = enptr_all(1,enptr_base+j  )");
  writeSource("     ipos_to   = enptr_all(1,enptr_base+j+1) -1");
  com();
  writeSource("     do k=ipos_from,ipos_to");
  writeSource("      if(con_all(2,con_base+k) .eq. mypeid) then");
  writeSource("       iptr = iptr + 1");
  writeSource("       enptr_ex(2,iptr  )=enptr_all(2,enptr_base+j)");
  writeSource("       enptr_ex(1,iptr+1)=enptr_ex(1,iptr)+(ipos_to-ipos_from+1)");
  writeSource("       matno_ex(iptr    ) = matno_all(matno_base+j)");
  com();

  writeSource("       do l=ipos_from,ipos_to");
  writeSource("        lptr = l-ipos_from       ! lptr = 0,1,2,3,....");
  writeSource("        con_ex(1,enptr_ex(1,iptr)+lptr)=con_all(1,con_base+l)");
  writeSource("        con_ex(2,enptr_ex(1,iptr)+lptr)=con_all(2,con_base+l)");
  writeSource("       end do");
  com();
  writeSource("       goto 11");
  writeSource("       end if");
  com();

  writeSource("      end do        ! do k=ipos_from,ipos_to");
  com();

  writeSource("11  continue   ! do j=1,nelem_tmp");
  com();
  writeSource("  end if   ! if(procbuf(i) .ne. 0 .and. mypeid+1 .ne. i)");
  writeSource("  end do   ! do i=1,nprocs");
  com();
  writeSource("end if  ! if(nelem_ex .eq. 0) then ..... ");
  com();

  writeSource("!-------------- end of making enptr_ex,con_ex,matno_ex");
  com();

  writeSource("!-----------------------------");
  writeSource("! mkexnode");
  writeSource("!-----------------------------");
  com();
  writeSource("! count nouter with DUPLICATION");
  com();
  writeSource("nouter = 0");
  com();
  writeSource("do i=1,nelem              ! search other PE's node in my elements");
  writeSource(" ipos_from = enptr(1,i  )");
  writeSource(" ipos_to   = enptr(1,i+1)-1");
  writeSource(" do j=ipos_from,ipos_to");
  writeSource("  if(con(2,j) .ne. mypeid) nouter = nouter + 1");
  writeSource(" end do");
  writeSource("end do");
  com();

  writeSource("do i=1,nelem_ex                ! search other N in other E");
  writeSource(" ipos_from = enptr_ex(1,i  )");
  writeSource(" ipos_to   = enptr_ex(1,i+1)-1");
  writeSource(" do j=ipos_from,ipos_to");
  writeSource("   if(con_ex(2,j) .ne. mypeid) nouter = nouter + 1");
  writeSource(" end do");
  writeSource("end do");
  com();

  writeSource("! allocate  ndno,peno, and x,y, fem variables(PROBLEM DEPENDENT)");

  writeSource("if(nouter .eq. 0) then");
  com();
  writeSource("  nullify(ndno,peno,ipf_ex,ipd_ex)");
  writeSource("  nullify(x_ex,y_ex)");

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("  nullify(");
      pushFEMVariableInCalled(itr());
      pushSource("_ex)");
      flushSource();
    }
  }

  com();

  writeSource("else");
  com();

  writeSource("  allocate(ndno(nouter),peno(nouter))");
  writeSource("!");
  writeSource("! fix duplication");
  writeSource("!");
  writeSource("  iptr = 0");
  com();
  writeSource("  do i=1,nelem          ! make outer node list with my elements");
  writeSource("   ipos_from = enptr(1,i  )");
  writeSource("   ipos_to   = enptr(1,i+1)-1");
  writeSource("   do 21 j=ipos_from,ipos_to");
  writeSource("    if(con(2,j) .ne. mypeid) then");
  writeSource("      do k=1,iptr");
  writeSource("       if(ndno(k)==con(1,j) .and. peno(k)== con(2,j)) goto 21");
  writeSource("      end do");
  writeSource("      iptr = iptr + 1");
  writeSource("      ndno(iptr) = con(1,j)");
  writeSource("      peno(iptr) = con(2,j)");
  writeSource("    end if");
  writeSource("21 continue ");
  writeSource("  end do");
  com();
  writeSource("  do i=1,nelem_ex                  ! make outer node list");
  writeSource("   ipos_from = enptr_ex(1,i  )");
  writeSource("   ipos_to   = enptr_ex(1,i+1)-1");
  writeSource("   do 22 j=ipos_from,ipos_to");
  writeSource("    if(con_ex(2,j) .ne. mypeid) then");
  writeSource("     do k=1,iptr");
  writeSource("      if(ndno(k)==con_ex(1,j) .and. peno(k)==con_ex(2,j)) goto 22");
  writeSource("     end do");
  writeSource("     iptr = iptr + 1");
  writeSource("     ndno(iptr) = con_ex(1,j)");
  writeSource("     peno(iptr) = con_ex(2,j)");
  writeSource("    end if  ");
  writeSource("22 continue");
  writeSource("  end do");
  com();

  writeSource("! reallocation peno/ndno");
  writeSource("  allocate( ipf_ex(iptr), ipd_ex(iptr))");
  writeSource("  do i=1,iptr");
  writeSource("    ipf_ex(i) = ndno(i)");
  writeSource("    ipd_ex(i) = peno(i)");
  writeSource("  end do");
  com();

  writeSource("!-------------");
  writeSource("! real nouter ");
  writeSource("!-------------");
  writeSource("  nouter = iptr");
  com();

  writeSource("  deallocate( ndno,peno )");
  writeSource("  allocate  ( ndno(nouter),peno(nouter))");
  com();

  writeSource("  do i=1,nouter");
  writeSource("    ndno(i)=ipf_ex(i)");
  writeSource("    peno(i)=ipd_ex(i)");
  writeSource("  end do");
  writeSource("  deallocate( ipf_ex,ipd_ex )");
  com();

  writeSource("! make ipf_ex,ipd_ex, and external fem variables");
  com();


  writeSource("  allocate(ipf_ex(nouter),ipd_ex(nouter))    ! ipf, ipd");

  switch(getSpaceDimension()) {
  case 1:
    writeSource("  allocate(x_ex(nouter))                     ! coordinates");
    break;
  case 2:
    writeSource("  allocate(x_ex(nouter),y_ex(nouter))        ! coordinates");
    break;
  case 3:
    writeSource("  allocate(x_ex(nouter),y_ex(nouter),z_ex(nouter)) ! coord");
    break;
  }

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("  allocate(");
      pushFEMVariableInCalled(itr());
      pushSource("_ex(nouter))");
      flushSource();
    }
  }
  com();

  writeSource("  do 31 i=1,nouter");
  writeSource("    do j=1,nd_allcounts");
  writeSource("      if(ndno(i)==nodeno_all(j) .and. peno(i)==peno_all(j)) then");
  writeSource("        ipf_ex(i)    = ipf_all(j)");
  writeSource("        ipd_ex(i)    = ipd_all(j)");

  switch(getSpaceDimension()) {
  case 1:
    writeSource("        x_ex(i)      = x_all(j)");
    break;
  case 2:
    writeSource("        x_ex(i)      = x_all(j)");
    writeSource("        y_ex(i)      = y_all(j)");
    break;
  case 3:
    writeSource("        x_ex(i)      = x_all(j)");
    writeSource("        y_ex(i)      = y_all(j)");
    writeSource("        z_ex(i)      = z_all(j)");
    break;
  }

  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("        ");
      pushFEMVariableInCalled(itr());
      pushSource("_ex(i) = ");
      pushFEMVariableInCalled(itr());
      pushSource("_all(j)");
      flushSource();
    }
  }
  writeSource("        goto 31");
  writeSource("      endif");
  writeSource("    end do");
  writeSource("    write(*,*) 'ERROR: Not found outer node'");
  writeSource("    write(*,*) 'pe,no=',peno(i),ndno(i),' i=',i");
  writeSource("    call abortexit(myrank)");
  writeSource("31 continue");
  com();

  writeSource("endif              !if(nouter.eq.0)");
  com();

  writeSource("!----------------------------------");
  writeSource("! Deallocation");
  writeSource("!---------------------------------");
  writeSource("deallocate(nflag,eflag)");
  writeSource("if(associated(enptr_send)) then");
  writeSource("  deallocate(enptr_send,con_send,matno_send)");
  writeSource("endif");
  writeSource("deallocate(nodeno_send)");
  writeSource("deallocate(ipf_send,ipd_send)");

  switch(getSpaceDimension()) {
  case 1:
    writeSource("deallocate(x_send)");
    writeSource("deallocate(x_all )");
    break;
  case 2:
    writeSource("deallocate(x_send,y_send)");
    writeSource("deallocate(x_all ,y_all )");
    break;
  case 3:
    writeSource("deallocate(x_send,y_send,z_send)");
    writeSource("deallocate(x_all ,y_all ,z_all )");
    break;
  }
  writeSource("deallocate(peno_all,ipf_all,ipd_all)");

  // Deallocation block for FEM variables
  for(itr.init(); !itr;++itr) {
    if(itr()->GetType() == VAR_FEM) {
      pushSource("deallocate(");
      pushFEMVariableInCalled(itr());
      pushSource("_send,");
      pushFEMVariableInCalled(itr());
      pushSource("_all)");
      flushSource();
    }
  }
  
  com();
  pushSource("end subroutine ");
  pushSource(hereRoutineName);
  flushSource();

  pushSource("end module mod_");
  pushSource(hereRoutineName);
  flushSource();

  CloseSource();
  return;

}



// 6. Generator subroutine EdevRoutine
void PM_feelfem90DRAMA::GenerateCoSolveEdevRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1
  
  sprintf(hereRoutineName,"edev%d_%d",solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);
  OpenSource(hereSourceName,LINKLEVEL_EDEV);

  pushSource("module mod_");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  pushSource("(mypeid,resvec,ipd,enptr,con,nelem");

  pushVariableListInCalled( sePtr->GetUnknownVariablePtrLst());
  pushSource(")");

  flushSource();
  
  SourceStarters();
  writeSource("use numeric");
  fortImplicit();
  com();

  writeSource("integer,intent(in)              :: mypeid");
  writeSource("real(kind=REAL8),dimension(:)   :: resvec");
  writeSource("integer,dimension(:)            :: ipd");
  writeSource("integer,dimension(:,:)          :: enptr,con");
  writeSource("integer,intent(in)              :: nelem");
  com();

  list <Variable *>varPtrLst = sePtr->GetUnknownVariablePtrLst();
  ArgumentVariableDeclarationLst(varPtrLst);
  com();

  writeSource("! auto variables");
  writeSource("integer                         :: i,j");
  writeSource("integer                         :: ipos_from,ipos_to");
  writeSource("integer                         :: nodes");
  writeSource("integer                         :: nnd,npe");

  // ienp_** and iedp_**
  listIterator <Variable *>itr(varPtrLst);
  for(itr.init(); !itr;++itr) {
    pushSource("integer,dimension(");
    pushSourceInt(itr()->testGetElementFreedom());
    pushSource(")            :: ienp_");
    pushSource(itr()->GetName());
    pushSource(",iedp_");
    pushSource(itr()->GetName());
    flushSource();
  }
  com();


  // data sentences

  writeSource("! data statements");

  int ienp_ptr,iedp_ptr;
  ienp_ptr = 0;
  iedp_ptr = 0;
  for(itr.init(); !itr;++itr) {
    
    pushSource("data ienp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->testGetElementFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIENP(ienp_ptr));
      ienp_ptr++;
    }
    pushSource("/");
    flushSource();

    pushSource("data iedp_");
    pushSource(itr()->GetName());
    pushSource("/ ");
    for(int k=0;k<itr()->testGetElementFreedom();k++) {
      if(k != 0) { pushSource(","); }
      pushSourceInt(sePtr->GetIthIEDP(iedp_ptr));
      iedp_ptr++;
    }
    pushSource("/");
    flushSource();
  }
  comment();



  com();
  
  writeSource("do i=1,nelem");
  writeSource("  ipos_from = enptr(1,i  )");
  writeSource("  ipos_to   = enptr(1,i+1)-1");
  writeSource("  nodes     = ipos_to-ipos_from+1");

  int ivars;
  ivars = 0;
  
  for(itr.init(); !itr;++itr) {
    com();
    pushSource(" do j=1,");
    pushSourceInt( itr()->testGetElementFreedom());
    flushSource();
    
    pushSource("  nnd = con(1,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    pushSource("  npe = con(2,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    writeSource("  if(npe .eq. mypeid) then");
    pushFEMVariableInCalled(itr());
    pushSource("(nnd) = resvec(ipd(nnd) + iedp_");
    pushSource(itr()->GetName());
    pushSource("(j))");
    flushSource();
    
    writeSource("  end if");
    writeSource(" end do");

    ivars++;
  }
  com();

  writeSource("end do");
  com();

  
  pushSource("end subroutine ");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  
  pushSource("end module mod_");
  pushEdevRoutineName( solvePtr->GetSolveNo(), solveElementNo);
  flushSource();
  
  
  CloseSource();
  return;

}





