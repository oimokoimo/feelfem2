/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90PAMG81.cpp
 *  Date     : 2000/12/07
 *  Modified : 
 *  
 *  Purpose  : Baserman's distributed CRS matrix library solver
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

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90PAMGCRS.hpp"
#include "LIB_feelfem90PAMG81.hpp"


//Default constructor 
template <> LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::LIB_feelfem90PAMG81()
{
  return;   // do nothing
}


//Default Destructor
template <> LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::~LIB_feelfem90PAMG81() = default;

template <> void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  COMMENTlong("Allocate solution vector");
  writeSource("allocate( resvec(neq + nhalo))");
  writeSource("call zerod(resvec,neq+nhalo)");
  com();

  COMMENTlong("PAMG parameters");
  writeSource("matrix    =  12     !(matrix type  1: symmetric  2: not symmetric)");
  com();

  writeSource("iswtch    =  4      !(setup->first->solve->wrkcnt, each entry is 4,3,2,1)");
  writeSource("                    !( in this case 4 ?)");
  com();

  writeSource("iout      =  14     !( 0:no output,1: residual 2:statistics cp-times,etc.");
  writeSource("                    !  3:residual at each amg-cycle   4: alles           )");
  com();

  writeSource("iprint    = 10606   ! 1st digit: not used; has to be non-zero");
  writeSource("                    ! 2nd and 3rd digit  --  iup: unit number for results");
  writeSource("                    ! 4th and 5th digit  --  ium: unit number for messages  ");
  com();

  writeSource("levelx    = 25      ! maximum number of mg-levels to be created");
  com();

  writeSource("ifirst    = 13      ! parameter for first approximation");
  writeSource("                    ! 1st digit of ifirst: not used; has to be non-zero. ");
  writeSource("                    ! 2nd digit of ifirst  --  itypu:");
  writeSource("                    ! =0: no setting of first approximation,");
  writeSource("                    ! =1: first approximation constant to zero,");
  writeSource("                    ! =2: first approximation constant to one,");
  writeSource("                    ! =3: first approximation is random function with");
  writeSource("                    !     the concrete random sequence being determined");
  writeSource("                    !     by the follwing digits.         ");
  com();

  writeSource("ncyc      = 125100  ! integer parameter describing the type of cycle to be");
  writeSource("                    ! used and the number of cycles to be performed.");
  writeSource("                    ! 1st digit of ncyc  --  igam:");
  writeSource("                    ! =1: v -cycle,");
  writeSource("                    ! =2: v*-cycle,");
  writeSource("                    ! =3: f -cycle,");
  writeSource("                    ! =4: w -cycle.");
  writeSource("                    ! if ncyc is negativ, then the approximation of the");
  writeSource("                    ! problem on the second finest grid is computed by");
  writeSource("                    ! igam v-cycles on that particular grid.");
  writeSource("                    !");
  writeSource("                    ! 2nd digit of ncyc  --  icgr:");
  writeSource("                    ! =0: no conjugate gradient,");
  writeSource("                    ! =1: conjugate gradient (only first step of cg),");
  writeSource("                    ! =2: conjugate gradient (full cg).");
  writeSource("                    !");
  writeSource("                    ! 3rd digit of ncyc  --  iconv:");
  writeSource("                    ! convergence criterion for the user-defined problem");
  writeSource("                    ! (finest grid):");
  writeSource("                    ! =1: perform a fixed number of cycles as given by");
  writeSource("                    !    ncycle (see below)");
  writeSource("                    ! =2: stop, if  ||res|| < eps");
  writeSource("                    ! =3: stop, if  ||res|| < eps * |f|");
  writeSource("                    ! =4: stop, if  ||res|| < eps * |u| * |diag|");
  writeSource("                    ! with ||res|| = l2-norm of residual,");
  writeSource("                    !      eps     (see input parameter eps)");
  writeSource("                    !      |f|   = supremum norm of right hand side");
  writeSource("                    !      |u|   = supremum norm of solution");
  writeSource("                    !     |diag|  = maximal diagonal entry in matrix l");
  writeSource("                    ! note that in any case the solution process stops");
  writeSource("                    ! after at most ncycle cycles.       ");
  com();

  writeSource("epsamg    = 1.0d-9  ! convergence criterion for solution process: (see");
  writeSource("                    ! parameter ncyc). note that no more than ncycle cycles");
  writeSource("                    ! are performed, regardless of eps.     ");
  com();

  writeSource("madapt    = 1       ! integer value specifying the choice of coarsest");
  writeSource("                    ! grid in cycling:");
  writeSource("                    ! 1st digit of madapt  --  msel:");
  writeSource("                    ! =1: in cycling, all grids constructed in the setup");
  writeSource("                    !     phase are used without check.");
  writeSource("                    ! =2: the number of grids is automatically reduced");
  writeSource("                    !     if the convergence factor on the coarser grids");
  writeSource("                    !     is found to be larger than a given value fac");
  writeSource("                    !     (see below).");
  writeSource("                    !");
  writeSource("                    ! rest of madapt  --  fac");
  writeSource("                    !    the rest of madapt defines the fractional part");
  writeSource("                    !    of a real number fac between 0.1 and 0.99, e.g.");
  writeSource("                    !    madapt=258 means msel=2 and fac=0.58. if madapt");
  writeSource("                    !    consists of only one digit, fac is set to 0.7");
  writeSource("                    !    by default.  ");
  com();

  writeSource("nrd       =  1231   !  parameter describing relaxation (downwards):");
  writeSource("                    ! 1st digit of nrd: not used; has to be non-zero.");
  writeSource("                    ! 2nd digit of nrd  --  nrdx:");
  writeSource("                    !     actual number of smoothing steps to be performed");
  writeSource("                    !     the type of which is given by the following digits");
  writeSource("                    ! following digits  --  array nrdtyp:");
  writeSource("                    ! =1: relaxation over the f-points only");
  writeSource("                    ! =2: full gs sweep");
  writeSource("                    ! =3: relaxation over the c-points only");
  writeSource("                    ! =4: full more color sweep, highest color first      ");
  com();

  writeSource("nsolco    =   2     ! parameter controlling the solution on coarsest grid:");
  writeSource("                    ! 1st digit  --  nsc:");
  writeSource("                    !  =1: gauss-seidel method");
  writeSource("                    !  =2: direct solver (YALE,ESSL or ESSL substitute)");
  writeSource("                    !      plug in IESSL or IYALE in the subroutine");
  writeSource("                    !      amg_strin_inp to choose the YALE sparse matrix");
  writeSource("                    !      direct solver or plug in IESSL for the ESSL");
  writeSource("                    !      direct solver for full");
  writeSource("                    !      nonsymmetric rectangular matrices. In case");
  writeSource("                    !      the ESSL solver is not installed on your machine");
  writeSource("                    !      you still may use the parameter IESSL if the");
  writeSource("                    !      substitutes for ESSL in amgesslsub.F has been");
  writeSource("                    !      installed by avoiding the pre-compiler directive");
  writeSource("                    !      -DESSL");
  writeSource("                    !      (Usually its a better to choose IESSL");
  writeSource("                    !       as the coarse grid matrices tend to be full)");
  writeSource("                    !");
  writeSource("                    ! rest of nsolco  --  nrcx: (only if nsc=1)");
  writeSource("                    ! number of gs sweeps on coarsest grid (>=0).");
  writeSource("                    ! if nrcx=0, then as many gs sweeps are performed");
  writeSource("                    ! as are needed to reduce the residual by two orders");
  writeSource("                    ! of magnitude. (maximal 100 relaxation sweeps)");
  com();

  writeSource("nru       =   1231  ! parameter for relaxation (upwards), analogous to nrd.");
  com();

  writeSource("! class 4 parameters ");
  writeSource("ecg1      =  0.     ! real parameters affecting the creation of coarser");
  writeSource("ecg2      =  0.25   ! real parameters affecting the creation of coarser");
  com();

  writeSource("ewt2      =  0.35   ! grids and/or the definition of the interpolation.");
  writeSource("                    ! the choice of these parameters depends on");
  writeSource("                    ! the actual amg version (see subroutine crsng) ");
  com();

  writeSource("nwt       =  14     ! integer parameter affecting the creation of coarser");
  writeSource("                    ! grids and/or the definition of the interpolation.");
  writeSource("                    ! the choice of this parameter depends on");
  writeSource("                    ! the actual amg version (see subroutine crsng)");
  com();

  writeSource("ntr       =  0      ! parameter controlling coarse-grid operator truncation");
  writeSource("                    ! =0: pairs of zeroes are removed from coarse grid");
  writeSource("                    !     operators");
  writeSource("                    ! =1: no coarse-grid operator truncation");
  writeSource("                    ! (there should be enough memory location contained in a");
  writeSource("                    !  ja if zeros need to be inserted !)    ");
  com();

  writeSource("ncoarsen  = 0");
  writeSource("icopy     = 0");
  writeSource("iflag     = 1");
  writeSource("!time");
  writeSource("!iunit_amg =14");
  com();

  // version 8.1 additionals
  int solveElements = 1;                // P2 FIX
  COMMENTlong("Version 8.1 additional parameters");
  pushSource( "call ");
  pushSource("pamg81param");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElements);
  pushSource("(mypeid,nprocs,isumup,      &");
  flushSource();
  writeSource("      enptr,con,nelem,                         &");
  writeSource("      ipf,ipd,npmax,                           &");
  writeSource("      enptr_ex,con_ex,nelem_ex,                &");
  writeSource("      ndno,peno,ipf_ex,ipd_ex,nouter,          &");
  writeSource("      neq,ipd_halo,nhalo,                      &");
  writeSource("      iuamg,ipamg,nsys,npts,iscale             ) ! set here");
  com();
                               



  writeSource("call amg2r5wf90(valmat,iptrcol,indrow,resvec,vfg,ncof,neq,nhalo, &");
  writeSource("                iuamg,ipamg,nsys,npts,iscale,                    &");
  writeSource("                penv,pupdate,glinfo,                             &");
  writeSource("                matrix,iswtch,iout,iprint,                       &");
  writeSource("                levelx,ifirst,ncyc,epsamg,madapt,nrd,nsolco,nru, &");
  writeSource("                ecg1,ecg2,ewt2,nwt,ntr,ncoarsen,                 &");
  writeSource("                icopy,iflag,time,iunit_amg,ierror                )");
  com();
  
  pushSource("      if(myrank.eq.0) call preportmodule('PAMG solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();
  comment();

  com();

  return;
}

