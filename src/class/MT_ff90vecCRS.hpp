/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90vecCRS.hpp
 *  Date     : 2001/11/29 (Copy MT_ff90AMGCRS.hpp)
 *  Modified : 
 *  
 *  Purpose  : Fortran90 AMGCRS matrix model for vector processor
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

#ifndef FEM_CLASS_MT_FF90CRSVEC
#define FEM_CLASS_MT_FF90CRSVEC

#include "PM_feelfem90vec.hpp"                // FEM Program Model

class MT_ff90vecCRS : public PM_feelfem90vec {

public:
  MT_ff90vecCRS();  // Constructor
  ~MT_ff90vecCRS(); // Destructor

  void F90useSolveMT(void);

  // P2/CRS dependent argument list
  void pushMatrixArgumentsCalled(void);      // in feelfem90, same as below
  void pushMatrixArgumentsAllocated(void);   // in feelfem90, same as over
  void writeMatrixDeclarations(void);

  // nvmax,nfmax ......

  void DoSolveCallLinearNeumannData  ( Solve *);
  void DoSolveCallLinearDirichletData( Solve *);
  void DoSolveCallEdevRoutine        ( Solve *); // distributed case, obligatoy
  void DoSolveMakeUpdateInformationMT( void   ); // make update information 
                                                 // after dcond
  void DoSolveFreeMemoryMT(); 

  // Solve part
#include "DO_solve_MT.hpp"

  // Element Assembly   
#include "DO_elem_MT.hpp"

  // MT Dirichlet generator
#include "DO_dirichlet_MT.hpp"

  // Neumann Conditions
  void DoNeumannRoutineHeaderMT(Neumann *);
  void DoNeumannArgumentSequenceMT(Neumann *);
  void DoNeumannApplyMatrixMT(Neumann *);


  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);
  void GenerateCoSolveEdevRoutine( Solve *);

};

#endif


