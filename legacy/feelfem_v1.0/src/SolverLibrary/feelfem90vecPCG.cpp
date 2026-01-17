/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90vecPCG.cpp
 *  Date     : 2001/11/29 (copy from feelfem90SAMG20c.cpp)
 *  Modified : 
 *  
 *  Purpose  : Washio's vector solver
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90vecCRS.hpp"
#include "LIB_feelfem90vecPCG.hpp"


//Default constructor 
LIB_feelfem90vecPCG <MT_ff90vecCRS>::LIB_feelfem90vecPCG()
{
  return;   // do nothing
}


//Default Destructor
LIB_feelfem90vecPCG <MT_ff90vecCRS>::~LIB_feelfem90vecPCG()
{
  return;  // do nothing;
}

void LIB_feelfem90vecPCG <MT_ff90vecCRS>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  COMMENTlong("Allocate solution vector");
  writeSource("allocate( resvec(neq ))");
  writeSource("call zerod(resvec,neq)");
  com();

  // version 8.1 additionals
  int solveElements = 1;                // P2 FIX
  COMMENTlong("Version SAMG20c parameters");
  com();
  pushSource( "call ");
  pushSource("samg20cparam");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElements);
  pushSource("(ielem,nelem,np,  &   ! nsys set,iscale allocated");
  flushSource();
  writeSource("      ipf,ipd,npmax,neq,              &   ! iuamg,ipamg allocated here");
  writeSource("      iuamg,ipamg,nsys,npts,iscale    )   ! (if necessary)");
  com();

  writeSource("if (npts > 0) then");
  writeSource("   ndip = neq           ! Future extension(Feb-05,2001)");
  writeSource("   ndiu = neq");
  writeSource("else");
  writeSource("   ndip = 1             ! Future extension(Feb-05,2001)");
  writeSource("   ndiu = 1");
  writeSource("endif");
  com();
                               
   
  writeSource("matrix    = 12          !(matrix type  1: symmetric  2: not symmetric)");

  writeSource("res_in    = 0.0");
  writeSource("res_out   = 0.0");
  writeSource("ncyc_done = 0  ");
  writeSource("ierr      = 0  ");
  writeSource("nsolve    = 20000       ! different from PAMG81"); 
  writeSource("ifirst    = 10 ");
  writeSource("epsamg    = 1.0d-9      ! convergence criterion for solution process");
  writeSource("ncyc      = 110500      ! different from PAMG81"); 
  writeSource("iswtch    = 5110031     ! different from PAMG81");
  writeSource("a_cmplx   = 3.0         !");
  writeSource("g_cmplx   = 3.0         !");
  writeSource("p_cmplx   = 3.0         !");
  writeSource("w_avrge   = 3.0         !");
  writeSource("chktol    = 0.0         !");
  writeSource("idump     = 1222        !");
  writeSource("iout      = 30          !");       
  com();

  writeSource("call samg(neq,ncof,nsys,iptrcol,indrow,valmat, &");
  writeSource("          vfg,resvec,iuamg,ndiu,ipamg,ndip,    &");
  writeSource("          matrix,iscale,                       &");
  writeSource("          res_in,res_out,ncyc_done,ierr,       &");
  writeSource("          nsolve,ifirst,epsamg,ncyc,iswtch,    &");
  writeSource("          a_cmplx,g_cmplx,p_cmplx,w_avrge,     &");
  writeSource("          chktol,idump,iout                    )");
  com();
  
  pushSource("call reportmodule('SAMG20c solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();
  comment();

  com();

  return;
}

void LIB_feelfem90vecPCG <MT_ff90vecCRS>::F90useSolveLIB(void)
{
  writeSource("! SAMG20c solver related modules");
  writeSource("! inclue 'amg_samg'  ! interface definition");
  com();
  
  return;
}


void LIB_feelfem90vecPCG <MT_ff90vecCRS>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_feelfem90vecPCG <MT_ff90vecCRS>::SolverLibraryParameters(void)");
  return;
}

void LIB_feelfem90vecPCG <MT_ff90vecCRS>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables(SAMG20c)");
  writeSource("real(kind=REAL8),dimension(:),pointer :: resvec");

  writeSource("integer                        :: matrix");
  writeSource("real(kind=REAL8)               :: res_in,res_out");
  writeSource("integer                        :: ncyc,ncyc_done");
  writeSource("integer                        :: nsolve");
  writeSource("integer                        :: ifirst");
  writeSource("real(kind=REAL8)               :: a_cmplx,g_cmplx,p_cmplx");
  writeSource("real(kind=REAL8)               :: w_avrge");
  writeSource("real(kind=REAL8)               :: chktol");
  writeSource("integer                        :: idump");
  writeSource("integer                        :: iout");
  writeSource("integer                        :: ierr");
  writeSource("integer                        :: iswtch");
  writeSource("real(kind=REAL8 )              :: epsamg");
  com();

  // Version 8.1  81 additional parameters
  writeSource("integer,dimension(:),pointer   :: iuamg,ipamg,iscale");
  writeSource("integer                        :: nsys,npts");
  writeSource("integer                        :: ndip,ndiu");

  com();

  return;
}
//
void LIB_feelfem90vecPCG <MT_ff90vecCRS>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  int solveElementNo = 1 ;   // P2 limitation FIX

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();
  // library dependent co-solve routine module
  pushSource("use mod_samg20cparam");
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

