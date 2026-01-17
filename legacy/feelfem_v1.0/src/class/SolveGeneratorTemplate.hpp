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
 *  
 */

#ifndef FEM_CLASS_SOLVEGENERATORTEMPLATE
#define FEM_CLASS_SOLVEGENERATORTEMPLATE

#include "feelfuncs.hpp"
#include "SolveScheme.hpp"

// if possible, it should be template

template <class MatMODEL> class SolveGeneratorTemplate
  : public MatMODEL, public SolveScheme {
public:
  SolveGeneratorTemplate() {;}            // do nothing NOW!!!!!!!!!!!!!!!!!!!!
  ~SolveGeneratorTemplate(){;}

  //Several Initializers
  void SetSolveNo2SolveGeneratorTemplate( int no ){
    solveNo     = no;
    routineName = GetSolveRoutineName( no );

    return;
  }

  void SolveRoutineInitialize   (Solve *);
  void SolveRoutineTerminate    (Solve *);

  void SolveRoutineHeader       (Solve *);   // Language dependent
  
  void SolveParameters          (Solve *);

  void SolveVariableDefinitions (Solve *);  

  void SolveInitializer         (Solve *);
  
  void SolveDegreeOfFreedom     (Solve *);

  void SolveAssemblyPreparation  (Solve *);

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
  virtual void DoSolveRoutineHeaderInLIB( char *,Solve *);
  
  // Library dependent functions (SolveVariableDefinitions)
  virtual void SolverLibraryParameters();
  virtual void SolverLibraryVariableDefinition();

  // Library dependent functions (SolveCallSolvers)
  virtual void SolveCallSolverRoutine   (Solve *);
  virtual void GenerateCoSolveRoutinesLIB(Solve *);  


private:
  char *routineName;
  char *sourceName;
  int   solveNo;
  
};

///////////////////////////////////////////////////////////
template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveRoutineInitialize(Solve *solvePtr)
{
  solveNo = solvePtr->GetSolveNo();
  routineName = GetSolveRoutineName( solveNo );   // PM routine
  sourceName  = GetSourceName(routineName);  // Source file name
  OpenSource(sourceName,LINKLEVEL_SOLVE);  // PM routine

  return;
}


template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveRoutineTerminate(Solve *solvePtr)
{
  CloseSource();            // PM routine
/*
  ElemGeneratorTemplate<MatMODEL> *ptrEG =
    new ElemGeneratorTemplate<MatMODEL>();
    ptrEG->DistributedAssembly(solve,solve.GetIthSolveElementPtr(0)); //P2 limi
    */


  // coroutine generation
  GenerateCoSolveElemGenerator( solvePtr );   // MT  call ElemGeneratorTemplate
                                              // Written in MT_*****
  //  GenerateCoSolveMathRoutineGenerator(solvePtr);
  //  cerr << "SolveGenaratorTemplate::SolveRoutineTerminate(){\n" <<
  //    "                         GenerateCoSolveMathRoutineGenerator(); \n"
  //  << endl;


  GenerateCoSolveRoutinesLIB(solvePtr);       // dependent on LIB
  GenerateCoSolveRoutines(solvePtr);          // dependent on PM, 

  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveRoutineHeader(Solve *solvePtr)
{ 

  // Language dependent
  // Main part is in LIB class

  DoSolveRoutineHeaderInLIB(routineName, solvePtr );

  //
  //  DoArgumentSequenceFromMain( routineName, solve.VariablePtrLst() ); //PM
  //  DoSolveStarters();                                                 //PM


  return;
}
  
template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveParameters          (Solve *solvePtr)
{ 
  
  DoSolveParametersPM( solvePtr );           //PM
  SolverLibraryParameters();              //LIB

  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveVariableDefinitions (Solve *solvePtr)
{ 
  // Auto variables

  DoSolveVariableDefinitionsPM(solvePtr); //Matrix independent variable parts)
  DoSolveVariableDefinitionsMT();        //Matrix dependent variable parts)

  // Library dependent variables
  SolverLibraryVariableDefinition();  //LIB
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveInitializer         (Solve *solvePtr)
{ 
  DoSolveInitialDefPM ( solvePtr );  // data statements nenfre, etc.

  DoSolveInitializerMT( solvePtr );
  DoSolveInitializerPM( solvePtr );
  return;
}  

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveDegreeOfFreedom     (Solve *solvePtr)
{ 
  DoSolveDegreeOfFreedom(solvePtr);
  return;
}  

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveAssemblyPreparation (Solve *solvePtr)
{ 
  DoSolveAssemblyPreparation(solvePtr);
  return;
}  

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveBoundaryDataPreparation( Solve *solvePtr)
{
  DoSolveBoundaryDataPreparation( solvePtr );
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveMatrixAllocate      (Solve *solvePtr)
{ 
  DoSolveMatrixAllocate (solvePtr);
  return;
}
template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveCallAssembleRoutine (Solve *solvePtr)
{ 
  DoSolveCallAssembleRoutine (solvePtr);                    //MT
  DoSolveReport(solvePtr->GetSolveNo(),"Assemble routine");
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveNeumannConditions   (Solve *solvePtr)
{ 
  DoSolveCallLinearNeumannData( solvePtr );                 // MT
  DoSolveReport(solvePtr->GetSolveNo(),"Neumann routine");
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveDirichletConditions (Solve *solvePtr)
{ 
  DoSolveCallLinearDirichletData( solvePtr );
  DoSolveReport(solvePtr->GetSolveNo(),"Dirichlet routine");
  return;
}  

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolvePostProcess         (Solve *solvePtr)   // edev routine
{ 
  DoSolveReport(solvePtr->GetSolveNo(),"Solver routine");
  DoSolveCallEdevRoutine(solvePtr);
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveTerminateSequence   (Solve *solvePtr)
{ 
  //  cout << "SolveTerminateSequence\n";
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveReturnSequence   (Solve *solvePtr)
{ 
  DoSolveFreeMemoryMT();              // MT dependent free memory
  doSolveFreeMemoryPM(solvePtr);      // PM dependent free memory
  DoSolveReturnSequence(solvePtr);
  return;
}
  

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolveCallSolverRoutine (Solve *solvePtr)
{
  dbgGeneratorReport("SolveGeneratorTemplate::SolveCallSolverRoutine",
  	             "virtual function in SolveGeneratorTemplate.hpp called");
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
GenerateCoSolveRoutinesLIB(Solve *)
{
  dbgGeneratorReport("SolveGeneratorTemplate::GenerateCoSolveRoutinesLIB",
  	             "virtual function in SolveGeneratorTemplate.hpp called");
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolverLibraryParameters()
{
  dbgGeneratorReport("SolveGeneratorTemplate::DoSolveParametersLIB",
  	             "virtual function in SolveGeneratorTemplate.hpp called");
  return;
}

template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
SolverLibraryVariableDefinition()
{
  dbgGeneratorReport("SolveGeneratorTemplate::DoSolveParametersLIB",
  	             "virtual function in solverLibraryVariableDefinition.hpp called");
  return;
}



template <class MatMODEL> void SolveGeneratorTemplate<MatMODEL>::
DoSolveRoutineHeaderInLIB(char *oimo,Solve *solvePtr)
{
  dbgGeneratorReport("SolveGeneratorTemplate<MatMODEL>::DoSolveRoutineInLIB()",
  	             "virtual function in SolveGeneratorTemplate.hpp called");
  return;
}

#endif
