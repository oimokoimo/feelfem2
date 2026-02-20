/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveNeumann.hpp
 *  Date     : 2001/07/24
 *  Modified : 
 *  
 *  Purpose  : Solve Neumann condition
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

#ifndef FEM_SYNTAX_SOLVENEUMANN
#define FEM_SYNTAX_SOLVENEUMANN

#include <iostream>

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "../../class/Expression.hpp"

class Neumann;

class SNsolveNeumannPairs : public SNunit {
public:
  SNsolveNeumannPairs( const char *name, Expression *ePtr)
    : SNunit("solveNeumannPairs",SN_SOLVENEUMANNPAIRS) {

    numberOfPairs = 1; // initialize

    string arg = name; // allocate memory
    neumannArgumentLst.addlast( arg );
    neumannExpressionLst.addlast( ePtr );

    return;
  }

  void addPair( const char *name, Expression *ePtr)
  {
    numberOfPairs++;

    string arg = name; // allocate memory
    neumannArgumentLst.addlast( arg );
    neumannExpressionLst.addlast( ePtr );

    return;
  }

  void print(std::ostream &ost);
  int  getNumberOfPairs(void) { return numberOfPairs; }
  void AddNeumannDataPairs( Neumann * );

  friend class SNsolveNeumann;


private:
  int  numberOfPairs;
  list <string>      neumannArgumentLst;
  list <Expression *>neumannExpressionLst;
    
};


class SNsolveNeumann : public SNunit {
public:

  // with default quadrature method
  SNsolveNeumann( SNsolveNeumannPairs *snpPtr, SNunit *sPtr)
    : SNunit("solveNeumann",SN_SOLVENEUMANN) {

    numberOfPairs = snpPtr->getNumberOfPairs();
    nPairsPtr    = snpPtr;
    nBoundaryLst = (SNidentifierlist *)sPtr;

    neumannPtr   = 0;

    return;
  }

  void print(std::ostream &ost);

  // CHECK  list neumannVarLst made here
  int VariableDefinedCheck_NeumannData(void);
  int IsTemporaryVariable( string &);

  void AddTVarStrToList( list <string>&);  // list up neumann temp variable
  int  CheckAllNTVarsAreUsed( list <string>&);

  // geometry check
  int GeometryCheck(void);

  // InfoGenerate
  void AddVariablePtr_Neumann(Neumann * );
  int  GeometryCreate();

  void AddNeumannDataPairs( Neumann * );


private:
  int                  numberOfPairs;
  SNsolveNeumannPairs *nPairsPtr;
  SNidentifierlist    *nBoundaryLst;

  Neumann             *neumannPtr;
};

#endif
