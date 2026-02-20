/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNweqTerm.hpp
 *  Date     : 2001/07/16
 *  Modified : 
 *  
 *  Purpose  : Weak formulation 
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

#ifndef FEM_SYNTAX_WEQTERM
#define FEM_SYNTAX_WEQTERM

#include "SNunit.hpp"

#include "list.hpp"
#include "string.hpp"
#include "Expression.hpp"

class SolveElement;
class SNsolveNeumann;
class Neumann;
class IntegrandSet;
class Quadrature;

class SNweqTerm : public SNunit {
public:

  // with default quadrature method
  SNweqTerm( int iType, Expression *ptr )    
    : SNunit("weqTerm",SN_WEQTERM) {

    integralType   = iType;
    quadratureType = TYPE_QUADRATURE_DEFAULT;

    integrandExprPtr = ptr;

    return;
  }

  SNweqTerm( int iType,  char *qMethod, Expression *ptr) 
    : SNunit("weqTerm",SN_WEQTERM) {

    integralType     = iType;    // regional or boundary

    quadratureType   = TYPE_QUADRATURE_SPECIFIED;
    quadratureMethod = qMethod;

    integrandExprPtr = ptr;
  }

  void print(std::ostream &ost) {

    if(integralType == TYPE_REGIONAL_INTEGRAND) {
      ost << "int";
    }
    else {
      ost << "bint";
    }
    
    if(quadratureType == TYPE_QUADRATURE_SPECIFIED) {
      ost <<"[" << quadratureMethod<<"]";
    }

    ost << "(";
    integrandExprPtr->print(ost);
    ost << ")";

    return;
  }

  //CHECK functions
  int IsBoundaryTerm(void);   // if boundary term, return YES

  int VariableDefinedCheck_Regional(list <string> &);
  int VariableDefinedCheck_Boundary(list <string> &,SNsolveNeumann *,
				    list <string> &);

  int EtypeConsistencyCheck( int refEtype, list <string> &,list <string>&);
  int QuadratureConsistencyCheck( int refEtype,list <string> &,Quadrature *);

  //Weakform (Region part)
  void WriteRegionWeqEqStrByQuad( int,string&,char *,int &,int);
  void MakeRegionIntegrandSetInfoByQuad(string &,IntegrandSet *,list<string>&);

  //Weakform (Boundary part)
  void WriteBoundaryWeqEqStr( int,char *,int &,int);
  void MakeBoundaryIntegrandSetInfo(BoundaryIntegrandSet *,list<string>&);
  
  //SolveElement
  void AddVariablePtr_Regional(SolveElement *,list <string>&);
  void ListUpQuadrature_Regional( list <string>& );

  //Neumann
  void AddVariablePtr_Boundary(Neumann *,list <string>&,list <string>&);


private:
  int         integralType;     // Regional integral or Boundary integral
                                // TYPE_REGIONAL_INTEGRAND or
                                // TYPE_BOUNDARY_INTEGRAND

  int         quadratureType;   // TYPE_QUADRATURE_DEFAULT
                                // TYPE_QUADRATURE_SPECIFIED
  string      quadratureMethod; // Numerical quadrature, if specified.

  Expression *integrandExprPtr; // integrand expression

};

#endif
