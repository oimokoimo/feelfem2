/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_feelP2.hpp
 *  Date     : 1999/11/15
 *  Modified : 1999/11/15
 *  
 *  Purpose  : Program model for feel P2
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

#ifndef FEM_PM_FEELP2
#define FEM_PM_FEELP2


#include "orderedPtrList.hpp"
#include "Source.hpp"
#include "Fortran77Generator.hpp"

#include "Solve.hpp"
#include "Variable.hpp"

#include "ElemGeneratorVirtuals.hpp"

#include "PM_External_Class.hpp"

class PM_feelP2 : public ElemGeneratorVirtuals, 
		  public Source, 
		  public Fortran77Generator   {

public:

  PM_feelP2();
  ~PM_feelP2();
  // File pointer management   [ it must be situated here! ]
  void OpenSource( const char *);
  void OpenSource( const char *, int);
  void CloseSource( void );

  // General comment functions
  void commentPM(void);

  // General Name managing functions
  void NameVariableInCalled( Variable *, string &);
  void pushVariableListInCalled( orderedPtrList <Variable *> );
  void pushVariableListInCalled( list       <Variable *> );

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



  /////////////////////////////////////////////////////
  // General Function Implementation in Called routine
  /////////////////////////////////////////////////////
  void DoArgumentSequenceFromMain(char *, orderedPtrList <Variable *> &);
  void DoDeclareVariablesFromMainPM( orderedPtrList <Variable *> );   

  void ArgumentVariableDeclarationLst(orderedPtrList <Variable *>&);
  void ArgumentVariableDeclaration(Variable *);
  void PopReturn();

  // SolveGeneratorTemplate related routines
  void GenerateCoSolveRoutines( Solve *);  // Co-generator for solve routine

  const char *GetSolveRoutineName ( int );
  void  pushSolveRoutineName( int );
  void  pushElemRoutineName ( int , int );
  void  pushNeumannRoutineName(int ,int );
  void  pushDirichletRoutineName(int ,int );
  void  pushEdevRoutineName(int , int); // in case of distributed, here


  ////////////////////////////
  // Solve related routines //
  ////////////////////////////
#include "DO_solve_PM.hpp"


  ///////////////////////////
  // Elem related routines //
  ///////////////////////////
#include "DO_elem_PM.hpp"


  ////////////////////////////////
  // Dirichlet related routines //
  ////////////////////////////////
  char *GetDirichletRoutineName( int , int  );

#include "DO_dirichlet_PM.hpp"


  //////////////////////////////
  // Neumann related routines //
  //////////////////////////////  
  char *GetNeumannRoutineName( int , int );

#include "DO_neumann_PM.hpp"


private:
  int usageCounter;

};


#endif