template <> void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::F90useSolveLIB(void)
{
  writeSource("! AMG solver related modules");
  writeSource("use mod_amg_penv");
  writeSource("use mod_amg_update");
  writeSource("use mod_amg_initialize");
  writeSource("use mod_amg_amg2r5wf90");
  com();
  
  return;
}


template <> void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::SolverLibraryParameters(void)");
  return;
}

template <> void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables");
  writeSource("real(kind=REAL8),dimension(:),pointer :: resvec");

  writeSource("integer                        :: matrix");
  writeSource("integer                        :: iswtch");
  writeSource("integer                        :: iout");
  writeSource("integer                        :: iprint");
  writeSource("integer                        :: levelx");
  writeSource("integer                        :: ifirst");
  writeSource("integer                        :: ncyc");
  writeSource("real(kind=REAL8 )              :: epsamg");
  writeSource("integer                        :: madapt");
  writeSource("integer                        :: nrd");
  writeSource("integer                        :: nsolco");
  writeSource("integer                        :: nru");
  writeSource("real(kind=REAL8 )              :: ecg1,ecg2 ");
  writeSource("real(kind=REAL8 )              :: ewt2 ");
  writeSource("integer                        :: nwt");
  writeSource("integer                        :: ntr");
  writeSource("integer                        :: ncoarsen");
  writeSource("integer                        :: icopy");
  writeSource("integer                        :: iflag");
  writeSource("real                           :: time(maxgrid)");
  com();

  // Version 8.1  81 additional parameters
  writeSource("integer,dimension(:),pointer   :: iuamg,ipamg,iscale");
  writeSource("integer                        :: nsys,npts");

  com();

  return;
}

