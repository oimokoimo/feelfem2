/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : BoundaryGalerkinMethod.hpp
 *  Date     : 2002/03/29 (Copy of GalerkinMethod.hpp)
 *  Modified : 
 *  
 *  Purpose  : Galerkin Formulation for Boundary Integration
 *             Create at Neumann_discretize.cpp  
 *             Neumann::ApplyBoundaryGalerkinMethod(void)
 */

#ifndef FEM_CLASS_BOUNDARYGALERKINMETHOD
#define FEM_CLASS_BOUNDARYGALERKINMETHOD

#include "list.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "matrix.hpp"

class DiscretizedComponent;
class Variable;
class Element;
class BoundaryIntegrandSet;
class TermConvert;

class BoundaryGalerkinMethod {
public:
  
  BoundaryGalerkinMethod();
  ~BoundaryGalerkinMethod();

  void SetNumberOfUnknowns( int n);
  void SetBoundaryIntegrandSetPtr(BoundaryIntegrandSet *);

  void AddUnknownVariablePtr( Variable *);
  void AddTestfuncStr( string );

  void SetParametricElementPtr(Element *);

  DiscretizedComponent *Discretize(void);

  // for normal component usage information from Neumann pointer
  void UseNX();
  void UseNY();
  void UseNZ();
  
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
			    Element *regionPtr,Element *boundaryPtr,
			    int freedomAdd,  int *coeffSblNoVec);

  int unknowns;
  int totalDOF;    // set at MakeElementInfo
  int equations;

  list <Variable *>unknownVarPtrLst;
  list <string>testfuncStrLst;    // test function symbols

  // for normal component usage flag
  int nxFlag,nyFlag,nzFlag;

  BoundaryIntegrandSet *weakIntegrandPtr; // this is not allocated here.
  // data for IntegrandSet
  int              variables;     // these are set in Make_Variableinfo
  int             *elementNo;     // corresponding No. (1 to elements)
  int             *degOfFreedom;  // copy of element freedom
  int             *startingSblNo; // starting symbol number
  int             *varType;       // copy of Variable * ->GetType()
  int             *ewiseType;     // ...  case of EWISE variables

  //list <string>elementTypeLst; //element name list used in the discretization


  // information data for discretization (be careful boundary and region)
  int             elements;
  list <Element *>elementPtrLst;         // THIS IS (REGION) element pointer
  int            *elementDOF;            // corresponding freedom (Boundary)

  Element *parametricElemPtr;            // passed to DiscretizedComponent ecal

  TermConvert    *tcPtr;

};

#endif
