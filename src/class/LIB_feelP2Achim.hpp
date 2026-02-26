/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelP2Achim.hpp
 *  Date     : 1999/12/09
 *  Modified : 1999/12/09
 *  
 *  Purpose  : Library class FEEL P2 version Achim Library
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

#ifndef FEM_CLASS_LIB_FEELP2ACHIM
#define FEM_CLASS_LIB_FEELP2ACHIM

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelP2Achim
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelP2Achim();
  ~LIB_feelP2Achim();

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolveCallSolverRoutine (Solve *);
  

};
  
#endif
