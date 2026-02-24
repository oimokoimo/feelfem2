/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_feelfem90vec.hpp
 *  Date     : 2000/11/29  (Copy PM_feelfem90.hpp)
 *  Modified : 
 *  
 *  Purpose  : Program model for feelfem90/Vector processing
 *  
 *             This is a code generator class for ielem,matno handling, etc.
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

#ifndef FEM_PM_FEELFEM90VEC
#define FEM_PM_FEELFEM90VEC


#include "orderedPtrList.hpp"
#include "Source.hpp"
#include "Fortran90Generator.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

#include "ElemGeneratorVirtuals.hpp"

#include "PM_External_Class.hpp"

class PM_feelfem90vec : public Source, 
			public Fortran90Generator,
			public ElemGeneratorVirtuals
{

public:

  PM_feelfem90vec();
  ~PM_feelfem90vec();
  // File pointer management   [ it must be situated here! ]
  void OpenSource( const char *);      // File pointer is set in this routines
  void OpenSource( const char *,int);  // File pointer is set in this routines
  void CloseSource( void );

  // General comment functions
  void commentPM(void);

  // General Name managing functions
  void pushCoordinateSource(void);           // push x,y,z

  // List push
  void NameVariableInCalled    ( Variable *, string &);
  void pushVariableInCalled    ( Variable * );                  // one variable
  void pushVariableListInCalled( orderedPtrList <Variable *> );     // orderedPtrList
  void pushVariableListInCalled( list  <Variable *> );          // list version
  void pushVariableListInSolve ( orderedPtrList <Variable *> );


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
  void F90useDirichletPM(void); // for dirichlet routine
  void F90useNeumannPM(void);   // for neumann routine

  // General Function Implementation in this memory model
  void MODULEzeroclearD(const char *,const char *);
  void MODULEzeroclearI(const char *,const char *);
  void MODULEmalloc    (const char *,const char *,const char *,const char *);
  void MODULEmallocERT (const char *,const char *,const char *,const char *);
  void MODULEmallocCHK ();
  void MODULEmallocF90 (const char *,const char *);

  // General Function Implementation in Main routine
  // void MakeCalledArugumentList( char *, orderedPtrList <Variable *> &);
  // void MakeCallArgumentList   ( orderedPtrList <Variable *> &);


  const char *GetSourceName(const char *);
  const char *GetMainSourceName(void);  


  // Temporary generator for main routine
  void GenerateMainTmp(Solve *);   // one solve sentence is assumed



  /////////////////////////////////////////////////////
  // General Function Implementation in Called routine
  /////////////////////////////////////////////////////
  void DoArgumentSequenceFromMain(const char *, orderedPtrList <Variable *> &);
  void DoDeclareVariablesFromMainPM( orderedPtrList <Variable *> );

  void ArgumentVariableDeclarationLst(list <Variable *>&);
  void ArgumentVariableDeclaration(Variable *);
  void CoordinateVariableDeclaration(void);

  void PopReturn();

  // Main Scheme
  void DoMainScheme_solve(Main *,Solve *);

  ////////////////////////////////////////////
  // MainGeneratorTemplate related routines //
  ////////////////////////////////////////////

#include "DO_main_PM.hpp"

  /////////////////////////////////////////////
  // SolveGeneratorTemplate related routines //
  /////////////////////////////////////////////

  void GenerateCoSolveRoutines ( Solve *);  // Co-generator for solve routine
  void GenerateCoSolveEdevRoutine( Solve *);  // edev routine generator

  const char *GetSolveRoutineName ( int );
  void  pushSolveRoutineName( int );
  void  pushElemRoutineName ( int );    // P2 difference  only one elem routine
  void  pushNeumannRoutineName(int ,int );
  void  pushDirichletRoutineName(int ,int );
  void  pushEdevRoutineName(int , int); // in case of distributed, here

  // Parallel additional procedures
  void MPIinclude(void);

#include "DO_solve_PM.hpp"


  ///////////////////////////
  // Elem related routines //
  ///////////////////////////
  const char *GetElemRoutineName( int );
  const char *GetElemRoutineName( int solveNo, int elemNo ) 
    {return(GetElemRoutineName(solveNo)); }   //P2 limit


  
  string SuperRinjiEcalP2DRAMA(const char *);

  // for vector processing algorithm

  void  DoElemQuadratureLoopStart(SolveElement *, int);  // int is quadNo
  void  DoElemQuadratureLoopEnd(SolveElement *, int);
  void  DoElemQuadLoopPreparation(SolveElement *,int);
  void  DoElemQuadLoopMakeAllElement(SolveElement *,int);


  // normal ElemGenerator
  void  doElemStarters();
  void  DoElemDeclareArgumentVariablesPM(SolveElement *); // from RoutineHeader
  void  DoElemParameters(SolveElement *);
  void  DoElemVariableDefinitionsPM(SolveElement *);
  void  DoElemInitializer(SolveElement *);
  //  void  DoElemElementLoopStart(int);
  //  void  DoElemCallEcalRoutine(SolveElement *,int);
  //  void  DoElemElementLoopEnd(int);
  void  DoElemReturnSequence(SolveElement *);

  //#include "DO_elem_PM.hpp"


  ////////////////////////////////
  // Dirichlet related routines //
  ////////////////////////////////
  const char *GetDirichletRoutineName( int , int  );

  const char *dirichletP2DOTEMP( const char *);  /* change '(ip)' -> '_dpt' */

#include "DO_dirichlet_PM.hpp"
 


  //////////////////////////////
  // Neumann related routines //
  //////////////////////////////  
  const char *GetNeumannRoutineName( int , int );

  void pushSuperDotempneumannFEMval(const char *, const char *);

#include "DO_neumann_PM.hpp"
  

private:
  int usageCounter;

};

#endif
