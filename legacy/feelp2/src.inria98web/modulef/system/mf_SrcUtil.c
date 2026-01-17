/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_SrcUtil.c
 *      Date:   1998/11/02
 *   
 *   Purpose:   Various source utility functions
 *   Functions: mf_header( FILE *fp ) : printing header
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"

static int output_level=2;   /* 0: nothing   1: midium  2: maximum */


void mfCOM(fp)
     FILE *fp;
{
  F77("*\n");
  return;
}

void mfCOMCOM(fp)
     FILE *fp;
{
  F77("*-------------------------------------------------\n");
  return;
}

void mf_header( fp )
     FILE *fp;
{
  if(output_level==0) return;

  mfCOMCOM(fp);
  F77("*    feel p3 fort77 (Modulef Structure)\n");

  if(output_level == 2) {
    PUT(fp,"*    User %s\n",feel_user);
    PUT(fp,"*    Date %s\n",feel_date);
  }
  mfCOMCOM(fp);

  return;
}
