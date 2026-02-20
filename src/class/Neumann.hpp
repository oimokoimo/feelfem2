/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Neumann.hpp
 *  Date     : 1999/11/24
 *  Modified : 2002/04/01
 *  
 *  Purpose  : Neumann Condition class
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

#ifndef FEM_CLASS_NEUMANN
#define FEM_CLASS_NEUMANN

#include "string.hpp"
#include "orderedList.hpp"
#include "orderedPtrList.hpp"
#include "Variable.hpp"

class Expression;
class NeumannGeom;
class BoundaryIntegrandSet;
class DiscretizedComponent;
class EcalInfo;
class EsetInfo;
class BoundaryElementNodePattern;
class ostream;
class StrStrPair;

class Neumann {
public:
  Neumann();
  ~Neumann();

  void operator=(const Neumann &);

  void AddNeumannGeomPtr(NeumannGeom *); //used SNsolveNeumann_InfoGenerate.cpp
  int  GetNumberOfNeumannGeoms(void);
  NeumannGeom *GetIthNeumannGeomPtr(int);

  // Get series
  int  GetSpaceDimension(void) { return spaceDim;}

  int  GetSolveNo(void) { return solveNo; }
  int  GetNcondNo(void) { return ncondNo; }
  int  GetNbedtno(void);

  int  GetNodes(void) { return nodes; }
  int  GetNDF(void) { return NDF; }
  int  GetNPG(void) { return NPG; }
  int  GetMatNonZero(void) { return matNonZero; }

  // Eset,Ecal
  EsetInfo*GetEsetInfoPtr() { return esetInfoPtr; }
  EcalInfo *GetEcalInfoPtr() { return ecalInfoPtr; }

  orderedList<string> &GetEcalIntegrandTermLst() {
    return(ecalIntegrandTermLst);
  }

  // BoundaryElementNodePattern, Node pattern
  BoundaryElementNodePattern *GetBoundaryElementNodePatternPtr() {
    return nBENPPtr;
  }
  
  int *GetNodePatternForEcal(Element *);  // allocated memory must be freed
  int *GetNodePatternForEcal(Variable *);  // allocated memory must be freed
  

  // Parametric element
  Element    *GetParametricElementPtr(void) { return parametricElementPtr; }

  // Quadrature
  Quadrature *GetQuadraturePtr() { return qPtr; }

  // DiscretizedComponent
  DiscretizedComponent *GetDiscretizedComponentPtr(void) { return dcPtr; }


  // set series
  void SetSolveNo(int);
  void SetNcondNo(int);
  void SetNbedtno(int);

  void SetSpaceDim(int);

  //SNsolveNeumannPairs_InfoGenerate.cpp
  void AddNeumannDataSSPairPtr( StrStrPair *);  // for cnd, 
                                          

  // boundary integrand
  void SetBoundaryIntegrandSetPtr(BoundaryIntegrandSet *);
  void AddUnknownVariablePtr( Variable * );
  void AddTestfuncStr( string &);
  void SetParametricElement( string & );
  
  // Discretization, called from discretizeSolve.cpp
  void ApplyGalerkinMethod(void);
  void GenerateEcalInfo(void);
  void GenerateEsetInfo(void);

  // Information generate after discretization
  void discretizeInfoGenerate(void);            // in Neumann_InfoGenerate.cpp
  void MakeBoundaryElementNodePattern(void);    // called from discretizeInfoG

  // Use series
  void UseX();            // finally, set in Neumann_discretize.cpp
  void UseY();
  void UseZ();
  
  void UseNX();
  void UseNY();
  void UseNZ();

  int IsUseX();
  int IsUseY();
  int IsUseZ();

  int IsUseNX();
  int IsUseNY();
  int IsUseNZ();

  // used in GiD_CND.cpp
  list <StrStrPair *>  &GetNeumannPairDataPtrLst(void) {
    return neumannPairDataPtrLst;
  }

  int GetFirstNeumannGeomNo_DOTMP(void);

  /////////////////////////////////////////////////////////////

  // test routines
  void testSetNbedtno( int );
  void testSetSolveNo( int no) { solveNo = no; return; }
  void testSetNcondNo( int no) { ncondNo = no; return; }

  void testSetNDF(int n) { NDF = n; return; }
  void testSetNPG(int n) { NPG = n; return; }


  void AddVariablePtr( Variable *);
  orderedPtrList <Variable *> &GetVariablePtrLst(void) {
    return(varPtrLst);
  }

  void AddQuadratureArrayLst( char *);  
  list <char *>GetQuadratureArrayLst(void) 
    {return(testQuadratureArrayLst); }

  void AddIENPLst(int);                  // add to list
  void AddIEDPLst(int);
  list <int>GetIENPLst(void) { return testIENPLst;}
  list <int>GetIEDPLst(void) { return testIEDPLst;}


  void testSetGaussPoints(int);
  void AddGXArrayLst( char *);
  void AddWArrayLst( char *);
  list   <char *> GetGXArrayLst(void) { return (testGXArrayLst); }
  list   <char *> GetWArrayLst (void) { return (testWArrayLst); }

