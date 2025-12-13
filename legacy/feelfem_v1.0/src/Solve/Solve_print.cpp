/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Solve_print.cpp
 *  Date     : 2002/02/05
 *  Modified : 
 *  
 *  Purpose  : check write routine
 *  
 */

#include <iostream.h>

#include "Solve.hpp"

void Solve::print(ostream &ost)
{
  ost << "---------------------------------------" << endl;
  ost << "solve no = " << solveNo << endl;
  ost << "dconds   = " << dirichletConditions << endl;
  ost << "nconds   = " << neumannConditions << endl;

  ost << endl;


  ost << "VARS ";
  listIterator <Variable *>itr(solveVariablePtrLst);
  for(itr.init(); !itr ; ++itr) {
    ost <<" ";
    itr()->print(ost);
  }
  ost << "---------------------------------------" << endl;
  return;
}

