/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Solve.hpp
 *  Date     : 1999/10/26
 *  Modified : 2002/02/01
 *  
 *  Purpose  : Solve class
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

#ifndef FEM_SOLVE_CLASS
#define FEM_SOLVE_CLASS

#include <iostream>

#include "orderedPtrList.hpp"
#include "SolveElement.hpp"
#include "Variable.hpp"

class Dirichlet;
class Neumann; 

class Solve {

public:
  Solve()   ;  // Constructor
  ~Solve()  ;  // Destructor


  // InfoGenerate family
  void MakeVariablePtrLst(void); // Make solveVariablePtrLst  from SE,D,N
  void MakeNodeInformation(void);


  int  GetProgramModelType();  // for ecal
  int  GetLibraryType();       // for elem,solve

  int  GetSolveNo(void);
  int  GetSolveElements(void);
  int  GetMaxnodes(void);
  int  GetSpaceDim(void);

  int  GetNonlinearFlag() { return nonlinearFlag; }



  SolveElement *GetIthSolveElementPtr( int );

  Neumann      *GetIthNeumannDataPtr( int );
  int  GetNconds(void);
  int  GetIthNeumannNbedtno(int);
  orderedPtrList <Variable *>GetIthNeumannVariablePtrLst(int);

  Dirichlet  *GetIthDirichletDataPtr( int );
  int  GetDconds(void); 
  int  GetIthDirichletNsetno(int);
  orderedPtrList <Variable *>GetIthDirichletVariablePtrLst(int);

  void AddSolveElementPtr ( SolveElement *);
  void AddDirichletDataPtr( Dirichlet    *);
  void AddNeumannDataPtr  ( Neumann      *);
  
  // Set functions
  void SetLibraryType( int no ) {
    libraryType = no;
    return;
  }
  void SetProgramModelType( int no ) {
    programModelType = no;
    return;
  }

  void SetSpaceDim( int n);

  // debug
  void print(std::ostream &);

  // test functions  
  void testSetLibraryType(int);
  void testSetSolveNo( int );
  void testSetMaxnodes( int );
  void testSetNonlinearFlag(int);
  void testSetUnknowns(int);
  //  void testSetUnknownVariablePtr(Variable *);

  orderedPtrList <Variable *> &VariablePtrLst(void) { 
    return solveVariablePtrLst;}


private:
  void AddVariablePtr     ( Variable     *);
  int  makeVariablePtrLstComeyetFlag;

  static int solves;     // total solve statements
  int        solveNo;    // this solve number

  int  maxnodes;         // max nodes 

  int  programModelType; // for ecal generation, etc. (02-02-20)
  int  matrixType;       // not use
  int  libraryType;      // LibraryType (Solver)  from Configure.hpp

  int  spaceDim;         // space dimension

  //  list       <Variable *>     solveUnknownVariablePtrLst;
  // Now made by the set of SolveElement *,Dirichlet *, Neumann .
  orderedPtrList <Variable *>     solveVariablePtrLst;

  int    solveElements; // Number of element groups
  list  <SolveElement *> solveSolveElementPtrLst;

  int    dirichletConditions;
  list  <Dirichlet *>    solveDirichletPtrLst;

  int    neumannConditions;
  list  <Neumann   *>    solveNeumannPtrLst;

  int    nonlinearFlag;
  int    unknowns;

};

#endif


