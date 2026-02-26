/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelP2iwashita.hpp
 *  Date     : 2000/11/23
 *  Modified : 
 *  
 *  Purpose  : Library class FEEL P2 version iwashita Library
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

#ifndef FEM_CLASS_LIB_FEELP2IWASHITA
#define FEM_CLASS_LIB_FEELP2IWASHITA

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelP2iwashita
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelP2iwashita();
  ~LIB_feelP2iwashita();

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolveCallSolverRoutine (Solve *);
  

};
  
#endif
