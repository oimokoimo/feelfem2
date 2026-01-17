/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementMatrices.hpp
 *  Date     : 2001/08/16
 *  Modified : 
 *  
 *  Purpose  : Store the element stiffness matrix and 
 *             element load vector mathematical components
 */

#ifndef FEM_CLASS_ELEMENTMATRICES
#define FEM_CLASS_ELEMENTMATRICES

#include "vector.hpp"
#include "exprString.hpp"

class ElementMatrices {

public:
  ElementMatrices();
  ~ElementMatrices();

private:

  int n,m;    // n for row, m for column
  
  vector <exprString> *KMvPtr;
  vector <exprString> *ELvPtr;

};

#endif
