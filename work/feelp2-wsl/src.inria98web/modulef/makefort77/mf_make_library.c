/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   
 *      Date:   1998/11/25
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"

void mf_make_library()
{
  
  /* This module makes feel-modulef library (always same..) */

  mf_mk_feelnopo();
  mf_mk_allocfemv();

  return;
}
    
