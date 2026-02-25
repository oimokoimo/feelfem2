/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90AMGCRS.hpp
 *  Date     : 2000/12/08
 *  Modified : 2000/12/08
 *  
 *  Purpose  : Fortran90 AMGCRS matrix model
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

#ifndef FEM_CLASS_MT_FF90AMGCRS
#define FEM_CLASS_MT_FF90AMGCRS

#include "PM_feelfem90.hpp"                // FEM Program Model

class MT_ff90AMGCRS : public PM_feelfem90 {

public:
  MT_ff90AMGCRS();  // Constructor
  ~MT_ff90AMGCRS(); // Destructor

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

  // Dirichlet Conditions
#include "DO_dirichlet_MT.hpp"

  // Neumann Conditions
#include "DO_neumann_MT.hpp"

  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);
  void GenerateCoSolveEdevRoutine( Solve *);

};

#endif