void LIB_feelfem90vecPCG<MT_ff90vecCRS>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1

  int ivars;                // number of unknowns
  
  sprintf(hereRoutineName,"samg20cparam%d_%d",
	  solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);

  OpenSource(hereSourceName,LINKLEVEL_LIBRARY_DEPENDENT);

  pushSource("module mod_samg20cparam");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine samg20cparam");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  pushSource("(ielem,nelem,np,     &");
  flushSource();

  writeSource("      ipf,ipd,npmax,neq,                      &");
  writeSource("      iuamg,ipamg,nsys,npts,iscale             )");
  com();
  writeSource("!===============================================================");
  writeSource("! This routine calcuflate and set");
  writeSource("!");
  writeSource("! nsys   : number of equations in PDE(physcal values)");
  writeSource("!");
  writeSource("! npts   : number of nodes associates to the unknowns");
  writeSource("!       (for mixed element methods, npts is not npmax)");
  writeSource("!");
  writeSource("! iscale : allocated and set here (now just 0)");
  writeSource("!");
  writeSource("! iuamg  : allocated and set here (indicater to phsycal unknown)");
  writeSource("!");
  writeSource("! ipamg  : allocated and set here (now just 0 - future extension)");
  writeSource("!");
  writeSource("! CAUTION");
  writeSource("!");
  writeSource("! Now even if nsys==1, both iuamg and ipamg are allocated.");
  writeSource("! It seems quite costy, so it must be changed in the future. oimo");
  writeSource("!");
  writeSource("!===============================================================");

  
  SourceStarters();
  writeSource("use numeric");
  fortImplicit();
  com();

  writeSource("integer,dimension(:,:),pointer  :: ielem");
  com();
  writeSource("integer,intent(in)              :: nelem,np");
  com();

  writeSource("integer,dimension(:)            :: ipf,ipd");
  writeSource("integer,intent(in)              :: npmax");
  com();

  writeSource("integer,intent(in)              :: neq");
  
  writeSource("integer,dimension(:),pointer    :: iuamg,ipamg,iscale");
  writeSource("integer                         :: nsys,npts");  


  writeSource("! auto variables");
  writeSource("integer                         :: i,j");
  writeSource("integer                         :: ind");
  writeSource("integer,dimension(:),pointer    :: npts_calc");
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
  com();
  
  writeSource("allocate(iscale(nsys))");
  com();
  writeSource("do i=1,nsys");
  writeSource(" iscale(i) = 0");
  writeSource("end do");
  com();



  writeSource("!  if(nsys == 1) then");
  com();
  writeSource("!  here should be some program to cancel");
  writeSource("!  the usage of iu,ip array in samg20c");
  writeSource("!  solver, but npts = 0, ndiu =1 does not");
  writeSource("!  work...............oimo");

  com();
  writeSource("!  npts = 0    ! do not allocat iuamg,ipamg");
  writeSource("! nullify(iuamg)");
  writeSource("! nullify(ipamg)");
  writeSource("!  return");
  com();
  writeSource("!endif");
  com();



  writeSource("allocate(iuamg(neq))");
  writeSource("allocate(ipamg(neq))");
  com();
  writeSource("! for calculate npts, because sometimes neq/nsys != npmax");
  writeSource("allocate(npts_calc(npmax))");
  writeSource("do i=1,npmax");
  writeSource(" npts_calc(i) = 0");
  writeSource("end do");
  com();

  writeSource("! future extension");
  writeSource("do i=1,neq");
  writeSource(" ipamg(i)=0");
  writeSource("end do");
  com();


  // for own element loop
  writeSource("do i=1,nelem");

  ivars = 0;
  
  for(itr.init(); !itr;++itr) {

    ivars++;

    com();
    pushSource(" do j=1,");
    pushSourceInt( itr()->testGetElementFreedom());
    flushSource();
    
    pushSource("  ind = ielem(ienp_");
    pushSource(itr()->GetName());
    pushSource("(j),i)");
    flushSource();

    // for caluclate npts
    writeSource("  npts_calc(ind) = 1");
    com();

    pushSource("   iuamg(ipd(ind)+iedp_");
    pushSource(itr()->GetName());
    pushSource("(j)) = ");
    pushSourceInt(ivars);
    flushSource();

    writeSource(" end do");  // do j=1,number of elemets

  }
  com();

  writeSource("end do");     // do i=1,nelem
  com();


  // calculate npts
  writeSource("! calculate npts");
  com();
  writeSource("do i=1,npmax");
  writeSource(" npts = npts + npts_calc(i)");
  writeSource("end do");
  com();
  

  pushSource("end subroutine samg20cparam");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  
  flushSource();
  
  pushSource("end module mod_");
  pushSource("samg20cparam");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  flushSource();


  
  CloseSource();
  return;

}


//Library dependent solve-co routine generator
void LIB_feelfem90vecPCG <MT_ff90vecCRS>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);
  return;
}
