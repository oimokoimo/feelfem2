/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Procedure.cpp
 *  Date     : 2001/04/23
 *  Modified : 
 *  
 *  Purpose  : Program model... (still pending for purpose)  2002.1.10
 *  
 */

#include "Procedure.hpp"
#include "feeldef.hpp"

Procedure feelfemproc;             

Procedure::Procedure()
{
  // do nothing now
  
  programModel = PROC_DEFAULT_PROGRAM_MODEL;

  return;
}


Procedure::~Procedure()
{

  // do nothing now 
}
