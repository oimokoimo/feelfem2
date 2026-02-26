/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelP2AchimCG.hpp
 *  Date     : 2001/01/25
 *  Modified : 
 *  
 *  Purpose  : Library class FEEL P2 version Achim Library(cg110loc call)
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

#ifndef FEM_CLASS_LIB_FEELP2ACHIMCG
#define FEM_CLASS_LIB_FEELP2ACHIMCG

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelP2AchimCG
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelP2AchimCG();
  ~LIB_feelP2AchimCG();

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolveCallSolverRoutine (Solve *);
  

};
  
#endif
