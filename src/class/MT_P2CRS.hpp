/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRS.hpp
 *  Date     : 1999/12/07
 *  Modified : 1999/12/07
 *  
 *  Purpose  : CRS storage for FEEL P2 program model
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

#ifndef FEM_CLASS_MT_P2CRS
#define FEM_CLASS_MT_P2CRS

#include "PM_feelP2.hpp"           // FEM Program Model

class MT_P2CRS : public PM_feelP2 {

public:
  MT_P2CRS();  // Constructor
  ~MT_P2CRS(); // Destructor

  // P2/CRS dependent argument list
  void pushMatrixArgumentsCalled(void);      // valmat,indptr,....
  void pushMatrixArgumentsAllocated(void);   // feel(np_VALMAT),...
  void writeMatrixDeclarations(void);

  // nvmax,nfmax ......
  void DoSolveCallLinearNeumannData  ( Solve *);
  void DoSolveCallLinearDirichletData( Solve *);
  void DoSolveCallEdevRoutine        ( Solve *); //distributed case, obligatoy
  void DoSolveFreeMemoryMT();

  // solver related
#include "DO_solve_MT.hpp"

  // Element Assembly   
#include "DO_elem_MT.hpp"

  // MT Dirichlet generators
#include "DO_dirichlet_MT.hpp"


  // Neumann Conditions
  void DoNeumannRoutineHeaderMT(Neumann *);
  void DoNeumannArgumentSequenceMT(Neumann *);
  void DoNeumannApplyMatrixMT(Neumann *);

  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);


};

#endif
