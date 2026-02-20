/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveWeq.hpp
 *  Date     : 2001/07/20
 *  Modified : 2002/04/18 (BCN)
 *  
 *  Purpose  : Solve weq component
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

#ifndef FEM_SYNTAX_SOLVEWEQ
#define FEM_SYNTAX_SOLVEWEQ

#include "SNunit.hpp"
#include "SNweqTerms.hpp"

#include "list.hpp"
#include "string.hpp"

class SolveElement;
class SNsolveNeumann;
class Neumann;
class IntegrandSet;
class BoundaryIntegrandSet;
class Quadrature;

class SNsolveWeq : public SNunit {
public:

  // with default quadrature method
  SNsolveWeq( SNweqTerms *lPtr, SNweqTerms *rPtr)
    : SNunit("solveWeq",SN_SOLVEWEQ) {

    leftHandSideWeqTermsPtr  = lPtr;
    rightHandSideWeqTermsPtr = rPtr;

  }

  // CHECK functions

  // returns number of undef vars
  int VariableDefinedCheck_Regional( list <string> &);  
  int VariableDefinedCheck_Boundary( list <string> & , SNsolveNeumann *,
				     list <string> &);  

  // returns number of unmatch etype objects
  int EtypeConsistencyCheck( int refEtype,list <string> & ,list <string> &);

  int QuadratureConsistencyCheck( int refEtype ,list<string>&,Quadrature *);

  int HasBoundaryTerm(void);   // return 1 if yes (=YES)

  // Weakform (Regional)
  void WriteRegionWeakEqStrByQuad(string &,char *,int &,int);
  void MakeRegionIntegrandSetInfoByQuad(string &,IntegrandSet *,list<string>&);

  // Weakform (Boundary)
  void WriteBoundaryWeakEqStr(char *,int &,int);
  void MakeBoundaryIntegrandSetInfo(BoundaryIntegrandSet *,list<string>&);

  // making SolveElement
  void AddVariablePtr_Regional( SolveElement *,list <string> &);
  void ListUpQuadrature_Regional( list <string> &);

  // making NeumannData
  void AddVariablePtr_Boundary( Neumann *,list <string> &,list <string>&);


  void print(std::ostream &ost) {

    leftHandSideWeqTermsPtr->print(ost);
    ost << "=";
    rightHandSideWeqTermsPtr->print(ost);    

    return;
  }


private:
  SNweqTerms *leftHandSideWeqTermsPtr;
  SNweqTerms *rightHandSideWeqTermsPtr;

};

#endif

