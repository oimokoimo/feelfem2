/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_aistpcp90.hpp
 *  Date     : 2002/06/28
 *  
 *  Purpose  : Program model for aistpcp90 (Made from feelfem90)
 *  
 *             This is a code generator class for ielem,matno handling, etc.
 *  
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#ifndef FEM_PM_AISTPCP90
#define FEM_PM_AISTPCP90


#include "orderedPtrList.hpp"
#include "Source.hpp"
#include "Fortran90Generator.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

#include "Write.hpp"

#include "ElemGeneratorVirtuals.hpp"

#include "TermConvert.hpp"

#include "PM_External_Class.hpp"

class PM_aistpcp90 : public Source, 
		     public Fortran90Generator,
		     public ElemGeneratorVirtuals
{

public:

  PM_aistpcp90();
  ~PM_aistpcp90();
  // File pointer management   [ it must be situated here! ]
  void OpenSource( char *);      // File pointer is set in this routines
  void OpenSource( char *,int);  // File pointer is set in this routines
  void CloseSource( void );

  // General comment functions
  void commentPM(void);

  // General Name managing functions

  void pushInteger4sc(void);     // integer                                 ::
  void pushInteger4pm(void);     // integer,parameter                       ::
  void pushInteger4Ptr1(void);   // integer,dimension(:),pointer            ::
  void pushInteger4Ptr2(void);   // integer,dimension(:,:),pointer          ::
  void pushInteger4In(void);     // integer,intent(in)                      ::
  void pushTypeDefCC(char *);    // STRING            ....                  ::
  void pushLogical(void);        // locical                                 ::

  void writeInteger4sc(const char *);    // integer                        
  void writeInteger4pm(const char *);    // integer,parameter              
  void writeInteger4Ptr1(const char *);  // integer,dimension(:),pointer   
  void writeInteger4Ptr2(const char *);  // integer,dimension(:,:),pointer 
  void writeInteger4In(const char *);    // integer,intent(in)             
  void writeLogical(const char *);

  void pushReal8sc(void);        // real(kind=REAL8)                        ::
  void pushReal8pm(void);        // real(kind=REAL8)                        ::
  void pushReal8Ptr1(void);      // real(kind=REAL8),dimension(:),pointer   ::
  void pushReal8Ptr2(void);      // real(kind=REAL8),dimension(:,:),pointer ::
  void pushReal8Array1(void);    // real(kind=REAL8),dimension(:)           ::

  void writeReal8sc(const char *);   // real(kind=REAL8)                   
  void writeReal8pm(const char *);   // real(kind=REAL8)                   
  void writeReal8Ptr1(const char *); // real(kind=REAL8),dimension(:),pointer
  void writeReal8Ptr2(const char *); // real(kind=REAL8),dimension(:,:),pointer


  void pushCoordinateSource(void);           // push x,y,z

  // Variable name push series
  void NameVariableInCalled    (Variable *, string &);
  void pushVariableInCalled    (Variable * );                  // one variable
  void pushVariableListInCalled(orderedPtrList<Variable *>); // orderedPtrList
  void pushVariableListInCalled(list  <Variable *> );         // list version
  void pushVariableListInCalledOnlyFEM(list  <Variable *> );  // Only FEM var
  void pushVariableListInSolve (orderedPtrList<Variable *>);

  void pushVariableNameInMain  (Variable *);
  void pushVariableListInMain  (orderedPtrList<Variable *>);

  // ecal related push (2002-02-20)
  void pushEcalArgumentLstInElem( SolveElement *,orderedPtrList <Variable *> );
  void pushEcalArgumentLstInEcal( SolveElement *,orderedPtrList <Variable *> );
  void EcalVarDeclarationInEcal( SolveElement *,orderedPtrList <Variable *> );

  // variable allocation
  void MainVariableAllocation( Variable *);


  // Individual push
  void pushFEMVariableInCalled        (Variable *);
  void pushFEMVariableInSolve         (Variable *);

  // General generator
  void DefaultParameterBlock();
  void SourceStarters();

  // for F90 use statements
  void F90useAlways(void);
  void F90useFEMDataType(void);

  void F90useMainPM(void);      // for main routine
  void F90useSolvePM(Solve *);  // for solve routine
  void F90useElemPM(SolveElement *);
  void F90useDirichletPM(void); // for dirichlet routine
  void F90useNeumannPM(void);   // for neumann routine

  // General Function Implementation in this memory model
  void MODULEzeroclearD(char *,char *);
  void MODULEzeroclearI(char *,char *);
  void MODULEmalloc    (char *,char *,char *,char *);
  void MODULEmallocERT (char *,char *,char *,char *);
  void MODULEmallocCHK ();
  void MODULEmallocF90 (char *,char *);

  void MemAllocate(const char *name,const char *arg, const char *arg_size,
		   int type);
  void MemDeallocate(const char *name,const char *arg, const char *arg_size,
		     int type);

  // General Function Implementation in Main routine
  // void MakeCalledArugumentList( char *, orderedPtrList <Variable *> &);
  // void MakeCallArgumentList   ( orderedPtrList <Variable *> &);


  char *GetSourceName(const char *);
  char *GetMainSourceName(void);  

  /////////////////////////////////////////////////////


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

  void PopReturn();


// Main SchemeGenerator
void DoMainScheme_solve(Main *,Solve *);


  // MainGeneratorTemplate related routines
#include "DO_main_PM.hpp"

// main coroutines (ProgramModel oriented)
  void GenerateMaterialVarInitializeRoutine(void);
  void GenerateMakefileForUserFunction(void);


  // SolveGeneratorTemplate related routines
  void GenerateCoSolveRoutines ( Solve *);  // Co-generator for solve routine
  void GenerateCoSolveEdevRoutine( Solve *);  // edev routine generator
  void GenerateCoSolveIpdinfoRoutine( Solve *);  // ipdinfo routine generator


  char *GetSolveRoutineName ( int );
  void  pushSolveRoutineName( int );
  void  pushElemRoutineName ( int );    // P2 difference  only one elem routine
  void  pushNeumannRoutineName(int ,int );
  void  pushDirichletRoutineName(int ,int );
  void  pushEdevRoutineName(int , int);    // in case of distributed, here
  void  pushIpdinfoRoutineName(int , int); // in case of distributed, here


#include "DO_solve_PM.hpp"


  // Parallel additional procedures
  void MPIinclude(void);



  ///////////////////////////
  // Elem related routines //
  ///////////////////////////
  char *GetElemRoutineName( int );
  char *GetElemRoutineName( int solveNo, int elemNo ) 
    {return(GetElemRoutineName(solveNo)); }   //P2 limit

  void  doElemStarters();
  void  doElemDeclareArgumentVariablesPM(SolveElement *); // from RoutineHeader
  void  DoElemParameters(SolveElement *);
  void  DoElemVariableDefinitionsPM(SolveElement *);
  void  DoElemInitializer(SolveElement *);
  void  DoElemElementLoopStart(int);
  void  DoElemCallEcalRoutine(SolveElement *,int);
  void  DoElemElementLoopEnd(int);
  void  DoElemReturnSequence(SolveElement *);


  ///////////////////////////
  // Ecal related routines //
  ///////////////////////////
  string SuperRinjiEcalP2DRAMA(const char *);

  char *GetEcalRoutineName( int solveNo, int elemNo );
  void pushEcalRoutineName( SolveElement *);
  void EcalArgumentVariableDeclarationLst(SolveElement *,
					  orderedPtrList<Variable *>&);

  void EcalElementMatRHSVariableDeclaration(int solveNo,int elemNo);
  void EcalElementMatRHSCommon(int solveNo, int elemNo );  // NDF is assumed

  void EcalQuadArgumentVariableDeclaration(SolveElement *,
					   DiscretizedComponent *,
					   int solveNo,int elemNo, int quadNo);
  void EcalQuadCommon(SolveElement *,
		      DiscretizedComponent *dcPtr,
		      int solveNo,int elemNo,int quadNo);

  void DoEcalRoutineHeader( SolveElement *);
  void doEcalArgumentSequence(SolveElement *);
  void doEcalDeclareArgumentVariables( SolveElement *);
  void pushEcalJacobiSub(int quadNo,int freedom,int *ndPattern,
			 const char *,const char *,const char *);
  void pushEcalCoordSub(int quadNo,Element *,SolveElement *,const char *coord);
  void pushEcalDiffSub_1st(int quadNo,Element *ePtr,int dim,int no,int diff);

  //  void doEcalVariableDefinition(SolveElement *);

  void DoEcalParameters(SolveElement *);
  void DoEcalVariableDefinitions(SolveElement *);

  void DoEcalElementMatInitialize(SolveElement *);

  void DoEcalQuadLoopStart(int quadNo, SolveElement *);
  void DoEcalCalcJacobian(int quadNo, SolveElement *);
  void DoEcalSetValAtGaussP(int quadNo, SolveElement *);
  void DoEcalCalcElementMatRHS(int quadNo, SolveElement *);

  void DoEcalQuadLoopEnd(int quadNo, SolveElement *);

  void DoEcalReturnSequence(SolveElement *);


  void GenerateCoSolveEcalRoutines(SolveElement *);
  void GenerateEsetRoutines(SolveElement *);
  void pushEsetRoutineName(int,int,int);

  void doEsetCalcInterpolation(SolveElement *,
			       DiscretizedComponent *dcPtr,
			       int solveNo,int elemNo,int quadNo);
  void doEsetCalcInterpolationSub(int quadNo,
				  SolveElement *,
				  Element *,
				  int type        );

  ////////////////////////////////
  // Dirichlet related routines //
  ////////////////////////////////

#include "DO_dirichlet_PM.hpp"
  char *GetDirichletRoutineName( int , int  );
  //  char *dirichletP2DOTEMP( char *);  /* change '(ip)' -> '_dpt' */

  //  void  DoDirichletArgumentVariableDefinitionsPM(Dirichlet *);
  //  void  doDirichletAutoVariableDefinitionsPM(Dirichlet *);
  //  void  DoDirichletReturnSequencePM(Dirichlet *);

  // called from Matrix data dependent Diriclet routine
  //

  //////////////////////////////
  // Neumann related routines //
  //////////////////////////////  
  char *GetNeumannRoutineName( int , int );
  void pushSuperDotempneumannFEMval(char *, char *);

#include "DO_neumann_PM.hpp"

  //////////////////////////////////  
  //  Assignment related routines //
  //////////////////////////////////
#include "DO_assign_PM.hpp"
#include "DO_output_PM.hpp"
#include "DO_write_PM.hpp"      // write


  // general scheme related routines
#include "DO_scheme_PM.hpp"   

private:
  int usageCounter;

};

#endif
