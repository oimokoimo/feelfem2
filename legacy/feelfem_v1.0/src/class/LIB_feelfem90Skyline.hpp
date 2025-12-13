/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90Skyline.hpp
 *  Date     : 2002/03/06 (Copied from LIB_feelfem90SAMG20c.hpp)
 *  Modified :
 *  
 *  Purpose  : Library class feelfem90 Skyline
 *  
 */

#ifndef FEM_CLASS_LIB_FEELFEM90SKYLINE
#define FEM_CLASS_LIB_FEELFEM90SKYLINE

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90Skyline
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90Skyline();
  ~LIB_feelfem90Skyline();

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



