/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem90AchimCG.cpp
 *  Date     : 2001/01/24
 *  Modified : 2001/01/24
 *  
 *  Purpose  : Single processor Achim CG (f90 version)
 *  
 */

#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_ff90AMGCRS.hpp"
#include "LIB_feelfem90AchimCG.hpp"


//Default constructor 
LIB_feelfem90AchimCG <MT_ff90AMGCRS>::LIB_feelfem90AchimCG()
{
  return;   // do nothing
}


//Default Destructor
LIB_feelfem90AchimCG <MT_ff90AMGCRS>::~LIB_feelfem90AchimCG()
{
  return;  // do nothing;
}


void LIB_feelfem90AchimCG <MT_ff90AMGCRS>::SolveCallSolverRoutine(Solve *solvePtr)
{
  //  DoSolveMakeUpdateInformationMT(); 
  // update information making(for some solvers)
  // not necessary for AchimCG solver   it confusing because AMGCRS 
  // is used only for amg solvers at first........

  COMMENTlong("Allocate solution vector");
  writeSource("allocate( resvec(neq))");
  writeSource("call zerod(resvec,neq)");
  com();

  COMMENTlong("Achim CG parameters (Main parameters read from cg110loc.in");

  writeSource("outlev    =    0        ! 0 no output");
  writeSource("                        ! 1 minimum output");
  writeSource("                        ! 2 medium output");
  writeSource("                        ! 3 maximal output");
  com();

  writeSource("choicerhs =    1        ! 1 ");
  com();
  
  writeSource("solvstart =    2        ! 2 ");
  com();

  writeSource("if(ismpicalled .ne. 1) then");
  writeSource("  call mpi_init(ierr)");
  writeSource("  call mpi_comm_size(mpi_comm_world,nprocs,ierr)");
  writeSource("  call mpi_comm_rank(mpi_comm_world,myrank,ierr)");
  writeSource("  ismpicalled = 1");
  writeSource("end if");
  com();

  writeSource("call cg110loc_f90(myrank,neq,ncof,valmat,indrow,iptrcol, &");
  writeSource("                  vfg,resvec,choicerhs,solvstart,outlev   )");
  com();
  
  pushSource(" call reportmodule('AchimCG90 solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();
  comment();

  com();

  return;
}

void LIB_feelfem90AchimCG <MT_ff90AMGCRS>::F90useSolveLIB(void)
{
  writeSource("! AMG solver related modules");
  writeSource("use mod_achim_cg");
  com();
  
  return;
}


void LIB_feelfem90AchimCG <MT_ff90AMGCRS>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_feelfem90AchimCG <MT_ff90AMGCRS>::SolverLibraryParameters(void)");
  return;
}

void LIB_feelfem90AchimCG <MT_ff90AMGCRS>::SolverLibraryVariableDefinition(void)
{
  COMMENTlong("Solver Library dependent variables");
  writeSource("real(kind=REAL8),dimension(:),pointer :: resvec");

  writeSource("integer                               :: choicerhs");
  writeSource("integer                               :: solvstart");
  writeSource("integer                               :: outlev");
  writeSource("integer                               :: myrank,nprocs,ierr");
  writeSource("integer,save                          :: ismpicalled = 0");
  com();

  writeSource("include 'mpif.h'");   // should be temporary
  com();

  return;
}

//
void LIB_feelfem90AchimCG<MT_ff90AMGCRS>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  F90useSolveLIB();
  F90useSolveMT();
  F90useSolvePM(solvePtr);
  
  fortImplicit();
  com();

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent
  
  return;
}



void LIB_feelfem90AchimCG<MT_ff90AMGCRS>::
GenerateCoSolveSolverParamRoutine(Solve *solvePtr)
{
  SolveElement *sePtr = solvePtr->GetIthSolveElementPtr(0); // P2 FIXED

  char  hereRoutineName[BUFSIZ];
  char *hereSourceName;

  int solveElementNo = 1;   // P2 FIXED to 1

  int ivars;                // number of unknowns

  //  no coroutine for this solver required

  return;

}

//Library dependent solve-co routine generator
void LIB_feelfem90AchimCG <MT_ff90AMGCRS>::
GenerateCoSolveRoutinesLIB(Solve *solvePtr)
{
  GenerateCoSolveSolverParamRoutine(solvePtr);    // iu, etc set
  return;
}
