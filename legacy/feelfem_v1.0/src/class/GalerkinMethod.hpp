/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GalerkinMethod.hpp
 *  Date     : 2002/01/30
 *  Modified : 
 *  
 *  Purpose  : Galerkin Formulation
 *             Create at SolveElement_discretize.cpp  
 *             SolveElement::ApplyGalerkinMethod(void)
 */

#ifndef FEM_CLASS_GALERKINMETHOD
#define FEM_CLASS_GALERKINMETHOD

#include "list.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class DiscretizedComponent;
class Variable;
class Element;
class IntegrandSet;
class TermConvert;

class GalerkinMethod {
public:
  
  GalerkinMethod();
  ~GalerkinMethod();

  void SetNumberOfUnknowns( int n);
  void SetIntegrandSetPtr(IntegrandSet *);

  void AddUnknownVariablePtr( Variable *);
  void AddTestfuncStr( string );

  void SetParametricElementPtr(Element *);

  DiscretizedComponent *Discretize(void);
  
private:
  // inner functions for discretization procedure
  void AddUniqElementPtr( Element * );

  void CalculateTotalDOF(void);
  void Make_ElementInfo(void);
  void Make_VariableInfo(void);

  void Make_TermConvert(void);            // use  Var,Elem work
  void VarPtr_ElementPtr_TC_init(void);   // init Var,Elem work

  void ApplyGalerkin(DiscretizedComponent *);
  void GalerkinTestFunction(DiscretizedComponent *,string ,string ,
			    Element *,int freedomAdd,  int *coeffSblNoVec);

  int unknowns;
  int totalDOF;    // set at MakeElementInfo
  int equations;

  list <Variable *>unknownVarPtrLst;
  list <string>testfuncStrLst;    // test function symbols


  IntegrandSet *weakIntegrandPtr; // this is not allocated here.
  // data for IntegrandSet
  int              variables;     // these are set in Make_Variableinfo
  int             *elementNo;     // corresponding No. (1 to elements)
  int             *degOfFreedom;  // copy of element freedom
  int             *startingSblNo; // starting symbol number
  int             *varType;       // copy of Variable * ->GetType()
  int             *ewiseType;     // ...  case of EWISE variables

  //list <string>elementTypeLst; //element name list used in the discretization


  // information data for discretization
  int             elements;
  list <Element *>elementPtrLst;
  int            *elementDOF;            // corresponding freedom

  Element *parametricElemPtr;            // passed to DiscretizedComponent ecal

  TermConvert    *tcPtr;

};

#endif
