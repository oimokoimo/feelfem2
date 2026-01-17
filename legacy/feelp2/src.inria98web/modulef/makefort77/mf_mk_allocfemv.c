/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_allocfemv.c
 *      Date:   1998/12/14
 *   
 *   Purpose:   make ALLOCFEMV subroutine
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"

void mf_mk_allocfemv()
{
  FILE *fp;

  fp = mfFileWriteOpen( MF_FNAME_ALLOCFEMV, MF_FCODE_ALLOCFEMV );
  
  F77("      SUBROUTINE ALLOCFEMV(M, NTYP, NIVB, NFNOPO, NINOPO, WORK)\n");
  F77("C------------------------------------------------------------------\n");
  F77("C     ALLOCATE B DATA STRUCTURE FOR FEM VARIABLE OF NFNOPO\n");
  F77("C------------------------------------------------------------------\n");
  F77("      DIMENSION M(*)\n");
  F77("      REAL*8    WORK(*)  , FEELZERO\n");
  F77("      LOGICAL   FONINT\n");
  F77("      EXTERNAL  FEELZERO\n");
  F77("C\n");
  F77("      if(NTYP .EQ. IINFO('REEL2')) THEN\n");
  F77("         NVEC   = -1\n");
  F77("      ELSE\n");
  F77("         NVEC   =  1\n");
  F77("      ENDIF\n");
  F77("*\n");
  F77("      ND     =  1\n");
  F77("      NFB    = 0\n");
  F77("      NIVB   = NIVB\n");
  F77("      NTAB   = 0\n");
  F77("      FONINT = .FALSE.\n");
  F77("\n");
  F77("C\n");
  F77("      CALL COSNOB(M,M,NFNOPO,NINOPO,NVEC,WORK,WORK,WORK,WORK,ND,\n");
  F77("     $            NFB,NIVB,NTAB,FONINT,FEELZERO,FEELZERO       )\n");
  F77("C\n");
  F77("      RETURN\n");
  F77("      END\n");
  F77("      REAL*8 FUNCTION FEELZERO(K,X,Y,Z)\n");
  F77("      FEELZERO = 0.0D0\n");
  F77("      RETURN\n");
  F77("      END\n");

  mfFileClose(fp);

  return;
}
