/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNmaterialVar_CHECK.cpp
 *  Date     : 2002/08/23
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include "SNfunctionDef.hpp"

#include "feelfuncs.hpp"
#include "Object.hpp"

#include "../../check/check_funcs.hpp"


int SNfunctionDef::Check(void)
{
  int errors = 0;

  if( isIntrinsicFunction(name) ) {
    SystemErrorStrA(this,name," is an intrinsic function name.");
    return(1);
  }
  
  if( isDifferentialOperator1( name ) ) {
    SystemErrorStrA(this,name," is a differential operator name.");
    return(1);
  }    

  return(0);
}
