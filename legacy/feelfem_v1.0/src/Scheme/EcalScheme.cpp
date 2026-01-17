/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalScheme.hpp
 *  Date     : 1999/12/10
 *  Modified : 1999/12/10
 *  
 *  Purpose  : Assembly routine definition
 *  
 */

#include <assert.h>
#include <iostream.h>
#include "EcalScheme.hpp"

EcalScheme::EcalScheme() {

  ecalSchemes++;
  return;
}

EcalScheme::~EcalScheme() {
  cout << "I'm EcalScheme Destructor\n";
}