//
template <> void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  int solveElementNo = 1 ;   // P2 limitation FIX

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();
  // library dependent co-solve routine module
  pushSource("use mod_pamg81param");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  flushSource();

  F90useSolveMT();
  F90useSolvePM(solvePtr);
  
  
  fortImplicit();
  com();

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent
  

  return;
}

template <> void LIB_feelfem90PAMG81<MT_ff90PAMGCRS>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  const char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1

  int ivars;                // number of unknowns
  
  sprintf(hereRoutineName,"pamg81param%d_%d",
	  solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);

  OpenSource(hereSourceName,LINKLEVEL_LIBRARY_DEPENDENT);

  pushSource("module mod_pamg81param");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine pamg81param");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  pushSource("(mypeid,nprocs,isumup,      &");
  flushSource();

  writeSource("      enptr,con,nelem,                         &");
  writeSource("      ipf,ipd,npmax,                           &");
  writeSource("      enptr_ex,con_ex,nelem_ex,                &");
  writeSource("      ndno,peno,ipf_ex,ipd_ex,nouter,          &");
  writeSource("      neq,ipd_halo,nhalo,                      &");
  writeSource("      iuamg,ipamg,nsys,npts,iscale             )");
  com();
  
  SourceStarters();
  writeSource("use numeric");
  writeSource("use subSolveDrama");  // for ndsearch_ex
  fortImplicit();
  com();

  writeSource("integer,intent(in)              :: mypeid,nprocs");
  writeSource("integer,dimension(:)            :: isumup");
  com();
  writeSource("integer,dimension(:,:)          :: enptr,con");
  writeSource("integer,intent(in)              :: nelem");
  com();

  writeSource("integer,dimension(:)            :: ipf,ipd");
  writeSource("integer,intent(in)              :: npmax");
  com();

  writeSource("integer,dimension(:,:)          :: enptr_ex,con_ex");
  writeSource("integer,intent(in)              :: nelem_ex");
  com();
  
  writeSource("integer,dimension(:)            :: ndno,peno,ipf_ex,ipd_ex");
  writeSource("integer,intent(in)              :: nouter");
  com();

  writeSource("integer,intent(in)              :: neq,nhalo");
  writeSource("integer,dimension(:)            :: ipd_halo");
  com();
  
  writeSource("integer,dimension(:),pointer    :: iuamg,ipamg,iscale");
  writeSource("integer                         :: nsys,npts");  


  writeSource("! auto variables");
  writeSource("integer                         :: i,j");
  writeSource("integer                         :: ipos_from,ipos_to");
  writeSource("integer                         :: nodes");
  writeSource("integer                         :: ind,ipe");
  writeSource("integer                         :: nd");
  com();

  // ienp_** and iedp_**

  
  list <Variable *> varPtrLst = sePtr -> GetUnknownVariablePtrLst();
  listIterator <Variable *>itr(varPtrLst);

  ivars = 0;
  for(itr.init(); !itr;++itr) {
    ivars++;
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


  pushSource( "nsys = ");
  pushSourceInt(ivars);
  pushSource("            ! number of physical unknown types");
  flushSource();
  writeSource("allocate(iscale(nsys))");
  com();
  writeSource("do i=1,nsys");
  writeSource(" iscale(i) = 0");
  writeSource("end do");
  com();
  
  writeSource("if(nsys == 1) then");
  com();

  writeSource("  npts = 0    ! do not allocat iuamg,ipamg");
  writeSource("  nullify(iuamg)");
  writeSource("  nullify(ipamg)");
  writeSource("  return");
  com();
  writeSource("endif");
  com();

  writeSource("allocate(iuamg(neq+nhalo))");
  writeSource("allocate(ipamg(neq+nhalo))");
  com();

  writeSource("! future extension");
  writeSource("do i=1,neq+nhalo");
  writeSource(" ipamg(i)=0");
  writeSource("end do");
  com();
  
  // for own element loop
  writeSource("do i=1,nelem");
  writeSource("  ipos_from = enptr(1,i  )");
  writeSource("  ipos_to   = enptr(1,i+1)-1");
  writeSource("  nodes     = ipos_to-ipos_from+1");

  ivars = 0;
  
  for(itr.init(); !itr;++itr) {

    ivars++;

    com();
    pushSource(" do j=1,");
    pushSourceInt( itr()->testGetElementFreedom());
    flushSource();
    
    pushSource("  ind = con(1,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    pushSource("  ipe = con(2,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    writeSource("  if(ipe .eq. mypeid) then");

    // for own node
    pushSource("   iuamg(ipd(ind)+iedp_");
    pushSource(itr()->GetName());
    pushSource("(j)) = ");
    pushSourceInt(ivars);
    flushSource();

    com();
    writeSource("  else");
    com();
    
    writeSource("   nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)");
    
    pushSource( "   iuamg(ipd_halo(nd)+iedp_");
    pushSource(itr()->GetName());
    pushSource("(j) + neq) = ");    
    pushSourceInt(ivars);
    flushSource();
    
    writeSource("  end if");
    writeSource(" end do");

  }
  com();

  writeSource("end do");
  com();


  // for outer element loop
  writeSource("do i=1,nelem_ex");
  writeSource("  ipos_from = enptr_ex(1,i  )");
  writeSource("  ipos_to   = enptr_ex(1,i+1)-1");
  writeSource("  nodes     = ipos_to-ipos_from+1");

  ivars = 0;
  
  for(itr.init(); !itr;++itr) {

    ivars++;

    com();
    pushSource(" do j=1,");
    pushSourceInt( itr()->testGetElementFreedom());
    flushSource();
    
    pushSource("  ind = con_ex(1,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    pushSource("  ipe = con_ex(2,ipos_from+ienp_");
    pushSource(itr()->GetName());
    pushSource("(j)-1)");
    flushSource();

    writeSource("  if(ipe .eq. mypeid) then");

    // for own node
    pushSource("   iuamg(ipd(ind)+iedp_");
    pushSource(itr()->GetName());
    pushSource("(j)) = ");
    pushSourceInt(ivars);
    flushSource();

    com();
    writeSource("  else");
    com();
    
    writeSource("   nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)");
    
    pushSource( "   iuamg(ipd_halo(nd)+iedp_");
    pushSource(itr()->GetName());
    pushSource("(j) + neq) = ");    
    pushSourceInt(ivars);
    flushSource();
    
    writeSource("  end if");
    writeSource(" end do");

  }
  com();

  writeSource("end do");
  com();

  
  pushSource("end subroutine pamg81param");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  
  flushSource();
  
  pushSource("end module mod_");
  pushSource("pamg81param");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  flushSource();
  
  
  CloseSource();
  return;

}


//Library dependent solve-co routine generator
template <> void LIB_feelfem90PAMG81 <MT_ff90PAMGCRS>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);
  return;
}
