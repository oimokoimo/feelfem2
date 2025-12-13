/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SG_feelP2Skyline.hpp
 *  Date     : 1999/11/18
 *  Modified : 1999/11/18
 *  
 *  Purpose  : Solve routine generator for feelP2 skyline
 *  
 */

#ifndef FEM_CLASS_SOLVEGENERATOR
#define FEM_CLASS_SOLVEGENERATOR

#include "MT_feelP2Skyline.hpp"
#include "SolveScheme.hpp"

//if possible, it should be template

template <class MODEL> class SG_feelP2Skyline 
  : public <MODEL>,
    public SolveScheme {
public:
  SG_feelP2Skyline();
  ~SG_feelP2Skyline();


  void SolveArgumentSequence    (Solve &);
  
  void SolveParameters          (Solve &);

  void SolveVariableDefinitions (Solve &);

  void SolveFortranCommons      (Solve &);
  
  void SolveInitializer         (Solve &);
  
  void SolveDegreeOfFreedom     (Solve &);
  
  void SolveMatrixAllocate      (Solve &);

  void SolveCallAssembleRoutine (Solve &);

  void SolveNeumannConditions   (Solve &);

  void SolveDirichletConditions (Solve &);

  void SolvePostProcess         (Solve &);   // edev routine

  void SolveTerminateSequence   (Solve &);

  void SolveReturnSequence      (Solve &);

  /////////////////////////////////////////////////////////////////////

  // Library dependent functions
  virtual void SolveCallSolverRoutine   (Solve &);
private:
  
};

#endif