  void testSetSValue( char *);
  char *GetSValue(void) {return testSValue; }

  void AddTermsLeftLst(char *);
  void AddTermsRightLst(char *);
  list   <char *> GetTermsLeftLst (void) { return(testTermsLeftLst ); }
  list   <char *> GetTermsRightLst(void) { return(testTermsRightLst); }

  void testSetBoundaryPoints(int);
  int GetBoundaryPoints(void) {return testBoundaryPoints; }
  
  void AddFemVarsFormulaLeftLst( char *);
  void AddFemVarsFormulaRightLst( char *);
  list <char *>GetFemVarsFormulaLeftLst(void) 
    { return testFemVarsFormulaLeftLst; }
  list <char *>GetFemVarsFormulaRightLst(void) 
    { return testFemVarsFormulaRightLst; }


  void testSetDxFormula( char *);
  char *GetDxFormula(void) { return testDxFormula; }
  
  void testSetDyFormula( char *);
  char *GetDyFormula(void) { return testDyFormula; }

  void testSetQxFlag( int );
  int GetQxFlag(void) { return testQxFlag; }

  //  void testSetQyFlag( int );
  //  int GetQyFlag(void) { return testQyFlag; }

  //  void testSetQxFormula( char *);
  //  char *GetQxFormula(void) { return testQxFormula; }

  //  void testSetQyFormula( char *);
  //  char *GetQyFormula(void) { return testQyFormula; }

  //  void testSetBaFlag( int );
  //  int  GetBaFlag(void) { return testExprBAFlag; }

  void AddBaFormulaLst(int ,int , char *);
  list   <int   >GetBaILst(void) {return  testBaILst; }
  list   <int   >GetBaJLst(void) {return  testBaJLst; }
  list   <char *>GetBaFormulaLst(void) { return testBaFormulaLst; }
  

  void testSetBbFreedom( int );
  int GetBbFreedom(void) { return testBbFreedom; }

  void AddBbFormulaLst( char *);
  list <char *>GetBbFormulaLst(void) { return testBbFormulaLst; }


  void check()
    {
	    std::cout << "CHECK NEUMANN NPG="<<NPG<<"\n";
      return;
    }

  void print(std::ostream &);

private:

  int         solveNo;
  int         ncondNo;
  int         nbedtNo;              // node set number for this neumann data

  int         spaceDim;

  int         nodes;                // set in Neumann_InfoGenerate.cpp
  int         NPG;                  // set in Neumann_InfoGenerate.cpp
  int         NDF;

  // System Variables (set at Expression_Infogenerate.cpp )
  int         qxFlag;               // x is used   
  int         qyFlag;               // y is used
  int         qzFlag;               // z is used

  int         normalFlag;           // normal components are used
  int         nxFlag;
  int         nyFlag;
  int         nzFlag;

  int         tangentialFlag;       // tangential components are used

  // boundary geometry
  list <NeumannGeom *> neumannGeomPtrLst;
  int                  nGeoms;

  // boundary Discretization
  int           unknowns;       // number of equations
  list <string> testfuncSymbolLst;                  //SNs_I_N.cpp(copy of SE)
  list <Variable *>unknownVarPtrLst;                //SNs_I_N.cpp(copy of SE)

  orderedPtrList <Variable *> varPtrLst;

  // ielem 
  Element            *parametricElementPtr;   // coordinate transformation

  BoundaryIntegrandSet *bIntegrandSetPtr;     // for boundary integrand 
  list <StrStrPair *>  neumannPairDataPtrLst; // neumann arg + data expression 

  DiscretizedComponent *dcPtr;
  int                   matNonZero;           // number of non zero in matrix

  EcalInfo *ecalInfoPtr;
  EsetInfo *esetInfoPtr;
  orderedList <string>    ecalIntegrandTermLst;

  BoundaryElementNodePattern *nBENPPtr;

  Quadrature         *qPtr;



  ////////////////////////////////////////////////////////////////
  // test (P2 engine interface)
  list   <char *> testQuadratureArrayLst;
  list   <int   > testIENPLst;
  list   <int   > testIEDPLst;

  int             testGaussPoints;  // same as NPG, not use
  list   <char *> testGXArrayLst;
  list   <char *> testWArrayLst;
  
  char *          testSValue;
  list   <char *> testTermsLeftLst;
  list   <char *> testTermsRightLst;

  int             testBoundaryPoints;

  list   <char *> testFemVarsFormulaLeftLst;
  list   <char *> testFemVarsFormulaRightLst;

  char *          testDxFormula;
  char *          testDyFormula;

  int             testQxFlag;
  int             testQyFlag;
  
  char           *testQxFormula;
  char           *testQyFormula;

  int             testExprBAFlag;
  list   <int   > testBaILst;
  list   <int   > testBaJLst;
  list   <char *> testBaFormulaLst;

  int             testBbFreedom;
  list   <char *> testBbFormulaLst;

};

#endif
