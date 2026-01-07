/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90AMG81.hpp
 *  Date     : 2000/12/08
 *  Modified : 2000/12/08
 *  
 *  Purpose  : Library class feelfem90 GMD AMG ver 8.1library 
 *  
 */

#ifndef FEM_CLASS_LIB_FEELFEM90AMG81
#define FEM_CLASS_LIB_FEELFEM90AMG81

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90AMG81
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90AMG81();
  ~LIB_feelfem90AMG81();

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



