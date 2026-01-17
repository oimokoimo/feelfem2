/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElemScheme.cpp
 *  Date     : 1999/12/10
 *  Modified : 1999/12/10
 *  
 *  Purpose  : Assembly routine definition
 *  
 */

#include <assert.h>
#include <iostream.h>
#include "ElemScheme.hpp"

ElemScheme::ElemScheme() {

  elemSchemes++;
  return;
}

ElemScheme::~ElemScheme() {
  cout << "I'm ElemScheme Destructor\n";
}

