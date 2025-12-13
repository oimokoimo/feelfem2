/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_feelfem90DRAMA.hpp
 *  Date     : 2000/10/16
 *  Modified : 2000/10/16
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Program model for feelfem90/Drama Double index(parallel)
 *  
 *             This is a code generator class for ielem,matno handling, etc.
 *  
 *  
 */

#ifndef FEM_PM_FEELFEM90DRAMA
#define FEM_PM_FEELFEM90DRAMA

#include <stdio.h>

#include "orderedPtrList.hpp"
#include "Source.hpp"
#include "Fortran90Generator.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

#include "ElemGeneratorVirtuals.hpp"

#include "TermConvert.hpp"

#include "PM_External_Class.hpp"

class PM_feelfem90DRAMA : public Source, 
			  public Fortran90Generator,
			  public ElemGeneratorVirtuals
{

public:

  PM_feelfem90DRAMA();
  ~PM_feelfem90DRAMA();
  // File pointer management   [ it must be situated here! ]
  void OpenSource( char *);      // File pointer is set in this routines
  void OpenSource( char *,int);  // File pointer is set in this routines
  void CloseSource( void );

  // General comment functions
  void commentPM(void);


  // for F90 related routines
#include "PM_F90.hpp"

  // General Name managing functions
#include "PM_basic.hpp"


  // for external variables, exclusive for feelfem90DRAMA
  void pushCoordinateExternalSource(void);   // push x_ex,y_ex,z_ex
  void pushFEMExternalVariableListInCalled( orderedPtrList <Variable *> );
  void pushVariableAndFEMExternalListInCalled( orderedPtrList <Variable *> );  // used elem, etc.
  void pushVariableAndFEMExternalListInSolve( orderedPtrList <Variable *> );  // used elem, etc.

  // externals in solve
  void pushFEMVariableExternalInCalled(Variable *);  // f90 same as below
  void pushFEMVariableExternalInSolve (Variable *);  // f90 same as upper

  // General generator
  void DefaultParameterBlock();
  void SourceStarters();



  // General Function Implementation in this memory model
  void MODULEzeroclearD(char *,char *);
  void MODULEzeroclearI(char *,char *);
  void MODULEmalloc    (char *,char *,char *,char *);
  void MODULEmallocERT (char *,char *,char *,char *);
  void MODULEmallocCHK ();
  void MODULEmallocF90 (char *,char *);

  // General Function Implementation in Main routine
  // void MakeCalledArugumentList( char *, orderedPtrList <Variable *> &);
  // void MakeCallArgumentList   ( orderedPtrList <Variable *> &);


  char *GetSourceName(char *);
  char *GetMainSourceName(void);  


  // Temporary generator for main routine
  void GenerateMainTmp(Solve *);   // one solve sentence is assumed



  /////////////////////////////////////////////////////
  // General Function Implementation in Called routine
  /////////////////////////////////////////////////////
  void DoArgumentSequenceFromMain(char *, orderedPtrList <Variable *> &);
  void DoDeclareVariablesFromMainPM( orderedPtrList <Variable *> );

  void ArgumentVariableDeclarationLst(list <Variable *>&);
  void ArgumentVariableDeclaration(Variable *);

  void MainVariableDeclaration(Variable *);

  void CoordinateVariableDeclaration(void);
  void CoordinateExternalVariableDeclaration(void);
  void FEMExternalVariableDeclaration(Variable *);
  void FEMExternalVariableDeclarationLst(list <Variable *>&);
  

  void PopReturn();

  // Main Scheme
  void DoMainScheme_solve(Main *,Solve *);

  // MainGeneratorTemplate related routines

#include "DO_main_PM.hpp"

// main coroutines
void GenerateMaterialVarInitializeRoutine(void);


  /////////////////////////////////////////////
  // SolveGeneratorTemplate related routines //
  /////////////////////////////////////////////
  void GenerateCoSolveRoutines ( Solve *);  // Co-generator for solve routine
  void GenerateCoSolveEdevRoutine( Solve *);  // edev routine generator
  void GenerateCoSolveExtDataRoutine( Solve *); // mksolve#extdata.f90

  char *GetSolveRoutineName ( int );
  void  pushSolveRoutineName( int );
  void  pushElemRoutineName ( int );    // P2 difference  only one elem routine
  void  pushNeumannRoutineName(int ,int );
  void  pushDirichletRoutineName(int ,int );
  void  pushEdevRoutineName(int , int); // in case of distributed, here


  // Parallel additional procedures
  void MPIinclude(void);
  void SubDoSolveMakeExtData(Solve *);                // f90 version


#include "DO_solve_PM.hpp"


  ///////////////////////////
  // Elem related routines //
  ///////////////////////////


#include "DO_elem_PM.hpp"

  ///////////////////////////
  // Ecal related routines //
  ///////////////////////////
  string SuperRinjiEcalP2DRAMA(const char *);

#include "DO_ecal_PM.hpp"

  ///////////////////////////
  // Eset related routines //
  ///////////////////////////
#include "DO_eset_PM.hpp"

  ////////////////////////////////
  // Dirichlet related routines //
  ////////////////////////////////
  char *GetDirichletRoutineName( int , int  );
  //  char *dirichletP2DOTEMP( char *);  /* change '(ip)' -> '_dpt' */

#include "DO_dirichlet_PM.hpp"
  //  void  DoDirichletArgumentVariableDefinitionsPM(Dirichlet *);
  //  void  doDirichletAutoVariableDefinitionsPM(Dirichlet *);
  //  void  DoDirichletReturnSequencePM(Dirichlet *);

  // called from Matrix data dependent Diriclet routine
  //  void  doSetDirichletValue(Dirichlet *);
  

  //////////////////////////////
  // Neumann related routines //
  //////////////////////////////  
  char *GetNeumannRoutineName( int , int );
  // void pushSuperDotempneumannFEMval(char *, char *);
  void pushSuperDotempDRAMAneumannFEMval(char *, char *);

#include "DO_neumann_PM.hpp"

  // Scheme routines
#include "DO_assign_PM.hpp"
#include "DO_output_PM.hpp"
  //#include "DO_write_PM.hpp"
  

private:
  int usageCounter;

};

#endif
