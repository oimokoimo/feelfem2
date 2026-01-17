/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : VariableEvalPair.hpp
 *  Date     : 2002/09/10
 *  Modified : 
 *  
 *  Purpose  : Variable eval pair for EwiseQuad assignment
 *  
 */

#ifndef FEM_CLASS_VARIABLEEVALPAIR
#define FEM_CLASS_VARIABLEEVALPAIR

#include "Variable.hpp"
class Element;

class VariableEvalPair {
public:
  VariableEvalPair(Variable *, int diffType);
  ~VariableEvalPair();

  Element  *GetElementPtr();
  Variable *GetVariablePtr();

  int       GetVarType() { return(variablePtr->GetType()); }
  int       GetDiffType() { return diffType; }
  int       IsElementType() { return isElement; }

private:
  int diffType;          // Differentiation type
  int isElement;
                     // TYPE_DIFF_ZERO,TYPE_DIFF_X,Y,Z
  Variable *variablePtr;
  Element  *elementPtr;
};

#endif
