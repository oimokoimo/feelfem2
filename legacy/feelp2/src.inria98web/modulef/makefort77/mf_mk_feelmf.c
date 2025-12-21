/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_mainroutine.c
 *      Date:   1998/11/02
 *   
 *   Purpose:   make mainroutine for Modulef
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"

void mf_mk_feelmf()
{
  FILE *fp;

  fp = mfFileWriteOpen( MF_FNAME_FEELMF , MF_FCODE_FEELMF);
  
  F77("      program feelmf\n");
  
  mf_header(fp);

  PUT(fp,"      parameter ( LM    = %10d)\n",get_feel_array_size());
  PUT(fp,"      parameter ( IMPRE = %10d)\n",MF_DEFAULT_IMPRE);

  mfCOM(fp);

  F77("      dimension  M(LM)\n");
  F77("      real *  8 XM\n");
  F77("      equivalence (M,XM)\n");
  
  mfCOM(fp);

  F77("      call ESPION(IMPRE)\n");
  F77("      call INITIS(M,LM,IMPRE,NNN)\n");
  
  mfCOM(fp);
  F77("      call feelmain(M,IMPRE)\n");
  
  mfCOM(fp);
  F77("      end\n");

  mfFileClose(fp);

  return;
}





  


