 /*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolve.hpp
 *  Date     : 2001/03/05
 *  Modified : 
 *  
 *  Purpose  : solve class for parser  (reference aumc)
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

#ifndef FEM_SYNTAX_SOLVE
#define FEM_SYNTAX_SOLVE

#include "../../class/stack.hpp"         // use stack (list)
#include "../../class/string.hpp"

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "SNsolveWeq.hpp"
#include "SNsolveDirichlet.hpp"
#include "SNsolveNeumann.hpp"

class Solve;
class Main;
class Quadrature;
class IntegrandSet;
class BoundaryIntegrandSet;

class SNsolve : public SNunit {
public:
  SNsolve( SNidentifierlist *, SNidentifierlist *,stack <SNunit *> &) ;

  void print(std::ostream & ) ;

  // CHECK functions
  void errWrtNameNO(std::ostream &,int);  // int = 1 write Solver Name
  void checkInit(void);          // check initialize.  
                                 // set program model name in string
                                 // convert default string to real name
                                 // (solver, [quadrature,] , etc.

  int setNumberOfUnknowns(void); // this function checks matching of test 
                                 // function number  SNsolve_CHECK.cpp
  int isConsistentNumberOfEqs(void); // check number of weq eqs and unknowns

  int SolverNameCheck(void);     // return YES(=OK), NO(=NG)
  int PM_LIBmatchCheck(void);    // return YES(=OK), NO(=NG)

  int ParametricNameCheck(void); // return 1 if errors

  int CheckNdataExists(void);    // boundary integral needs neumann data

  int VariableDefinedCheck(void); // check all variable are defined or not

  // etype consistency check
  int EtypeConsistencyCheck(void);  // return number of errors

  int QuadratureConsistencyCheck(void); // return number of errors

  // geometry check(called from scheme_solve_geom_check.cpp)
  // it generates BGeom list (2002/03/21)

  // int RegionGeometryCheck();
  int BoundaryGeometryCheck();    // list up Boundary condition geometry obj.
  int BoundaryGeometryCreate();


  // Weakform (region part)
  IntegrandSet *GetIntegrandSetPtrByQuad_Region( string quadName ,
						 Quadrature *);

  // Weakform (boundary part)
  BoundaryIntegrandSet *GetBoundaryIntegrandSetPtr(void);

  // Solve class generator
  int InfoGenerate(void);        // Solve class generator

  // Code generator
  void CodeGenerate(void);                // Code generator
  void CodeGenerateMain(void *,Main *);   // code generator for main routine


  // Discretization
  //  void SNsolve::GalerkinMethod(void);  -> moved to SolveElement


  // Solve * ptr 
  Solve *GetSolvePtr(void) {
    return( solvePtr );
  }
  
private:
  
  // Infogenerate family
  void MakeSolveElement( Solve *,int solveNo, int solveElementNo);
  void MakeDirichletDataPtr( Solve *, int solveNo);
  void MakeNeumannDataPtr( Solve *,int solveNo);

  int numberOfSolveElements;
  int numberOfUnknowns;

  int refEtype;             // set in SNsolve_CHECK.cpp, EtypeConsistencyCheck
  
  SNidentifierlist *unknownIdentifierList;
  SNidentifierlist *testFunctionIdentifierList;

  int    nonlinearFlag;
  string nonlinearMethod;

  string quadratureMethod;
  string solverName;
  string parametricName;          // coordinate transformation element name
  string programModelNameCopy;    // in order to access as string...


  int weakEquations;
  list <SNsolveWeq *>weqLst;

  int dirichletConditions;
  list <SNsolveDirichlet *>dcondLst;

  int neumannConditions;
  list <SNsolveNeumann *>ncondLst;

  Solve *solvePtr;              // allocate in check routine

  // Generated information (while check, Infogenerate)
  int infoGeneratePossibleFlag;    // severe error surpress info generation
  int numberOfQuadratureMethods;

};

#endif
