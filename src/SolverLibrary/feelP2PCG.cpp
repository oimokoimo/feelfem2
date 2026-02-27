/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2PCG.cpp
 *  Date     : 1999/11/22
 *  Modified : 1999/11/22
 *  
 *  Purpose  :
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
#include "MT_P2PCG.hpp"
#include "LIB_feelP2PCG.hpp"

//template <class MatMODEL> LIB_feelP2PCG <MatMODEL>::~LIB_feelP2PCG()
template <> LIB_feelP2PCG <MT_P2PCG>::LIB_feelP2PCG()
{
//  cerr << "Constructor must be with Solve class\n";
//  exit(1);
}


//template <class MatMODEL> LIB_feelP2PCG <MatMODEL>::~LIB_feelP2PCG()
template <> LIB_feelP2PCG <MT_P2PCG>::~LIB_feelP2PCG() = default;

//template <class MatMODEL> LIB_feelP2PCG <MatMODEL>::SolveCallSolverRoutine()
template <> void LIB_feelP2PCG <MT_P2PCG>::SolveCallSolverRoutine(Solve *solvePtr)
{
  writeSource("*=========================");
  writeSource("* CALL WEBRMS SOLVER      ");
  writeSource("*=========================");

  writeSource("      IDS    = 2");
  writeSource("      IPM(1) = 0");
  writeSource("      IPM(3) = 0");
  writeSource("      IPM(4) = 0");
  writeSource("      IPM(5) = 1");
  writeSource("      IPM(6) = 0");
  writeSource("      IPM(7) = 0");
  writeSource("      IPM(8) = 0");
  writeSource("      RPM(1) = 1.0D-12");
  writeSource("      RPM(4) = 0.10");
  writeSource("      RPM(5) = 0.95");
  com();

  writeSource("      call WEBRMS(feel(np_A),neq,neq,MJ,feel(np_JA),JDP,feel(np_B),");
  writeSource("     $            feel(np_U),IDS,IPM,RPM,feel(np_IW),feel(np_W),OUT,");
  writeSource("     $            IERR)");
  com();

  writeSource("      if(IERR.ne.0) then");
  writeSource("        write(*,*) 'WEBRMS RETURNS ',IERR");
  writeSource("      endif");
  com();
  
  pushSource("      call report('P2 PCG Solver for solve ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" END')");
  flushSource();

  writeSource("      call rep_CG(IPM(2),RPM(2))");

  comment();

  return;
}


template <> void LIB_feelP2PCG <MT_P2PCG>::SolverLibraryParameters(void) { doNothingNow("void LIB_feelP2PCG <MT_P2PCG>::SolverLibraryParameters(void)");
  return;
}

template <> void LIB_feelP2PCG <MT_P2PCG>::SolverLibraryArgumentVariableDefinition(void)
{
  doNothingNow("void LIB_feelP2PCG <MT_P2PCG>::SolverLibraryArgumentVariableDefinition(void)");
  return;
}

//
template <> void LIB_feelP2PCG <MT_P2PCG>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent

  return;
}
