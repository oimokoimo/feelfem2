/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelP2PCG.hpp
 *  Date     : 1999/11/22
 *  Modified : 1999/11/22
 *  
 *  Purpose  : Library class FEEL P2 version PCG solver 
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

#ifndef FEM_CLASS_LIB_FEELP2PCG
#define FEM_CLASS_LIB_FEELP2PCG

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelP2PCG 
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelP2PCG();
  ~LIB_feelP2PCG();

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB( char *,Solve *);

  void SolveCallSolverRoutine (Solve *);
  void SolverLibraryParameters(void);
  void SolverLibraryArgumentVariableDefinition(void);

};
  
#endif
