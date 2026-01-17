/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90Lumping.hpp
 *  Date     : 2002/10/07 (Copied from LIB_feelfemskyline.hpp)
 *  Modified :
 *  
 *  Purpose  : Library class feelfem90 Lumping
 *  
 */

#ifndef FEM_CLASS_LIB_FEELFEM90LUMPING
#define FEM_CLASS_LIB_FEELFEM90LUMPING

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90Lumping
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90Lumping();
  ~LIB_feelfem90Lumping();

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



