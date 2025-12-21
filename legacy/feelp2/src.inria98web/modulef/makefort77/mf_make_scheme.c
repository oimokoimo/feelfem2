/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_make_scheme.c
 *      Date:   1998/11/25
 *   
 *   Purpose:   make feelmain.f routine
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"


void mf_make_scheme( utiliser_avs )
     int utiliser_avs;
{
  FILE *fp ;
  int i;
  
  int nopos;       /* number of nopo data (current 1) */


  fp = mfFileWriteOpen( MF_FNAME_FEELMAIN, MF_FCODE_FEELMAIN );
  
  if(utiliser_avs) {
    fprintf(stderr,"Maintenant, il n'y a pas.\n");
    exit(1);
  }
  else {

    
    F77("      SUBROUTINE FEELMAIN(M,DM,IMPRE)\n");
    F77("*--------------------------------------------------\n");
    F77("      PARAMETER (MAXSBD = 10)\n");
    F77("\n");
    F77("      dimension  M(*)\n");
    F77("      real*8    DM(*)\n");

   

  }


  F77("*--------------------------------------------------\n");
  F77("* SET GENERAL VARIABLES\n");
  F77("* \n");
  F77("* NTYP   : REAL VALUE TYPE\n");
  F77("* NBREMO : FACTOR IN READRE MODULEF SUBROUTINE\n");
  F77("*--------------------------------------------------\n");
  F77("      NTYP = IINFO('REEL2')\n");
  F77("      CALL TYPMOT(NTYP, NBREMO)\n");
  F77("*--------------------------------------------------\n");
  F77("\n");
  F77("*---------------------------------------*\n");
  F77("* ASSIGN NOPO DATA TO FILE (BAMG OUTPUT)*\n");
  F77("*---------------------------------------*\n");



  fprintf(stderr,"Now Under construnction, nopo=1\n");
  nopos = 1;

  for(i=0;i<nopos;i++) {

    PUT(fp,"      CALL TRUNIT(NFNOPO%d)\n",i+1);
    PUT(fp,"      CALL OUVRIS(NFNOPO%d,'bamg.nopo','OLD,UNFORMATTED',0)\n",i+1);
    PUT(fp,"*\n");
    PUT(fp,"      NINOPO%d = %d\n",i+1,i+1);
    PUT(fp,"      NTNOPO%d =  0\n",i+1);

    PUT(fp,"      call FEELNOPO(M,NFNOPO%d,NINOPO%d,NTNOPO%d,\n",i+1,i+1,i+1);
    PUT(fp,"     $              NPMAX%d,NE%d)\n",i+1,i+1);
    F77(   "*\n");
  }

  F77("*---------------------------------------------------\n");
  F77("* ALLOCATE WORK ARRAY (DOUBLE PRECISION FOR POINTS\n");
  F77("*                                           ELEMENTS\n");
  F77("*---------------------------------------------------\n");
  for(i=0;i<nopos;i++) {
    PUT(fp,"      CALL READRE(NTYP,'WKP%d',NP_WKP%d,NPMAX%d*NBREMO,M,IOUT)\n",
	i+1,i+1,i+1);
    PUT(fp,"      CALL READRE(NTYP,'WKE%d',NP_WKE%d,NE%d   *NBREMO,M,IOUT)\n",
	i+1,i+1,i+1);
    F77("*\n");
  }

  /* fem variable allocation */
  mf_make_scheme_femalloc(fp);


  /* ewise variable allocation */
  mf_make_scheme_ewisealloc(fp); 
  
  
  /* scalar variable allocation */
  /*  mf_make_scheme_scalaralloc(fp); */
  

  fprintf(stderr,"UNDER CONSTRUCTION(mf_make_scheme)\n");


  mfCOM(fp);
  F77("      RETURN\n");
  F77("      END\n");

  mfFileClose(fp);

  return;
}

