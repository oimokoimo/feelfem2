/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : LIB_feelP2Skyline.hpp
 *  Date     : 1999/11/10
 *  Modified : 1999/11/11
 *  
 *  Purpose  : Library class FEEL P2 version skyline solver
 *  
 */

#ifndef FEM_CLASS_LIB_FEELP2SKYLINE
#define FEM_CLASS_LIB_FEELP2SKYLINE

#include "SolveGeneratorTemplate.hpp"

template <class MatMODEL> class LIB_feelP2Skyline 
  :public SolveGeneratorTemplate <MatMODEL> {
public:
  LIB_feelP2Skyline();
  ~LIB_feelP2Skyline();

  // Virtual functions in SolveGeneratorTemplate
  void DoSolveRoutineHeaderInLIB( char *,Solve *);

  void SolveCallSolverRoutine (Solve *);
  void SolverLibraryParameters(void);
  void SolverLibraryArgumentVariableDefinition(void);
  

};
  
#endif

