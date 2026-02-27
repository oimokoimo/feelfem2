/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveGeneratorTemplate.hpp
 *  Date     : 1999/11/18
 *  Modified : 1999/11/18
 *  Modified : 2001/01/31 LINKLEVEL_SOLVE added
 *
 *  Purpose  : Solve routine generator template
 *
 *             SolveScheme class deals with only pure abstract scheme.
 *             SolveGeneratorTemplate deals with implementation
 *                                    (ex. let XXX = OP(YYY) etc.)
 */

#ifndef FEM_CLASS_SOLVEGENERATORTEMPLATE
#define FEM_CLASS_SOLVEGENERATORTEMPLATE

#include "feelfuncs.hpp"
#include "SolveScheme.hpp"

// forward declarations（ヘッダ依存を軽くする）
class Solve;

template <class MatMODEL>
class SolveGeneratorTemplate : public MatMODEL, public SolveScheme {
public:
  SolveGeneratorTemplate() = default;
  ~SolveGeneratorTemplate() = default;

  // Several Initializers
  void SetSolveNo2SolveGeneratorTemplate(int no)
  {
    solveNo     = no;
    routineName = this->GetSolveRoutineName(no); // two-phase lookup 対応
  }

  void SolveRoutineInitialize   (Solve *);
  void SolveRoutineTerminate    (Solve *);

  void SolveRoutineHeader       (Solve *);   // Language dependent
  void SolveParameters          (Solve *);
  void SolveVariableDefinitions (Solve *);
  void SolveInitializer         (Solve *);
  void SolveDegreeOfFreedom     (Solve *);
  void SolveAssemblyPreparation (Solve *);
  void SolveBoundaryDataPreparation (Solve *);
  void SolveMatrixAllocate      (Solve *);
  void SolveCallAssembleRoutine (Solve *);
  void SolveNeumannConditions   (Solve *);
  void SolveDirichletConditions (Solve *);
  void SolvePostProcess         (Solve *);   // edev routine
  void SolveTerminateSequence   (Solve *);
  void SolveReturnSequence      (Solve *);

  /////////////////////////////////////////////////////////////////////

  // Library dependent functions (SolveHeader)
  virtual void DoSolveRoutineHeaderInLIB(const char *, Solve *);

  // Library dependent functions (SolveVariableDefinitions)
  virtual void SolverLibraryParameters();
  virtual void SolverLibraryVariableDefinition();

  // Library dependent functions (SolveCallSolvers)
  virtual void SolveCallSolverRoutine    (Solve *);
  virtual void GenerateCoSolveRoutinesLIB(Solve *);

private:
  const char *routineName = nullptr;
  const char *sourceName  = nullptr;
  int         solveNo     = 0;
};

