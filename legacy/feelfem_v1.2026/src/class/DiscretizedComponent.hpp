/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DiscretizedComponent.hpp
 *  Date     : 2001/06/06
 *  Modified : 
 *  
 *  Purpose  : Discretized mathematical component
 *  
 */

#ifndef FEM_CLASS_DISCRETIZEDCOMPONENT
#define FEM_CLASS_DISCRETIZEDCOMPONENT

#include <iostream.h>

#include "list.hpp"
#include "Element.hpp"

#include "vector.hpp"
#include "matrix.hpp"
#include "string.hpp"

#define TERM_LENGTH  256

class TermConvert;
class EcalInfo;
class EsetInfo;

class Element;

class SolveElement;
class IntegrandSet;

class Neumann;
class BoundaryIntegrandSet;

class DiscretizedComponent {

public:
  DiscretizedComponent(int,int);
  ~DiscretizedComponent();

  // in SolveElement_discretize.cpp
  void SetNumbers(int solveNo,int elemNo,int quadNo);  

  // for Neumann_discretize.cpp
  void SetNumbers(int solveNo,int ncondNo);

  void SetCoefficient(int , int , const char *);
  void SetRHS(int , const char *);

  void print(ostream &ost);

  // for ecal family
  void SetIdentifierList( TermConvert *);   // converted identifier list
  void SetElementPtrList( TermConvert *);   // element ptr list 

  void SetParametricElementPtr( Element *); // set parametric element
  
  EcalInfo *GenerateEcalInfo( int , Element *,IntegrandSet *);
  EsetInfo *GenerateEsetInfo( SolveElement *,Element *);

  // for boundary integrand
  EcalInfo *GenerateBoundaryEcalInfo( int dim,
				      Element *parametricElementPtr,
				      BoundaryIntegrandSet *);
  EsetInfo *GenerateBoundaryEsetInfo( Neumann *,Element *);


  list <Element *> &GetUsedElementPtrList(void) {
    return elementPtrLst;
  }

  int  IsUsedIntegrandTerm(string &);

  // for ecal ea(i,j)=ea(i,j)+...
  int GetRows(void)    { return rows;}
  int GetColumns(void) { return columns;}
  int GetFreedom(void) { return rows;}

  char *GetElementMatIJ(int , int) ;  // starts 1
  char *GetElementLoadI(int );

  int GetMatrixNonZero(void) { return matrixNonZero; }
  int IsZeroMatCoeff(int n, int m);
  int IsZeroRHSVec(int n);

private:
  int regionalIntegrationFlag;        // component is for main weak form
  int boundaryIntegrationFlag;        // component is for Neumann type

  int solveNo;
  int solveElementNo;
  int quadNo;

  int ncondNo;

  int elementType;

  int rows,columns;
  matrix <string> *elementStiffMatPtr;
  matrix <int>    *sparseFlagMatPtr;     // 1 or 0
  int matrixNonZero;                    // number of nonzero entry in matrix
  vector <string> *rhsVecPtr;
  vector <int>    *nullFlagRHSVecPtr;

  list <string>    identifierLst;
  Element         *parametricElemPtr;
  list <Element *> elementPtrLst;

};

#endif
