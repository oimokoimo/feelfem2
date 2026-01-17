/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_dobper.c
 *      Date:   1998/12/04
 *   
 *   Purpose:   Make Modulef library control program PNRAID.f
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../modulef_def/modulef_def.h"
#include "../../solve_comp/solve_comp.h"

void mf_mk_dobper( solves , etype)   /* element type is here, in etype */
     int solves;
     int etype;
{
  int i,j,k,dix,pr;
  int counter;

  Solve           *solve_ptr;
  SolveElement    *solve_elem_ptr;
  SolveFORT77     *solve77_ptr;
    
  FILE *fp;


  fp = mfFileWriteOpen( MF_FNAME_DOBPER, MF_FCODE_DOBPER );


  F77("      SUBROUTINE DOBPER(M,I1,I2,NCOD,NRECH)\n");
  F77("C  --------------------------------------------------\n");
  F77("C  BUT : DOB CALL UTILITY FOR PERSONAL LIBRARY\n");
  F77("C        IF NRECH = 1\n");
  F77("C           CALCULATE THE NUMBER OF CODE OF THE ELEMENT AND\n");
  F77("C           VERYFY IT REALLY EXISTS IN THE ELEMENT LIBRARY\n");
  F77("C\n");
  F77("C        IF NRECH = 2\n");
  F77("C           CALL THE ELEMENT-INTERPOLATION DEFINITION ROUTINES \n");
  F77("C           SPECIFIED BY THE ELEMENT NUMBER CODE I1 AND I2\n");
  F77("C  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  F77("C  PARAMETRE D ENTREE :\n");
  F77("C  ------------------\n");
  F77("C  M      : SUPER-TABLEAU DE TRAVAIL\n");
  F77("C  I1,I2  : NOM DU TYPE D ELEMENT (2A4)\n");
  F77("C  NRECH  : VOIR DESCRIPTION DU BUT\n");
  F77("C  PARAMETRE D ENTREE OU SORTIE :\n");
  F77("C  ----------------------------\n");
  F77("C  NCOD   : NUMERO DE CODE DE L ELEMENT\n");
  F77("C  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  F77("C  PROGRAMMEUR : DANIELE LEROY IRIA 954 90 20 VERSION 1985\n");
  F77("C  ...................................................................\n");
  PUT(fp,"      PARAMETER  (LNB=%d)\n",solves);
  F77("*\n");
  F77("      INTEGER     M (*)\n");
  F77("      CHARACTER*4 CHAR4\n");
  F77("      CHARACTER*8 TYPELE,NB(LNB)\n");
  F77("*\n");

  F77("      DATA NB/");

  k = 0;
  for(i=0;i<solves;i++) {

    k=k+1;

    if(etype == TRI) {
      F77("'TRIAS0");
    }
    else {
      F77("'QUADS0");
    }
    j = i+1;
    if(j<10) {
      F77("0");
      PUT(fp,"%d",j);
    }
    else {
      PUT(fp,"%d",j);   /* <99 */
    }
    F77("'");
    if(solves-1 != i) {
      F77(",");

      if(k==5) {
	F77("\n          ");
      }
    }
  }
  F77("/\n");


  F77("*\n");
  F77(" 2000 FORMAT(' %% ERROR DOBPER :THE ELEMENT ',2A4,' DOES NOT EXIST ',\n");
  F77("     *' IN THE LIBRARY PERS '/)\n");
  F77("C\n");
  F77("      GOTO (1,6) NRECH\n");
  F77("\n");
  F77(" 1    TYPELE = CHAR4(I1)//CHAR4(I2)\n");
  F77("\n");
  F77("      DO 5 I=1,LNB\n");
  F77("         IF(TYPELE .EQ. NB(I)) GOTO 4\n");
  F77(" 5    CONTINUE\n");
  F77("\n");
  F77("C     THE ELEMENT TYPE DOES NOT EXIST IN THE LIBRARY\n");
  F77(" 999  WRITE (IINFO('I'),2000) I1,I2\n");
  F77("      STOP\n");
  F77("      \n");
  F77("C     NCOD FOR PERSONAL LIBRAY IS I ITSELF\n");
  F77("\n");
  F77("    4 NCOD = I\n");
  F77("\n");
  F77("\n");
  F77("      RETURN\n");
  F77("C\n");
  F77("C NRECH=2\n");
  F77("C\n");
  F77("    6 I=NCOD\n");
  F77("C\n");
  F77("C     SEARCH THE ELEMENT BY EACH 10 SET\n");
  F77("      IPP=(I-1)/10\n");
  F77("      IP1=IPP+1\n");
  F77("      IGT=I-IPP*10\n");
  F77("*\n");

  F77("      GOTO (");
  dix = (solves-1)/10;             /* j has dixenne */
  for(i=0;i<10;i++) {
    if(i <= dix) {
      PUT(fp,"%3d",10+i);
    }
    else {
      PUT(fp,"%3d",999) ;
    }
    if(i!=9) { F77(","); }
  }
  F77(") IP1\n");



  F77("C\n");
  F77("C     SEARCH THE ELEMENT ONE BY ONE\n");
  F77("C\n");


  for(i=0;i<dix+1;i++) {   /* step by 10 */
    PUT(fp,"%5d GOTO (",i+10);

    k= 0;
    for(j=dix*10;j<dix*10+10;j++) {
      if(j < solves) {
	pr = j+100;
      }
      else {
	pr = 999;
      }
      PUT(fp,"%3d",pr);
      if(j != dix*10+10-1) F77(",");
    }
    F77(") IGT\n");
    F77("*\n");
  }

  mfCOMCOM(fp);
  for(i=0;i<solves;i++) {
    pr=i+100;
    PUT(fp,"%5d CALL PDS0",pr);
    if((i+1)<10) {
      F77("0");
      PUT(fp,"%d",i+1);
    }
    else {
      PUT(fp,"%d",i+1);   /* <99 */
    }
    F77("(M)\n");
    F77("      RETURN\n");
    F77("*\n");
  }

  F77("      END\n");

  mfFileClose(fp);

  return;
}
