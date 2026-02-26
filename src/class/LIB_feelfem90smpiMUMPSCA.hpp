/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90smpiMUMPSCA.hpp
 *  Date     : 2003/01/01 (Copied from SAMG20c)
 *  Modified : 2003/01/04
 *  
 *  Purpose  : Library class feelfem90smpi MUMPS Centered Assembled
 *
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

#ifndef FEM_CLASS_LIB_FEELFEM90SMPIMUMPSCA
#define FEM_CLASS_LIB_FEELFEM90SMPIMUMPSCA

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90smpiMUMPSCA
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90smpiMUMPSCA();
  ~LIB_feelfem90smpiMUMPSCA();

  void SolveCallSolverRoutine (Solve *);

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolverLibraryParameters(void);
  void SolverLibraryVariableDefinition(void);
  
  void F90useSolveLIB(void);

  // library independent cosolve routines
  void GenerateCoSolveRoutinesLIB( Solve *);
  void GenerateCoSolveSolverParamRoutine( Solve *);

};
  
#endif



