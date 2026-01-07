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
 */

#ifndef FEM_SYNTAX_SOLVENEUMANN
#define FEM_SYNTAX_SOLVENEUMANN

#include <iostream.h>

#include "SNunit.hpp"
#include "SNidentifierlist.hpp"
#include "../../class/Expression.hpp"

class Neumann;

class SNsolveNeumannPairs : public SNunit {
public:
  SNsolveNeumannPairs( char *name, Expression *ePtr)
    : SNunit("solveNeumannPairs",SN_SOLVENEUMANNPAIRS) {

    numberOfPairs = 1; // initialize

    string arg = name; // allocate memory
    neumannArgumentLst.addlast( arg );
    neumannExpressionLst.addlast( ePtr );

    return;
  }

  void addPair( char *name, Expression *ePtr)
  {
    numberOfPairs++;

    string arg = name; // allocate memory
    neumannArgumentLst.addlast( arg );
    neumannExpressionLst.addlast( ePtr );

    return;
  }

  void print(ostream &ost);
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

  void print(ostream &ost);

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
