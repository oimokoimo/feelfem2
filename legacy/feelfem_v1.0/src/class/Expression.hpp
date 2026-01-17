/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Expression.hpp
 *  Date     : 2001/02/15
 *  Modified : 
 *  
 *  Purpose  : expressions
 *  
 */

#ifndef FEM_CLASS_EXPRESSION
#define FEM_CLASS_EXPRESSION

#include <stdio.h>
#include "string.hpp"
#include "list.hpp"

#include "../parser/Syntax/SNunit.hpp"
#include "orderedPtrList.hpp"

class SolveElement;
class SNsolveNeumann;
class Dirichlet;
class Neumann;
class Assign;

class IntegrandSet;
class BoundaryIntegrandSet;
class Quadrature;


class Expression {

public:
  Expression(SNunit *  );    // constructor 
  ~Expression();   

  // this is called in constructor
  friend void exprAnalysis(Expression *, SNunit *);

  void LineNumber(int n) {
    lineNumber = n;
    return;
  }

  void print(ostream & );

  // used in evaluation
  int howManyNotDefinedVariable(int flag, void *ptr1,void *ptr2)
  {
    if(snExprPtr == NULL) {
      cerr << "try to howManyNotDefinedVariable NULL EXPR\n";
      return(-1);
    }
    return(snExprPtr->howManyNotDefinedVariable(flag,ptr1,ptr2));
  }

  int howManyNotDefinedFunction(int flag, void *ptr1,void *ptr2)
  {
    if(snExprPtr == NULL) {
      cerr << "try to howManyNotDefinedFunction NULL EXPR\n";
      return(-1);
    }
    return(snExprPtr->howManyNotDefinedFunction(flag,ptr1,ptr2));
  }

  int howManyNotAssignedVariable(int flag, void *ptr1,void *ptr2)
  {
    if(snExprPtr == NULL) {
      cerr << "try to howManyNotAssignedVariable NULL EXPR\n";
      return(-1);
    }
    return(snExprPtr->howManyNotAssignedVariable(flag,ptr1,ptr2));
  }

  int howManyIdentifiers(void) { return identifiers; }
  int howManyNotIntrinsicFunctions(void);

  // check function family
  int checkDefinedVariableSN(SNunit *);
  int checkDefinedFunctionSN(SNunit *);

  int checkDefinedFEMObjectSN(SNunit * );

  int checkDefinedVariable_RegionalSN(SNunit * ,list<string> &);
  int checkDefinedVariable_BoundarySN(SNunit *,list<string>&,SNsolveNeumann *,
				      list <string>&);
  int EtypeConsistencyCheckSN(SNunit *snuPtr, int refEtype,list<string> &);
  int EtypeConsistencyCheckSN(SNunit *snuPtr, int refEtype,list<string> &,
			      list <string> &);  // for boundary integrand
  int checkDefinedVariable_DirichletSN(SNunit *,list<string> &unknown);
  int checkDefinedVariable_NeumannDataSN(SNunit *,list<string>&nVarLst);

  int checkQuadratureConsistency_RegionalSN(SNunit *, list<string>&,
					    Quadrature *);


  // assign valid expression check
  int checkNoFemSN(SNunit *snPtr);
  int checkNoCoordinateSN(SNunit *snPtr);
  int checkNoEwiseSN(SNunit *snPtr);
  int checkNoMaterialSN(SNunit *snPtr);
  int checkNoNormalSN(SNunit *snPtr);

  int checkNoDifferentialFuncSN(SNunit *snPtr);


  // Infogenerate family
  void MakeVariablePtr(orderedPtrList <Variable*> &);  // with uniq
  void AddVariablePtr_Regional(SolveElement *,list<string> &);
  void AddVariablePtr_Boundary(Neumann *,list<string> &,list <string>&);
  void AddVariablePtr_Dirichlet(Dirichlet * );
  void AddVariablePtr_Neumann(Neumann *);

  void CheckXYZNXNYNZ_Neumann(Neumann *);  // SNsolveNeumannPairs_InfoGenerate
  void CheckXYZNXNYNZ_Assign(Assign *);    // SNassignment_InfoGenerate.cpp

  // for user function
  void MakeUserFuncLst( list <string> &);  // store used user function list

  // for Ewise-assign
  int HasDifferential1st(void);
  int HasDifferential2nd(void);    // not implemented now, 020722

  // WEAKEQ family
  void MakeIntegrandSetInfo( IntegrandSet * , list <string>&);
  void MakeIntegrandSetInfoBoundary( BoundaryIntegrandSet * , list <string>&);



  void exprPrint(char *buf,int flag, void *ptr1,void *ptr2)
  {
    if(snExprPtr == NULL) {
      *buf = '\0';
      cerr << "try to exprPrint NULL EXPR\n";
      return;
    }
    snExprPtr->exprPrint(buf,flag,ptr1,ptr2);
  }

private:

  SNunit *snExprPtr;
  int     eval_flag;
  double  evalValue;             // evaluated value

  int identifiers;
  list <string> identifierLst;

  int functions;
  list <string> functionLst;

  int andOperators;
  int orOperators;
  int xorOperators;
  
  int equalOperators;
  int nequalOperators;
  int gtOperators;
  int geOperators;
  int ltOperators;
  int leOperators;

  int plusOperators;
  int subOperators;
  int mulOperators;
  int divOperators;
  int minusOperators;

  int intNumbers;
  int doubleNumbers;

  int brackets;

  int lineNumber;

};  

class ExprCell{

public:
  ExprCell();
  ~ExprCell();
  

private:
  int       cellType;        // ATOM, ARRAY, or....
  int       symbol;
  char     *val;
  ExprCell *car;
  ExprCell *cdr;
  
};


class Expr {

public:
  Expr();
  ~Expr();

  void print();
  void fprint(FILE *);     
  

private:
  int identifiers;
  char *exprInf;     // 
  char *expr;

};

#endif
