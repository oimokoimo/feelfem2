/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90smpiMUMPSCA.hpp
 *  Date     : 2003/01/01 (Copied from MT_ff90AMGCRS.hpp)
 *  Modified : 2003/01/04
 *  
 *  Purpose  : Fortran90 MUMPSCA matrix model
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

#ifndef FEM_CLASS_MT_FF90SMPIMUMPSCA
#define FEM_CLASS_MT_FF90SMPIMUMPSCA

#include "PM_feelfem90smpi.hpp"                // FEM Program Model

class MT_ff90smpiMUMPSCA : public PM_feelfem90smpi {

public:
  MT_ff90smpiMUMPSCA();  // Constructor
  ~MT_ff90smpiMUMPSCA(); // Destructor

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

  // Elem part
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
