/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNassignment.cpp
 *  Date     : 2001/08/23
 *  Modified : 
 *  
 *  Purpose  : Constructors
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
 *  
 */

#include <iostream>

#include "feeldef.hpp"
#include "SNassignment.hpp"

SNassignment::SNassignment(const char *nm, Expression *ptr) 
  :SNunit("assignment",SN_ASSIGNMENT) 
{ 
  leftVarName    = nm; 
  exprPtr        = ptr;
  condExprPtr    = 0;
  integralType   = ASSIGNMENT_TYPE_ORIGINAL;     // for integral,bintegral flag

  refEtypeIntegral  = 0;
  refEtypeBintegral = 0;


  placeFlag      = SN_ASSIGNMENT_NORMAL;

  placeLst       = 0;

  return;
}

SNassignment::SNassignment( const char *nm, Expression *ptr,int iType) 
  :SNunit("assignment",SN_ASSIGNMENT) 
{ 
  leftVarName    = nm; 
  exprPtr        = ptr;
  condExprPtr    = 0;

  integrationMethod = DEFAULT_STRING;
  integralType      = iType;
    
  refEtypeIntegral  = 0;
  refEtypeBintegral = 0;

  placeFlag      = SN_ASSIGNMENT_NORMAL;
  placeLst       = 0;

  return;
}

// with integration method
SNassignment::SNassignment(const char *nm,char *qd,Expression *ptr,int iTyp) 
  :SNunit("assignment",SN_ASSIGNMENT) 
{ 
    leftVarName    = nm; 
    exprPtr        = ptr;
    condExprPtr    = 0;

    integralType      = iTyp;
    integrationMethod = qd;

    refEtypeIntegral  = 0;
    refEtypeBintegral = 0;

    placeFlag      = SN_ASSIGNMENT_NORMAL;
    placeLst       = 0;

    return;
}

SNassignment::SNassignment( const char *nm, Expression *ptr, 
			    int place, SNidentifierlist *lstPtr) 
    : SNunit("assignment",SN_ASSIGNMENT) 
{ 
  leftVarName    = nm; 
  exprPtr        = ptr;
  condExprPtr    = 0;

  integralType   = ASSIGNMENT_TYPE_ORIGINAL;     // for integral,bintegral flag

  refEtypeIntegral  = 0;
  refEtypeBintegral = 0;

  placeFlag      = place;
  placeLst       = lstPtr;
  
  return;
}

SNassignment::SNassignment( const char *nm, Expression *ptr, int place, 
			    Expression *whereCond) 
  : SNunit("assignment",SN_ASSIGNMENT) 
{ 
  leftVarName    = nm; 
  exprPtr        = ptr;
  integralType   = ASSIGNMENT_TYPE_ORIGINAL;     // for integral,bintegral flag

  refEtypeIntegral  = 0;
  refEtypeBintegral = 0;

  condExprPtr    = whereCond;
  placeFlag      = place;
  placeLst       = 0;

  return;
}


void SNassignment::print(std::ostream & ost)
{ 
  ost << leftVarName << " = ";
  exprPtr->print(ost);

  switch(placeFlag) {

  case SN_ASSIGNMENT_AT:
    ost << ", at ";
    placeLst->print(ost);
    break;

  case SN_ASSIGNMENT_ON:
    ost << ", on ";
    placeLst->print(ost);
    break;

  case SN_ASSIGNMENT_IN:
    ost << ", in ";
    placeLst->print(ost);
    break;

  case SN_ASSIGNMENT_WHERE:
    ost << ", where( ";
    condExprPtr->print(ost);
    ost << " )";
    break;
      
  default:
    break;
  }

  return;
}
