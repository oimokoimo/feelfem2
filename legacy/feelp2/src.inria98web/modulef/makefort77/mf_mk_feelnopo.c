/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_feelnopo.c
 *      Date:   1998/11/25
 *   
 *   Purpose:   make feelnopo.f
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"
  
#include "../modulef_def/modulef_def.h"

void mf_mk_feelnopo()
{
  FILE *fp;

  fp = mfFileWriteOpen( MF_FNAME_FEELNOPO, MF_FCODE_FEELNOPO );
  
  F77("      SUBROUTINE FEELNOPO(M,NFNOPO,NINOPO,NTNOPO,NPMAX , NE )\n");
  F77("*--------------------------------------------------------------------\n");
  F77("      PARAMETER (LNOPO = 19)\n");
  F77("\n");
  F77("      DIMENSION M(*)\n");
  F77("      DIMENSION MCNOPO(LNOPO)\n");
  F77("*\n");
  F77("      COMMON/ALNOPO/NENOPO,\n");
  F77("     +       NNOP0,IANOP0,LNOP0,NNOP1,IANOP1,LNOP1,NNOP2,IANOP2,LNOP2,\n");
  F77("     +       NNOP3,IANOP3,LNOP3,NNOP4,IANOP4,LNOP4,NNOP6,IANOP6,LNOP6\n");
  F77("*\n");
  F77("      EQUIVALENCE (NENOPO,MCNOPO(1))\n");
  F77("*--------------------------------------------------------------------\n");
  F77("\n");
  F77("      CALL SDREST(M,'NOPO',NFNOPO,NINOPO,MCNOPO,LNOPO,NNOPO,IANOPO)\n");
  F77("*\n");

  F77("* KEEP NOPO IN CORE\n");
  F77("      CALL CLOSE (NFNOPO)\n");
  F77("      NFNOPO =  0\n");

  F77("*\n");
  F77("      NDIM   = M(IANOP2   )\n");
  F77("      NE     = M(IANOP2+ 5-1)\n");
  F77("      NPMAX  = M(IANOP2+15-1)\n");
  F77("\n");
  F77("      RETURN\n");
  F77("\n");
  F77("      end\n");

  
  mfFileClose(fp);

  return;
}
