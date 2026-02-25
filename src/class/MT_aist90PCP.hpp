/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_aist90PCP.hpp
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

#ifndef FEM_CLASS_MT_AIST90PCP
#define FEM_CLASS_MT_AIST90PCP

#include "PM_aistpcp90.hpp"                // FEM Program Model

class MT_aist90PCP : public PM_aistpcp90 {

public:
  MT_aist90PCP();  // Constructor
  ~MT_aist90PCP(); // Destructor

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
