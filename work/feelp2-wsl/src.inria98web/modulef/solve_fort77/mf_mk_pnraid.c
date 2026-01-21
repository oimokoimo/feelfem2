/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_pnraid.c
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

void mf_mk_pnraid( solves )
     int solves;
{
  int i,j;
  int counter;

  Solve           *solve_ptr;
  SolveElement    *solve_elem_ptr;
  SolveFORT77     *solve77_ptr;
    
  FILE *fp;


  fp = mfFileWriteOpen( MF_FNAME_PNRAID, MF_FCODE_PNRAID );


  F77("      SUBROUTINE PNRAID(M,NDIM,NOCAL,NOTELM,NOTELF,NMMAST,NTYTA,NINDI,\n");
  F77("     +           NSTOC,X,NDI,NPO,\n");
  F77("     +           VOLUME,LVOLUM,SURFAC,LSURFA,ARETE,LARETE,POINT,LPOINT,\n");
  F77("     +           VOLUMF,LVOLUF,SURFAF,LSURFF,ARETF,LARETF,POINTF,LPOINF,\n");
  F77("     +           NOREF,IAXELO,NAXELO,AXELOC,LCPT,AE,NCODE,NFPOBA,NDSDE,\n");
  F77("     +           NONO,AXENOD,LXNOD,LVECT,TRAV,LTRAV,INDICE)\n");
  F77("C  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  F77("C   PURPOSE: TO CALL THE ELEMENT STIFFNESS MATRIX CALCULATION ROUTINES\n");
  F77("C            FOR PERSONAL LIBRARY\n");
  F77("C  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  F77("C *NOTICE*\n");
  F77("C   This is a copy of MODULEF's program TNRAID, with calls to all\n");
  F77("C   the existing elements removed and slightly modified for PERSonal\n");
  F77("C   element library.\n");
  F77("C   To incorporate the element into the MODULEF library, this\n");
  F77("C   routine would not be used, and instead TNRAID would be modified\n");
  F77("C   accordigly.\n");
  F77("C  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  F77("C   INPUT PARAMETERS\n");
  F77("C   -----------------------\n");
  F77("C   NDIM    : SPACE DIMENSION\n");
  F77("C   NOCAL   : CALCULATION OPTION INDICATOR\n");
  F77("C             1 : JUST RETURN CARACTERISTIC ELEMENT PARAMETERS\n");
  F77("C             2 : CALCULATE THE ELEMENT MATRIX \n");
  F77("C\n");
  F77("C   NOTELM   : TREATMENT PARAMETER FOR 'MILI' DATA STRUCTURE\n");
  F77("C              > 0 ISOTROPIC\n");
  F77("C              < 0 ANISOTROPIC\n");
  F77("C   X,Y,Z   : COORDINATES OF THE POINTS\n");
  F77("C\n");
  F77("C   VOLUME  : VOLUME  DESCRIPTION TABLE for MILI/FORC and element library\n");
  F77("C   SURFAC  : SURFACE DESCRIPTION TABLE for MILI/FORC and element library\n");
  F77("C   ARETE   : EDGE    DESCRIPTION TABLE for MILI/FORC and element library\n");
  F77("C   POINT   : POINT   DESCRIPTION TABLE for MILI/FORC and element library\n");
  F77("C\n");
  F77("C   LES MEMES AVEC F AU BOUT : IDEM MAIS LIEES A 'FORC'\n");
  F77("C   NCODE   : ELEMENT CODE NUMBER IN THE LIBRARY\n");
  F77("C   LCPT    : COMPTEUR DU NOMBRE D ELEMENTS DE TYPE NCODE   (v.o)\n");
  F77("C   LVECT   : LENGTH OF VECTOR (For Vector processor machines cf. NEC SX-5\n");
  F77("C   TRAV    : WORK ARRAY(S)  (TABLEAUX DE TRAVAIL)\n");
  F77("C\n");
  F77("C   OUTPUT PARAMETERS:\n");
  F77("C   --------------------\n");
  F77("C         SI NOCAL = 1 :\n");
  F77("C   NMMAST  : NUMBER OF REQUIRED WORDS!! TO STORE ELEMENT MATRIX AE\n");
  F77("C   NTYTA   : VARIABLE TYPE\n");
  F77("C   NINDI   : NOMBRE D INDICES DU TABLEAU\n");
  F77("C   NSTOC   : CODE DE SYMETRIE , >0 SI IL Y A SYMETRIE , < 0 SINON\n");
  F77("C   LVOLUM  : DIMENSION DU TABLEAU VOLUME  ( EN MOTS )\n");
  F77("C   LSURFA  : DIMENSION DU TABLEAU SURFAC\n");
  F77("C   LARETE  : DIMENSION DU TABLEAU ARETE\n");
  F77("C   LPOINT  : DIMENSION DU TABLEAU POINT\n");
  F77("C   LES MEMES AVEC F AU BOUT : IDEM MAIS LIEES A 'FORC'\n");
  F77("C   LTRAV   : LONG DU TAB DE TRAVAIL\n");
  F77("C   INDICE  : INDICE(4,4)\n");
  F77("C             INDICE(I,J)  I = 1 Mass matrix\n");
  F77("C                              2 Stiffness matrix\n");
  F77("C                              3 2nd member\n");
  F77("C                              4 CONTRAINTES (FLUX)\n");
  F77("C                          J = 1...3 VAL MAX DES INDICES\n");
  F77("C                              4 NOMBRE D'INDICES\n");
  F77("C         SI NOCAL = 2 :\n");
  F77("C   AE      : MATRICE ELEMENTAIRE DE RIGIDITE ,SYMETRIQUE DONT SEULE\n");
  F77("C                    LA PARTIE TRIANGULAIRE SUPERIEURE EST STOCKEE,\n");
  F77("C                    DE HAUT EN BAS ET DE LA GAUCHE VERS LA DROITE\n");
  F77("C \n");
  F77("C   REMARQUE :\n");
  F77("C   NONO,AXENOD,LXNOD : PARAMETRES BIDON AJOUTES POUR AVOIR LE MEME \n");
  F77("C   NOMBRE DE PARAMETRE EN THERMIQUE ET EN ELASTICITE\n");
  F77("C  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  F77("C   PROGRAMMEUR : MARINA VIDRASCU  . INRIA . \n");
  F77("C  ....................................................................\n");
  F77("      DIMENSION M(*),AE(*),VOLUME(*),SURFAC(*),ARETE(*), POINT(*),\n");
  F77("     +           X(LVECT*NPO,*),VOLUMF(*),SURFAF(*),ARETF(*),\n");
  F77("     +           POINTF(*),TRAV(*),INDICE(4,4)\n");
  F77("      INTEGER NOREF(*),NOTELM(*),NOTELF(*)\n");
  F77("      COMMON/PAQUET/IPAQUE\n");
  F77("99991 FORMAT(' %% ERROR PNRAID : ELEMENT',I10,' DOES NOT EXIST.')\n");
  F77("C\n");
  F77("      IMPRIM = IINFO('I')\n");
  F77("      NCOD1 = NCODE - 000000\n");
  F77("C   ******************************************************************\n");
  F77("C     CAUTION: THIS ROUTINE WAS GENERATED BY FEEL P3 SYSTEM\n");
  F77("C   ******************************************************************\n");
  F77("C\n");


  F77("      GO TO (");
  counter = 0;
  for(i=0;i<solves;i++) {
    counter = counter + 1;
    if(counter == 6) { F77("     $       ");  counter = 0; }
    PUT(fp,"%4d,",1001+i);
  }
  F77("9999)\n");
  F77("     +       ,NCOD1\n");
  F77("C\n");


  for(i=0;i<solves;i++) {
    PUT(fp," %4d CALL PRS0",1001+i);
    if(i < 10) {
      PUT(fp,"0%d",i+1);
    }
    else {
      PUT(fp,"%2d",i+1);
    }
    F77(" (NOCAL,NOTELM,NOREF,\n");
    F77("     $             MMAST,NTYTA,NINDI,NSTOC,\n");
    F77("     $             X(1,1),X(1,2),\n");
    F77("     $             VOLUME,LVOLUM,\n");
    F77("     $             SURFAC,LSURFA,\n");
    F77("     $             ARETE, LARETE,\n");
    F77("     $             POINT, LPOINT,\n");
    F77("     $             AE                      )\n");
  F77("      GOTO 1000\n");
  F77("C\n");
  }

  F77(" 9999 WRITE (IMPRIM,99991) NCODE\n");
  F77("      STOP\n");
  F77("C\n");
  F77(" 1000 CONTINUE\n");
  mfCOM(fp);

  F77("      IF (NOCAL .EQ. 2 .AND. IPAQUE .NE. 1) THEN\n");
  F77("         IF (NSTOC.EQ.1 .OR. NSTOC.EQ.0) THEN\n");
  F77("            CALL TYPMOT(NTYTA,NBREMO)\n");
  F77("            INDICE(2,1) = NMMAST/NBREMO\n");
  F77("            INDICE(2,4) = 1\n");
  F77("         ELSE\n");
  F77("            CALL TYPMOT(NTYTA,NBREMO)\n");
  F77("            LL = NMMAST/NBREMO\n");
  F77("            LL = SQRT(REAL(LL))\n");
  F77("            INDICE(2,1) = LL\n");
  F77("            INDICE(2,2) = LL\n");
  F77("            INDICE(2,4) = 2\n");
  F77("         ENDIF\n");
  F77("      END IF\n");
  F77("*\n");
  F77("      RETURN\n");
  F77("      END\n");

  
  mfFileClose(fp);

  return;
}

