/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNoutput_CodeGenerator.cpp
 *  Date     : 2002/07/16
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#include <iostream.h>

#include "SNoutput.hpp"
#include "CodeGenerators.hpp"

void SNoutput::CodeGenerate(void)
{

  cg_Output( outputPtr );

  return;
}
