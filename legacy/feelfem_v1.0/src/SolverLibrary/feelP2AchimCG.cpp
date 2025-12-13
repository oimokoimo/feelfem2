/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2AchimCG.cpp
 *  Date     : 2001/01/25
 *  Modified : 
 *  
 *  Purpose  : cg110loc version to use in single
 *  
 */

#include "MT_P2CRS.hpp"
#include "Solve.hpp"
#include "LIB_feelP2AchimCG.hpp"


//Default constructor 
LIB_feelP2AchimCG <MT_P2CRS>::LIB_feelP2AchimCG()
{
  return;   // do nothing
}



//Default Destructor
LIB_feelP2AchimCG <MT_P2CRS>::~LIB_feelP2AchimCG()
{
  return;  // do nothing;
}

void LIB_feelP2AchimCG <MT_P2CRS>::SolveCallSolverRoutine(Solve *solvePtr)
{
  wrtDEBUGcode("LIB_feelP2AchimCG <MT_P2CRS>::SolveCallSolverRoutine");

  writeSource("*=========================");
  writeSource("* CALL Achim SOLVER     ");
  writeSource("*=========================");

  writeSource("      call mpi_init(ierr)");
  writeSource("      call mpi_comm_size(mpi_comm_world,nprocs,ierr)");
  writeSource("      call mpi_comm_rank(mpi_comm_world,myrank,ierr)");
  com();
  
  writeSource("      nf_choicderhs = 1");
  writeSource("      nf_outlev     = 3");
  writeSource("      nf_indcmaac   = 0");
  writeSource("      nf_solvstart  = 2");         
  com();
  
  writeSource("      call cg110loc_feel(feel,");
  writeSource("     $     myrank,neq,ncof,feel(np_valmat),nf_indcmaac,");
  writeSource("     $     feel(np_indrow),feel(np_iptrcol),feel(np_vfg),");
  writeSource("     $     feel(np_resvec),");
  writeSource("     $     nf_choicderhs,nf_solvstart,nf_outlev)");

  com();

  pushSource("      call report('P2 Achim Solver for solve ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" END')");
  flushSource();
  comment();

  return;
}

//
void LIB_feelP2AchimCG <MT_P2CRS>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  wrtDEBUGcode("* LIB_feelP2AchimCG <MT_P2CRS>::DoSolveRoutineHeaderInLIB");

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent

  writeSource("      include 'mpif.h'");  // RINJI

  return;
}

