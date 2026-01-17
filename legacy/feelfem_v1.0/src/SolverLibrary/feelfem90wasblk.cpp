/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90wasblk.cpp  (copied from feelfem90SAMG20c.cpp)
 *  Date     : 2002/01/24
 *  Modified : 
 *  
 *  Purpose  : Baserman's distributed CRS matrix library solver
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90AMGCRS.hpp"
#include "LIB_feelfem90wasblk.hpp"


//Default constructor 
LIB_feelfem90wasblk <MT_ff90AMGCRS>::LIB_feelfem90wasblk()
{
  return;   // do nothing
}


//Default Destructor
LIB_feelfem90wasblk <MT_ff90AMGCRS>::~LIB_feelfem90wasblk()
{
  return;  // do nothing;
}

void LIB_feelfem90wasblk <MT_ff90AMGCRS>::SolveCallSolverRoutine(Solve *solvePtr)
{
  DoSolveMakeUpdateInformationMT();       // update information making(for some solvers)

  COMMENTlong("Allocate solution vector");
  writeSource("allocate( resvec(neq ))");
  writeSource("call zerod(resvec,neq)");
  com();

  // version 8.1 additionals
  int solveElements = 1;                // P2 FIX
  COMMENTlong("Version wasblk parameters");
  com();

  // call 
  pushSource( "call ");
  pushSource("wasblkparam");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElements);
  pushSource("(ielem,nelem,np,  &   ! nsys set,iscale allocated");
  flushSource();
  writeSource("      ipf,ipd,npmax,neq,              &   ! iuamg,ipamg allocated here");
  writeSource("      ibk,ndkind                      )   ! (if necessary)");
  com();

  writeSource("!--------------------------------------------------");
  writeSource("! WASBLK solver parameters");
  writeSource("!--------------------------------------------------");
  writeSource("resid         = 1.0d-12           ! residual");
  writeSource("isolve        = 1                 ! 0:STAB, 1:GMRES");
  writeSource("m             = 1000              ! in case of GMRES,restrat");
  writeSource("iter          = 1000              ! max ");
  writeSource("iproc         = -1                ! ???");
  com();
  writeSource("fillmap(1,1,1)= 0");
  writeSource("fillmap(1,2,1)= 0");
  writeSource("fillmap(2,1,1)= 0");
  writeSource("fillmap(2,2,1)= 0");
  writeSource("fillmap(1,1,2)= 0");
  writeSource("fillmap(1,2,2)= 0");
  writeSource("fillmap(2,1,2)= 0");
  writeSource("fillmap(2,2,2)= 0");
  com();
  writeSource("updatemap     = 0                  ! array operation");
  com();

  writeSource("call wasblksolver(neq,indrow,iptrcol,balmat,vfg,resvec, &");
  writeSource("                  nbks,ibk,ndkind,                      &");
  writeSource("                  nkinds,fillmap,updatemap,             &");
  writeSource("                  iproc,iter,fill,resid                  )");

  com();
  
  pushSource("call reportmodule('wasblk solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();
  comment();

  com();

  return;
}

void LIB_feelfem90wasblk <MT_ff90AMGCRS>::F90useSolveLIB(void)
{
  writeSource("! wasblk solver related modules");
  writeSource("! use mod_wasblk    ! interface definition");
  com();
  
  return;
}


void LIB_feelfem90wasblk <MT_ff90AMGCRS>::SolverLibraryParameters(void)
{
  writeSource("! wasblk parameters");
  writeSource("integer,parameter     :: nkinds = 2           ! temporary");
  com();

  
  return;
}

void LIB_feelfem90wasblk <MT_ff90AMGCRS>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables(wasblk)");
  writeSource("real(kind=REAL8),dimension(:),pointer :: resvec");
  com();

  writeSource("! block information");
  writeSource("integer                               :: nbks");
  writeSource("integer,dimension(:),pointer          :: ibk0,nodekind0");
  com();

  writeSource("! solver parameter");
  writeSource("integer                                 :: isolve,m");
  writeSource("integer                                 :: iproc,iter");
  writeSource("real(kind=REAL8)                        :: resid");
  com();

  writeSource("integer,dimension(nkinds,nkinds,nkinds) :: fillmap");
  writeSource("integer,dimension(nkinds,nkinds,nkinds) :: updatemap");
  com();

  return;
}
//
void LIB_feelfem90wasblk <MT_ff90AMGCRS>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  int solveElementNo = 1 ;   // P2 limitation FIX

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();
  // library dependent co-solve routine module
  pushSource("use mod_wasblkparam");
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

void LIB_feelfem90wasblk<MT_ff90AMGCRS>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1

  int ivars;                // number of unknowns
  
  sprintf(hereRoutineName,"wasblkparam%d_%d",
	  solvePtr->GetSolveNo(),solveElementNo);  
  hereSourceName = GetSourceName(hereRoutineName);

  OpenSource(hereSourceName,LINKLEVEL_LIBRARY_DEPENDENT);

  pushSource("module mod_wasblkparam");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  flushSource();
  writeSource("contains");
  com();

  pushSource("subroutine wasblkparam");
  pushSourceInt( solvePtr->GetSolveNo());
  pushSource("_");
  pushSourceInt(solveElementNo);
  pushSource("(ielem,nelem,np,     &");
  flushSource();

  writeSource("      ipf,ipd,npmax,neq,                   &");
  writeSource("      nbks,ibk,ndkind                      )");
  com();
  writeSource("!============================================================");
  writeSource("! wasblk solver parameter setting");
  writeSource("!============================================================");

  
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
void LIB_feelfem90wasblk <MT_ff90AMGCRS>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);
  return;
}