///////////////////////////////////////////////////////////

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveRoutineInitialize(Solve *solvePtr)
{
  solveNo     = solvePtr->GetSolveNo();
  routineName = this->GetSolveRoutineName(solveNo);   // PM routine
  sourceName  = this->GetSourceName(routineName);     // Source file name
  this->OpenSource(sourceName, LINKLEVEL_SOLVE);      // PM routine
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveRoutineTerminate(Solve *solvePtr)
{
  this->CloseSource();            // PM routine

  // coroutine generation
  this->GenerateCoSolveElemGenerator(solvePtr);  // MT (ElemGeneratorTemplate呼び)
                                                 // Written in MT_*****

  this->GenerateCoSolveRoutinesLIB(solvePtr);    // dependent on LIB
  this->GenerateCoSolveRoutines(solvePtr);       // dependent on PM
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveRoutineHeader(Solve *solvePtr)
{
  // Language dependent, main part is in LIB class
  this->DoSolveRoutineHeaderInLIB(routineName, solvePtr);

  // this->DoArgumentSequenceFromMain(routineName, solvePtr->VariablePtrLst()); // PM (if used)
  // this->DoSolveStarters();                                                  // PM (if used)
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveParameters(Solve *solvePtr)
{
  this->DoSolveParametersPM(solvePtr);  // PM
  this->SolverLibraryParameters();     // LIB
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveVariableDefinitions(Solve *solvePtr)
{
  // Auto variables
  this->DoSolveVariableDefinitionsPM(solvePtr); // Matrix independent variable parts
  this->DoSolveVariableDefinitionsMT();         // Matrix dependent variable parts

  // Library dependent variables
  this->SolverLibraryVariableDefinition();      // LIB
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveInitializer(Solve *solvePtr)
{
  this->DoSolveInitialDefPM(solvePtr);   // data statements nenfre, etc.

  this->DoSolveInitializerMT(solvePtr);
  this->DoSolveInitializerPM(solvePtr);
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveDegreeOfFreedom(Solve *solvePtr)
{
  this->DoSolveDegreeOfFreedom(solvePtr);
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveAssemblyPreparation(Solve *solvePtr)
{
  this->DoSolveAssemblyPreparation(solvePtr);
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveBoundaryDataPreparation(Solve *solvePtr)
{
  this->DoSolveBoundaryDataPreparation(solvePtr);
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveMatrixAllocate(Solve *solvePtr)
{
  this->DoSolveMatrixAllocate(solvePtr);
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveCallAssembleRoutine(Solve *solvePtr)
{
  this->DoSolveCallAssembleRoutine(solvePtr);                   // MT
  this->DoSolveReport(solvePtr->GetSolveNo(), "Assemble routine");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveNeumannConditions(Solve *solvePtr)
{
  this->DoSolveCallLinearNeumannData(solvePtr);                 // MT
  this->DoSolveReport(solvePtr->GetSolveNo(), "Neumann routine");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveDirichletConditions(Solve *solvePtr)
{
  this->DoSolveCallLinearDirichletData(solvePtr);
  this->DoSolveReport(solvePtr->GetSolveNo(), "Dirichlet routine");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolvePostProcess(Solve *solvePtr)
{
  this->DoSolveReport(solvePtr->GetSolveNo(), "Solver routine");
  this->DoSolveCallEdevRoutine(solvePtr);
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveTerminateSequence(Solve *)
{
  // do nothing
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveReturnSequence(Solve *solvePtr)
{
  this->DoSolveFreeMemoryMT();          // MT dependent free memory
  this->doSolveFreeMemoryPM(solvePtr);  // PM dependent free memory
  this->DoSolveReturnSequence(solvePtr);
}

///////////////////////////////////////////////////////////////////
// default virtual hooks (safe stubs)

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolveCallSolverRoutine(Solve *)
{
  dbgGeneratorReport(
      "SolveGeneratorTemplate::SolveCallSolverRoutine",
      "virtual function in SolveGeneratorTemplate.hpp called");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::GenerateCoSolveRoutinesLIB(Solve *)
{
  dbgGeneratorReport(
      "SolveGeneratorTemplate::GenerateCoSolveRoutinesLIB",
      "virtual function in SolveGeneratorTemplate.hpp called");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolverLibraryParameters()
{
  dbgGeneratorReport(
      "SolveGeneratorTemplate::SolverLibraryParameters",
      "virtual function in SolveGeneratorTemplate.hpp called");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::SolverLibraryVariableDefinition()
{
  dbgGeneratorReport(
      "SolveGeneratorTemplate::SolverLibraryVariableDefinition",
      "virtual function in SolveGeneratorTemplate.hpp called");
}

template <class MatMODEL>
inline void SolveGeneratorTemplate<MatMODEL>::DoSolveRoutineHeaderInLIB(const char *, Solve *)
{
  dbgGeneratorReport(
      "SolveGeneratorTemplate<MatMODEL>::DoSolveRoutineHeaderInLIB",
      "virtual function in SolveGeneratorTemplate.hpp called");
}

#endif // FEM_CLASS_SOLVEGENERATORTEMPLATE
