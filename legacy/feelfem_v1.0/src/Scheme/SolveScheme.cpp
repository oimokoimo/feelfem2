/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SolveScheme.cpp
 *  Date     : 1999/10/26
 *  Modified : 1999/11/18
 *  
 *  Purpose  : test function
 *  
 */

#include <assert.h>
#include "SolveScheme.hpp"

SolveScheme::SolveScheme() {

  solveSchemes++;
  return;
}

SolveScheme::~SolveScheme() {
  cout << "I'm SolveScheme Destructor\n";
}
