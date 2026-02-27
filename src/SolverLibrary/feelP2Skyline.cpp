/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelP2Skyline.cpp
 *  Date     : 1999/11/11
 *  Modified : 1999/11/11
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
#include "MT_P2Skyline.hpp"
#include "LIB_feelP2Skyline.hpp"

//template <class MatMODEL> LIB_feelP2Skyline <MatMODEL>::~LIB_feelP2Skyline()
template <> LIB_feelP2Skyline <MT_P2Skyline>::LIB_feelP2Skyline()
{
  return;  // do nothing
}


//template <class MatMODEL> LIB_feelP2Skyline <MatMODEL>::~LIB_feelP2Skyline()
template <> LIB_feelP2Skyline <MT_P2Skyline>::~LIB_feelP2Skyline()=default;

//template <class MatMODEL> LIB_feelP2Skyline <MatMODEL>::SolveCallSolverRoutine()
template <> void LIB_feelP2Skyline <MT_P2Skyline>::SolveCallSolverRoutine(Solve *solvePtr)
{
  writeSource("*=========================");
  writeSource("* CALL SKYLINE SOLVER     ");
  writeSource("*=========================");
  writeSource("      np_resvec = np_VFG");
  com();

  writeSource("      IFAC = 1");
  writeSource("      ISOL = 1");
  writeSource("      NSYM = 1");
  writeSource("      call SOL(feel(np_VKGS),feel(np_VKGD),feel(np_VKGI),");
  writeSource("     $         feel(np_VFG),feel(np_KLD),neq,io_stderr,");
  writeSource("     $         IFAC,ISOL,NSYM,ENERG)");
  com();
  
  pushSource("      call report('P2 Skyline Solver for solve ");
  pushSourceInt(solvePtr->GetSolveNo());
  pushSource(" END')");
  flushSource();
  comment();

  return;
}

// SolverLibrary dependent program portions

template <> void LIB_feelP2Skyline <MT_P2Skyline>::SolverLibraryParameters(void)
{
  doNothingNow("void LIB_feelP2Skyline <MT_P2Skyline>::SolverLibraryParameters(void)");
  return;
}

template <> void LIB_feelP2Skyline <MT_P2Skyline>::SolverLibraryArgumentVariableDefinition(void)
{
  doNothingNow("void LIB_feelP2Skyline <MT_P2Skyline>::SolverLibraryArgumentVariableDefinition(void)");
  return;
}

//
template<> void LIB_feelP2Skyline <MT_P2Skyline>::
DoSolveRoutineHeaderInLIB(char *routineName, Solve *solvePtr) {

  DoArgumentSequenceFromMain( routineName, solvePtr->VariablePtrLst() ); //PM
  DoSolveStarters();                                                 //PM

  DoDeclareVariablesFromMainPM( solvePtr->VariablePtrLst());   //Fortran dependent

  return;
}

