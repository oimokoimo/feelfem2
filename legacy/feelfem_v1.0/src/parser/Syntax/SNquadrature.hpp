/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNquadrature.hpp
 *  Date     : 2001/03/27
 *  Modified : 
 *  
 *  Purpose  : quadrature class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_QUADRATURE
#define FEM_SYNTAX_QUADRATURE

#include "stack.hpp"         // use stack (list)
#include "string.hpp"
#include "Quadrature.hpp"

#include "SNunit.hpp"
class SNquadratureGaussP;

class SNquadrature : public SNunit {
public:
  SNquadrature( char *nm, char *elem, stack <SNunit *> &) ;


  // for check function
  int isAlreadyUsedName( list <string> &strLst) {
    if(strLst.includes(name)) {
      return(YES);
    }
    else {
      strLst.addlast(name);
      return(NO);
    }
  }

  // used in quadrature_check
  int SetGaussPoints(void); // Set gaussPoints if no error
  int SetEtype(void);       // Set etype code from 'string elementShape'


  // for error message
  void errWrtName(ostream &ost ) {
    ost << name;
    return;
  }

  void print(ostream & ) ;

  // Check functions
  int CheckGaussPDimension(void); // check every GaussP has proper dimension
  int EvalExpressions(void);      // Evaluation (a part of check procedure)  
  int CheckGaussPRange(void);     // check Gauss point range
  int CheckConsistency(void);     // check integration is consistent

  // Make Quadrature class
  int InfoGenerate(void);        // called from check/quadrature_create.cpp

  // Debug XDisplay
  void dbgXDisplay(void) {
    if(quadPtr) {
      quadPtr->dbgXDisplay();
    }
    else {
      cerr << "SNquadrature::dbgXDisplay for " << name 
	   << " Quadrature pointer has not been assigned.\n";
    }
  }

private:

  string name;
  string elementShape;
  int    etype;             // quadrature_check, SetEtype()
  int    dimension;

  int    doubles;
  int    assignments;

  int    gaussPoints;       // quadrature_check, SetGaussPoints()

  list <SNunit *>dblAndAssignPtrLst;
  list <SNquadratureGaussP *>gaussPPtrLst;

  Quadrature *quadPtr;
  
};

#endif
