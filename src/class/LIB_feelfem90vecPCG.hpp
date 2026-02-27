/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90vecPCG.hpp
 *  Date     : 2001/11/29 (copy from LIB_feelfem90SAMG20c.hpp)
 *  Modified : 
 *  
 *  Purpose  : Library class feelfem90vec Vector PCG
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

#ifndef FEM_CLASS_LIB_FEELFEM90VECPCG
#define FEM_CLASS_LIB_FEELFEM90VECPCG

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90vecPCG
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90vecPCG();
  ~LIB_feelfem90vecPCG();

  void SolveCallSolverRoutine (Solve *);

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolverLibraryParameters(void);
  void SolverLibraryVariableDefinition(void);
  
  void F90useSolveLIB(void);

  // library independent cosolve routines
  void GenerateCoSolveRoutinesLIB( Solve *);
  void GenerateCoSolveSolverParamRoutine( Solve *);

};
  
#endif



