/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_feelP2DRAMA.hpp
 *  Date     : 2000/03/20
 *  Modified : 2000/03/20
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : Program model for feel P2/Drama Double index(parallel)
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

#ifndef FEM_PM_FEELP2DRAMA
#define FEM_PM_FEELP2DRAMA


#include "orderedPtrList.hpp"
#include "Source.hpp"
#include "Fortran77Generator.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

#include "ElemGeneratorVirtuals.hpp"

#include "PM_External_Class.hpp"

class PM_feelP2DRAMA : public Source, 
		       public Fortran77Generator,
		       public ElemGeneratorVirtuals 
{

public:

   PM_feelP2DRAMA();
  ~PM_feelP2DRAMA();
  // File pointer management   [ it must be situated here! ]
  void OpenSource( const char *);      // File pointer is set in this routines
  void OpenSource( const char *,int);  // File pointer is set in this routines
  void CloseSource( void );

  // General comment functions
  void commentPM(void);

  // General Name managing functions
  void NameVariableInCalled    ( Variable *, string &);
  void pushVariableListInCalled( orderedPtrList <Variable *> );
  void pushVariableListInCalled( list       <Variable *> );

  void pushVariableNameInMain  (Variable *);

  void pushFEMVariableInCalled(Variable *);
  void pushFEMVariableExternalInCalled( Variable *);
  void pushFEMVariableExternalInSolve(Variable *);

  // General generator
  void DefaultParameterBlock();
  void SourceStarters();

  // General Function Implementation in this memory model
  void MODULEzeroclearD(const char *,const char *);
  void MODULEzeroclearI(const char *,const char *);
  void MODULEmalloc    (const char *,const char *,const char *,const char *);
  void MODULEmallocERT (const char *,const char *,const char *,const char *);
  void MODULEmallocCHK ();

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
  void DoArgumentSequenceFromMain(char *, orderedPtrList <Variable *> &);
  void DoDeclareVariablesFromMainPM( orderedPtrList <Variable *> );

  void ArgumentVariableDeclarationLst(list <Variable *>&);
  void ArgumentVariableDeclaration(Variable *);

  void PopReturn();

  // Main Scheme
  void DoMainScheme_solve(Main *,Solve *);

  // MainGeneratorTemplate related routines
#include "DO_main_PM.hpp"

// main coroutines
void GenerateMaterialVarInitializeRoutine(void);


  // SolveGeneratorTemplate related routines
  void GenerateCoSolveRoutines ( Solve *);  // Co-generator for solve routine
  void GenerateCoSolveEdevRoutine( Solve *);  // edev routine generator
  void GenerateCoSolve_mksdbuf ( Solve *);  // co-co generator for mksdbuf
  void GenerateCoSolve_mkexnode( Solve *);  // co-co generator for mkexnode

  const char *GetSolveRoutineName ( int );
  void  pushSolveRoutineName( int );
  void  pushElemRoutineName ( int );    // P2 difference  only one elem routine
  void  pushNeumannRoutineName(int ,int );
  void  pushDirichletRoutineName(int ,int );
  void  pushEdevRoutineName(int , int); // in case of distributed, here

#include "DO_solve_PM.hpp"


  // Parallel additional procedures
  void MPIinclude(void);
  void SubDoSolveMessageKnownFEMVars( Solve *);
  void SubDoSolveMakeExIelem(void);
  void SubDoSolveMakeSumupDegree(void);
  void SubDoSolveMakeExNode(Solve *);


  ///////////////////////////
  // Elem related routines //
  ///////////////////////////

  string SuperRinjiEcalP2DRAMA(const char *);


#include "DO_elem_PM.hpp"


  ////////////////////////////////
  // Dirichlet related routines //
  ////////////////////////////////
  const char *GetDirichletRoutineName( int , int  );

  const char *dirichletP2DOTEMP( const char *);  /* change '(ip)' -> '_dpt' */

  void  DoDirichletArgumentVariableDefinitionsPM(Dirichlet *);
  void  doDirichletAutoVariableDefinitionsPM(Dirichlet *);
  void  DoDirichletReturnSequencePM(Dirichlet *);


  //////////////////////////////
  // Neumann related routines //
  //////////////////////////////  
  const char *GetNeumannRoutineName( int , int );

  void pushSuperDotempDRAMAneumannFEMval(const char *, const char *);

#include "DO_neumann_PM.hpp"
  

private:
  int usageCounter;

};

#endif
