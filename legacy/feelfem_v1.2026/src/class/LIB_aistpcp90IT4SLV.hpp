/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_aistpcp90IT4SLV.hpp
 *  Date     : 2002/06/28   (copy from LIB_feelfem90AMG81.hpp)
 *  Modified : 
 *  
 *  Purpose  : Library class feelfem90 GMD AMG ver 8.1library 
 *  
 */

#ifndef FEM_CLASS_LIB_AISTPCP90IT4SLV
#define FEM_CLASS_LIB_AISTPCP90IT4SLV

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_aistpcp90IT4SLV
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_aistpcp90IT4SLV();
  ~LIB_aistpcp90IT4SLV();

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



