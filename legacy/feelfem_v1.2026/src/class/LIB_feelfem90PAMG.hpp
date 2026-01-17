/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelfem90PAMG.hpp
 *  Date     : 2000/10/25
 *  Modified : 2000/10/25
 *  
 *  Purpose  : Library class feelfem90 GMD PAMG library 
 *  
 */

#ifndef FEM_CLASS_LIB_FEELFEM90PAMG
#define FEM_CLASS_LIB_FEELFEM90PAMG

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelfem90PAMG
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelfem90PAMG();
  ~LIB_feelfem90PAMG();

  void SolveCallSolverRoutine (Solve *);

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB(char *, Solve *);

  void SolverLibraryParameters(void);
  void SolverLibraryVariableDefinition(void);
  
  void F90useSolveLIB(void);

};
  
#endif
