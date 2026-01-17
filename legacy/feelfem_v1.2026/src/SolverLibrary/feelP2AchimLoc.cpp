/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2AchimLoc.cpp
 *  Date     : 2000/03/24
 *  Modified : 2000/03/24
 *  
 *  Purpose  : Baserman's distributed CRS matrix library solver
 *  
 */
#include "feelfem.hpp"

#include "Solve.hpp"
#include "MT_P2CRSLOC.hpp"
#include "LIB_feelP2AchimLoc.hpp"


//Default constructor 
LIB_feelP2AchimLoc <MT_P2CRSLOC>::LIB_feelP2AchimLoc()
{
  return;   // do nothing
}



//Default Destructor
LIB_feelP2AchimLoc <MT_P2CRSLOC>::~LIB_feelP2AchimLoc()
{
  return;  // do nothing;
}

void LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolveCallSolverRoutine(Solve *solvePtr)
{
  wrtDEBUGcode("* LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolveCallSolverRoutine");

  writeSource("*=========================");
  writeSource("* CALL AchimLoc SOLVER");
  writeSource("*=========================");
  writeSource("      call f_alloc(np_resvec,'resvec',neq,1,0)");
  writeSource("      call zerod(feel(np_resvec),neq)");
  com();

  writeSource("      nf_choicderhs = 1");
  writeSource("      nf_outlev     = 1");
  writeSource("      nf_indcmaac   = 0");
  writeSource("      nf_solvstart  = 2");
  com();
  writeSource("      call mpi_barrier(mpi_comm_world,ierr)");
  
  writeSource("      call cg110loc_feel(feel,");
  writeSource("     $     myrank,neq,ncof,feel(np_valmat),nf_indcmaac,");
  writeSource("     $     feel(np_indrow),feel(np_iptrcol),feel(np_vfg),");
  writeSource("     $     feel(np_resvec),");
  writeSource("     $     nf_choicderhs,nf_solvstart,nf_outlev)");

  pushSource("      if(myrank.eq.0) call preportmodule('CG110LOC solve No.");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" Finished')");
  flushSource();
  comment();

  com();

  return;
}



// SolverLibrary dependent program portions

void LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolverLibraryParameters(void)
{
  wrtDEBUGcode("* LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolverLibraryParameters");

  doNothingNow("void LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolverLibraryParameters(void)");
  return;
}

void LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolverLibraryArgumentVariableDefinition(void)
{
  wrtDEBUGcode("* LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolverLibraryArgumentVariableDefinition");

  doNothingNow("void LIB_feelP2AchimLoc <MT_P2CRSLOC>::SolverLibraryArgumentVariableDefinition(void)");
  return;
}

void LIB_feelP2AchimLoc <MT_P2CRSLOC>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  wrtDEBUGcode("LIB_feelP2AchimLoc <MT_P2CRSLOC>::DoSolveRoutineHeaderInLIB");

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent

  return;
}
