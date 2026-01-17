/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveScheme.hpp
 *  Date     : 1999/10/26
 *  Modified : 1999/11/09
 *  
 *  Purpose  : Abstract numerical scheme definition class
 *  
 *  
 *  
 */
#ifndef FEM_SOLVEGENERATOR_CLASS
#define FEM_SOLVEGENERATOR_CLASS


#include "Solve.hpp"

class SolveScheme {

public:
  SolveScheme();
  ~SolveScheme();

  // Scheme Libraries  (These are NOT VIRTUAL functions)
  void NormalLinearProblem     (Solve *);   
  void NormalNonlinearProblem  (Solve *);

  // File management routines
  virtual void SolveRoutineInitialize(Solve *);
  virtual void SolveRoutineTerminate (Solve *);

  // Basic main procedures in FEM procedures
  virtual void SolveRoutineHeader      (Solve *);  // Language dependent

  virtual void SolveParameters         (Solve *);  // Program Model
  virtual void SolveVariableDefinitions(Solve *);  // Program Model
  virtual void SolveInitializer        (Solve *);  // Program Model
  virtual void SolveDegreeOfFreedom    (Solve *);  // Program Model
  virtual void SolveBoundaryDataPreparation(Solve *);  // Program Model
  virtual void SolveMatrixAllocate     (Solve *);  // Matrix model
  virtual void SolveCallAssembleRoutine(Solve *);  // Program Model
  virtual void SolveNeumannConditions  (Solve *);  // Program Model
  virtual void SolveDirichletConditions(Solve *);  // Program Model
  virtual void SolveCallSolverRoutine  (Solve *);  // Program Model
  virtual void SolvePostProcess        (Solve *);  // Program Model
  virtual void SolveTerminateSequence  (Solve *);  // Program Model
  virtual void SolveReturnSequence     (Solve *);  // Program Model

  // Parallel computation
  virtual void SolveAssemblyPreparation (Solve *);   // Program Model

  virtual void SolveNonlinearInitialize(Solve *);  // Nonlinear
  virtual void SolveNonlinearPostProcess(Solve *); // Nonlinear

  // FEM procedures (Strongly dependent on Program model)

  // Solver related procedures (Dependent on solver libraries)
  //  virtual void SolveLibraryDependentDeclares(); // LIB
  //  virtual void SolveAllocMat();                 // LIB
  //  virtual void SolveCalcMatTopologie();         // LIB

private:
  static int solveSchemes;

};

#endif
