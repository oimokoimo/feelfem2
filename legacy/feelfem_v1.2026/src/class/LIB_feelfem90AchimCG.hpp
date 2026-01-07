/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90AchimCG.hpp
 *  Date     : 2001/01/24
 *  Modified : 2001/01/24
 *  
 *  Purpose  : Library class feelfem90 Achim CG Fortran90 version
 *  
 */

#ifndef FEM_CLASS_LIB_FEELFEM90ACHIMCG
#define FEM_CLASS_LIB_FEELFEM90ACHIMCG

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90AchimCG
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90AchimCG();
  ~LIB_feelfem90AchimCG();

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
