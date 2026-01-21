/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   modulef_var_ctrl.c
 *      Date:   1998/12/17
 *   
 *   Purpose:   set DS B niveau 
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "var_comp.h"

#include "../modulef/modulef_def/modulef_def.h"

static int B_niv = 0;
int get_new_B_niv()
{
  B_niv++;
  return(B_niv);
}

