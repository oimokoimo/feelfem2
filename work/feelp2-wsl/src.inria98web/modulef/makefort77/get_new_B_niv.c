/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   get_new_B_niv.c
 *      Date:   1998/12/28
 *   
 *   Purpose:   Make B level number
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"

static int B_niveau = 0;

int get_new_B_niv()
{
  B_niveau++;

  return(B_niveau);
}
