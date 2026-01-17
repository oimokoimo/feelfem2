/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Variable_print.cpp
 *  Date     : 2002/02/01
 *  Modified : 
 *  
 *  Purpose  : check write
 *  
 */

#include <iostream.h>
#include <assert.h>
#include "Variable.hpp"

void Variable::print(ostream &ost)
{
  switch(varType) {
  case VAR_FEM:
    ost << "fem";
    break;

  case VAR_EWISE:
  case VAR_EWISE_A:
    ost << "ewise";
    break;

  case VAR_DOUBLE:
    ost << "double";
    break;

  case VAR_INT:
    ost << "int";
    break;

  case VAR_CONST:
    ost << "const";
    break;

  case VAR_VFEM:
    ost << "vfem";
    break;

  default:
    assert(1==0);
  }

  ost << " " << varName;
  
  switch(varType) {
  case VAR_FEM:
  case VAR_EWISE_A:

    ost << "[" << functionName << "]";
    break;


  default:
    break;
  }

  return;
}


