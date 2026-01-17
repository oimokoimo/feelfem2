/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment_CHECKvalidExpr.cpp
 *  Date     : 2002/07/15
 *  Modified : 
 *  
 *  Purpose  : check valid expr
 *  
 */

#include "SNassignment.hpp"
#include "../../check/check_funcs.hpp"

int SNassignment::checkValidExpr_FEM(void)
{
  //  No EWISE valiable here
  //  No VFEM  valiable here???

  int ret=0;
  ret += exprPtr->checkNoEwiseSN(this);    // no ewise variable
  ret += exprPtr->checkNoMaterialSN(this); // no material variable
  ret += exprPtr->checkNoNormalSN(this);   // no normal component

  ret += exprPtr->checkNoDifferentialFuncSN(this);

  return(ret);
}

int SNassignment::checkValidExpr_EWISE(void)    // scalar at each element
{
  int ret = 0;
  
  ret += exprPtr->checkNoDifferentialFuncSN(this);
  ret += exprPtr->checkNoNormalSN(this);
  ret += exprPtr->checkNoFemSN(this);

  return(ret);
}

int SNassignment::checkValidExpr_EWISE_A(void)
{
  int ret = 0;

  return(ret);
}

int SNassignment::checkValidExpr_INTEGRAL(void)
{
  int ret   = 0;

  ret += exprPtr->checkNoNormalSN(this);  // no normal component

  int  etype = refEtypeIntegral;
  list <string>nothing;  // EtypeConsistencyCheckSN is originally for SNweqTerm
  ret += exprPtr->EtypeConsistencyCheckSN(this,etype,nothing,nothing);

  return(ret);
}
  

int SNassignment::checkValidExpr_DOUBLE(void)
{
  int ret = 0;
  
  ret += exprPtr->checkNoEwiseSN(this);   // no ewise variable
  ret += exprPtr->checkNoMaterialSN(this); // no material variable
  ret += exprPtr->checkNoNormalSN(this);  // no normal component  

  ret += exprPtr->checkNoDifferentialFuncSN(this);  // no differential
  
  if(placeFlag != SN_ASSIGNMENT_AT) {
    ret += exprPtr->checkNoFemSN(this);   // no fem variable here
    ret += exprPtr->checkNoCoordinateSN(this);
  }

  return(ret);
}

int SNassignment::checkValidExpr_INT(void)
{
  int ret = 0;
  
  ret += exprPtr->checkNoEwiseSN(this);   // no ewise variable
  ret += exprPtr->checkNoMaterialSN(this); // no material variable
  ret += exprPtr->checkNoNormalSN(this);  // no normal component

  ret += exprPtr->checkNoDifferentialFuncSN(this);  // no differential
  
  if(placeFlag != SN_ASSIGNMENT_AT) {
    ret += exprPtr->checkNoFemSN(this);   // no fem variable here
    ret += exprPtr->checkNoCoordinateSN(this);
  }

  return(ret);
}
