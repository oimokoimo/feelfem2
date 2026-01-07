/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : 
 *  Date     : 2000/04/25
 *  Modified : 2000/04/25
 *  
 *  Purpose  :
 *  
 */

#include "Scheme.hpp"

Scheme::Scheme(void) {
  // do nothing 
  return;
}

Scheme::~Scheme(void) {
  // do nothing 
  return;
}

Scheme::Scheme(void *po, int type) {

  schemeType = type;
  ptr = po;

  return;
}

