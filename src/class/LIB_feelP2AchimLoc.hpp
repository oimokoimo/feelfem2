/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelP2AchimLoc.hpp
 *  Date     : 2000/03/24
 *  Modified : 2000/03/24
 *  
 *  Purpose  : Library class FEEL P2 Baserman's loc distributed solver
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

#ifndef FEM_CLASS_LIB_FEELP2ACHIMLOC
#define FEM_CLASS_LIB_FEELP2ACHIMLOC

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelP2AchimLoc
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelP2AchimLoc();
  ~LIB_feelP2AchimLoc();


  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolveCallSolverRoutine (Solve *);
  void SolverLibraryParameters(void);
  void SolverLibraryArgumentVariableDefinition(void);
  

};
  
#endif
