/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2PCG.hpp
 *  Date     : 1999/11/22
 *  Modified : 1999/11/22
 *  
 *  Purpose  : Matrix Allocations for feel P2 iteration solver 
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

#ifndef FEM_CLASS_MT_P2PCG
#define FEM_CLASS_PM_P2PCG

#include "PM_feelP2.hpp"           // FEM Program Model

class MT_P2PCG : public PM_feelP2 {

public:
  MT_P2PCG();  // Constructor
  ~MT_P2PCG(); // Destructor


  void DoSolveCallLinearNeumannData(Solve *);
  void DoSolveCallLinearDirichletData(Solve *);
  void DoSolveCallEdevRoutine(Solve *);
  void DoSolveFreeMemoryMT();


  // solve related
#include "DO_solve_MT.hpp"


  // ElemGenerator main
#include "DO_elem_MT.hpp"

  // Neumann Conditions
  void DoNeumannRoutineHeaderMT(Neumann *);
  void DoNeumannArgumentSequenceMT(Neumann *);
  void DoNeumannApplyMatrixMT(Neumann *);


  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);
  void GenerateCoSolveEdevRoutine( Solve *);

};

#endif

