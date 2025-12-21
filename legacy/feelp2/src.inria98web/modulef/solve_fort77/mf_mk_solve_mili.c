/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_solve_mili.c
 *      Date:   1998/12/11
 *   
 *   Purpose:   make solveXXmili.f
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../solve_comp/solve_comp.h"
#include "../../mesh_comp/mesh_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_mk_solve_mili( solve_ptr , solve77_ptr)
     Solve       *solve_ptr;
     SolveFORT77 *solve77_ptr;
{
    int i,j;
    int flag;
    
    int solve_no;
    
    int elemg;   /* 要素グループの個数、SolveElementの数 */
    int solve_elements;  /* 上と重複しているが… */
    SolveElement *solve_element_ptr;

    int max_nodes;
    int dconds,nconds;

    FILE *fp;

    
    ElementFORT77 **elem77_ptrptr,*elem77_ptr;   
    ElemDat        *elem_dat_ptr;
    DirichletData **d_ptrptr,*d_ptr; 
    NeumannData   **n_ptrptr,*n_ptr;

    Domain         *domain_ptr;
    int             regions_in_domain;

    
    char fname[30];

    /* Get mesh information */    
    domain_ptr = get_nth_domain_ptr(0);
    regions_in_domain = domain_ptr -> regions;


    /* Get information */
    solve_no      = solve77_ptr -> solve_no;
    elemg         = solve77_ptr -> elemg;
    solve_elements= solve_ptr   -> solve_elements;
    elem77_ptrptr = solve77_ptr -> elem77_ptrptr;
    max_nodes     = solve77_ptr -> max_nodes;
    
    
    dconds   = solve_ptr -> d_conditions;
    d_ptrptr = solve_ptr -> d_dat;
    
    nconds   = solve_ptr -> n_conditions;
    n_ptrptr = solve_ptr -> n_dat;
    


    /* First Solve Element Information (This is for MODULEF short time expansion) */
    if(elemg != 1) {
      SystemAbort("MODULEF EXPANSION, elemg is assumed to be only one.");
    }

    solve_element_ptr = *(solve_ptr->solve_elem_dat + 0);




    /* The end of short time coding */


    /* MAKE FILE NAME */
    if(solve_no <1 || solve_no>99) {
      SystemAbort("solve no. Error (mf_mk_solve_mili)");
    }

    sprintf(fname,MF_FNAME_SOLVE_MILI,solve_no);
    fp = mfFileWriteOpen( fname , MF_FCODE_SOLVE_MILI);
    
    
    /* 01:SUBROUTINE STATEMENT */
    PUT(fp,"      subroutine ");
    PUT(fp,MF_NOM77_SOLVE_MILI,solve_no);    
    if(solve_no<10) F77(" ");
    PUT(fp,"(");

    F77("M");
    

    F77(",IEMILI,NFMILI,NIMILI,NTMILI)\n");

    /* 02:Discription statement */
    mf_header(fp);

    /* DECLARE MAXSBD */
    F77("      PARAMETER    (MAXSBD = 10)\n");
    mfCOM(fp);

    /* :SUPPER ARRAY */
    F77("      dimension M(*)\n");
    mfCOMCOM(fp);




    F77("C  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    F77("C  Purpose :  Create data structure MILI \n");
    F77("C\n");
    F77("C             This is modified subroutine of comili.f\n");
    F77("C     \n");
    F77("C  Caution :  NIVMIL -> NIMILI    Name changed\n");
    F77("C             NTAMIL -> NTMILI    Name changed\n");
    F77("C\n");
    F77("C  CAUTION!:  THIS SUBROUTINE IS MESH DEPENDENT!!!(especially subdomains)\n");
    F77("C\n");

    F77("C  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    F77("C  IN :\n");
    F77("C  --\n");
    F77("C  M      : SUPER Array\n");
    F77("C  NFMILI : Unit No. for MILI data structure\n");
    F77("C  NIMILI : Level No. for this MILI D.S.\n");
    F77("C  NTMILI : Total number of Associated arrays\n");
    F77("C  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    F77("C  Original programmer : MARINA ROTTMAN   INRIA\n");
    F77("C  ...................................................................\n");


    F77("      CHARACTER*4 CHAR4\n");
    F77("      DIMENSION  M(*),K(24),NZMILI(34)\n");
    F77("      COMMON /UNITES/ LECTEU,IMPRIM,FILUNI(30)\n");
    F77("      COMMON/TRAVA1/NX(28),LONREE,IMPRE,IFILL(3)\n");
    F77("      COMMON/ALMILI/NEMILI,NMIL0,IAMIL0,LMIL0,NMIL1,IAMIL1,LMIL1,\n");
    F77("     +                     NMIL2,IAMIL2,LMIL2,NMIL3,IAMIL3,LMIL3,\n");
    F77("     +                     NMIL4,IAMIL4,LMIL4,NMIL5,IAMIL5,LMIL5,\n");
    F77("     +                     NMIL6,IAMIL6,LMIL6,NMIL7,IAMIL7,LMIL7,\n");
    F77("     +                     NMIL8,IAMIL8,LMIL8,NMIL9,IAMIL9,LMIL9,\n");
    F77("     +                     NMILA,IAMILA,LMILA\n");
    F77("      EQUIVALENCE (NMIL3,K(1)),(NEMILI,NZMILI(1))\n");
    F77("C------------------------------------------------------------------\n");
    F77("      IF ( IMPRE .NE. 0 ) WRITE (IMPRIM,100) (NX(I),I=1,20)\n");
    F77("      IF ( IMPRE .GE. 2 ) WRITE(IMPRIM,110) NFMILI,NIMILI,NTMILI\n");
    F77("C------------------------------------------------------------------\n");
    F77("C    INITIALISER LE COMMON\n");
    F77("C    ---------------------\n");
    F77("      CALL INICSD(M,'MILI',NIMILI,NZMILI,34,NCMILI,IACMIL)\n");
    F77("      NMEMIL = 0\n");
    F77("C\n");
    F77("C    PREMIER TABLEAU\n");
    F77("C    ---------------\n");
    F77("      LMIL0 = 32\n");
    F77("      CALL READRE(1,CHAR4(NMIL0),IAMIL0,LMIL0,M,NRET)\n");
    F77("C\n");
    F77("      CALL TRTATA(NX,M(IAMIL0),28)\n");
    F77("      NOMSD = ICHAR4('MILI')\n");
    F77("      M(IAMIL0+28) = NOMSD\n");
    F77("      M(IAMIL0+29) = NIMILI\n");
    F77("      M(IAMIL0+30) = 0\n");
    F77("      M(IAMIL0+31) = NTMILI\n");
    F77("C\n");
    F77("C    LES TABLEAUX ASSOCIES\n");
    F77("C    ---------------------\n");
    F77("      IF(NTMILI.NE.0) CALL COTASD(M,NTMILI,NTMILI,NMIL1,IAMIL1,LMIL1)\n");
    F77("C\n");
    F77("C    TABLEAU  MIL2\n");
    F77("C    -------------\n");
    F77("      LMIL2 = 8\n");
    F77("      CALL READRE(1,CHAR4(NMIL2),IAMIL2,LMIL2,M,NRET)\n");
    F77("\n");
    F77("\n");
    F77("C----------------------------------------\n");
    F77("C     Original program read from Keyboard\n");
    F77("C     [CALL LECTUT(1,M(IAMIL2),8)]\n");
    F77("C  \n");
    F77("C     MIL2 for\n");
    F77("C     MIL3 (IAMIL2 + 1 -1)  Volume   by  Reference No. (sub-domain No.) \n");
    F77("C     MIL4 (IAMIL2 + 2 -1)  Surface  by  Reference No.F\n");
    F77("C     MIL5 (IAMIL2 + 3 -1)  Edge     by  Reference No.C\n");
    F77("C     MIL6 (IAMIL2 + 4 -1)  Point    by  Reference No.\n");
    F77("C\n");
    F77("C     MIL7 (IAMIL2 + 5 -1)  Volume   by  Element \n");
    F77("C     MIL8 (IAMIL2 + 6 -1)  Surface  by  Element\n");
    F77("C     MIL9 (IAMIL2 + 7 -1)  Edge     by  Element\n");
    F77("C     MILA (IAMIL2 + 8 -1)  Point    by  Element\n");
    F77("C\n");
    F77("C     Volume   Volume (One call for milieu)\n");
    F77("C     Surface  3D case number of surface call (6 for hexahedra, 4 for tetra)\n");
    F77("C              2D One call \n");
    F77("C     Edge     Called number of edges depending on the element shape\n");
    F77("C     Point    Called number of Point depending on the element\n");
    F77("C  \n");
    F77("C     References         V  number of different LOPT you want\n");
    F77("C                          (Generally, number of sub-domains)\n");
    F77("C----------------------------------------\n");
    F77("      M(IAMIL2 + 1 -1) = 0\n");
    PUT(fp,"      M(IAMIL2 + 2 -1) = %d\n",regions_in_domain);
    F77("      M(IAMIL2 + 3 -1) = 0\n");
    F77("      M(IAMIL2 + 4 -1) = 0\n");

    F77("      M(IAMIL2 + 5 -1) = 0\n");
    F77("      M(IAMIL2 + 6 -1) = 0\n");
    F77("      M(IAMIL2 + 7 -1) = 0\n");
    F77("      M(IAMIL2 + 8 -1) = 0\n");
    F77("C\n");
    F77("C    TABLEAUX SUIVANTS\n");
    F77("C    -----------------\n");
    F77("\n");
    F77("C--------------------------------------------------------------------\n");
    F77("C----------\n");
    F77("      I = 2\n");
    F77("C----------\n");
    F77("      NEL = M(IAMIL2+I-1)\n");
    F77("      IF ( NEL .EQ. 0 ) stop 'INNER ERROR IN SOLVE@MILI'\n");
    F77("      L   = 7 * NEL\n");
    F77("      K(3*I) = MAX(K(3*I),L)\n");
    F77("      CALL READRE(1,CHAR4(K(3*(I-1)+1)),K(3*(I-1)+2),K(3*I),M,NRET)\n");
    F77("\n");
    F77("      J = K(3*I-1)\n");
    F77("\n");


    F77("*-----------------------------------------------------\n");
    F77("*  MIL3 Data Information in MILI D.S.\n");
    F77("*-----------------------------------------------------\n");

    F77("*1:I_NDSD   : Sub-region No. (for SURFACE 2D case)in MIL3)\n");
    F77("*           : Reference  No. (for SURFACE 3D case in MIL3)\n");

    F77("*2:I_ADR    : always 0\n");
    F77("*3:I_NUM    : always 0\n");
    F77("*\n");
    F77("*4:I_IOPT   : >0 if isotropic, <0 if anisotropic, so here set to -1\n");

    F77("*\n");
    F77("*5:I_CODE   : How to set data FLAG\n");
    F77("* (ITRAIT)    = 1 by array\n");
    F77("*             = 2 by subroutine MILIEU  (USE HERE)\n");
    F77("*             = 3 by user subroutine\n");
    F77("*\n");
    F77("*6:I_INFO1  : I_CODE=1  the array name\n");
    F77("*           : I_CODE=2  the value for 'LOPT' in case of I_NDSD\n");
    F77("*                       for subroutine MILIEU\n");
    F77("*             I_CODE=3  0\n");
    F77("*\n");
    F77("*7:I_INFO2  : I_CODE=1  the address in the array of the first value needed\n");
    F77("* ?????     : I_CODE=2  the address in the array on return from \n");
    F77("*                       subroutine MILIEU of the first value needed\n");
    F77("*             I_CODE=3  0\n");
    F77("*-----------------------------------------------------\n");    


    for(i=0;i<regions_in_domain;i++) {
      
      
      PUT(fp,"      I_NDSD  =  %d\n",i+1);
      F77(   "      I_IADR  =  0\n");
      F77(   "      I_NUM   =  0\n");
      F77(   "      I_OPT   = -1\n");
      F77(   "      I_OPT   =  2\n");
      F77(   "* Pass region No. to MILIEU\n");
      PUT(fp,"      I_INFO1 =  %d\n",i+1);
      F77(   "      I_INFO2 = 999?\n");
      F77("*-----\n");
      /*    F77("c         CALL LECTU4(1,M(J),M(J+2),M(J+3),M(J+4))\n");
	    F77("c                       NOSD NUM    IOPT   \n");          */
      F77("         M(J)   = I_NDSD\n");
      F77("         M(J+2) = I_NUM\n");
      F77("         M(J+3) = I_OPT\n");
      F77("         M(J+4) = I_CODE\n");
      F77("c\n");
      F77("         M(J+1) = I_IADR\n");
      F77("         IJ     = M(J+4)\n");
      F77("c         ->CODE\n");
      F77("*\n");
      F77("         IF ( IJ .EQ. 1 ) THEN\n");
      F77("\n");
      F77("* becasue M(J+5) is name of array, originally\n");
      F77("            M(J+5) = I_INFO1\n");
      F77("            M(J+6) = I_INFO2\n");
      F77("         ELSE\n");
      F77("            M(J+5) = I_INFO1\n");
      F77("            M(J+6) = I_INFO2\n");
      F77("\n");
      F77("         END IF\n");
      F77("         J = J + 7\n");
    }

    F77("c------------------------------------------------------------------\n");
    F77("c  end of I=2\n");
    F77("c------------------------------------------------------------------\n");
    F77("      CALL SDSAUV(M,'MILI',NFMILI,NIMILI,NZMILI,34,NCMILI,IACMIL,\n");
    F77("     +                          NMEMIL)\n");
    F77("      IF ( IMPRE .NE. 0 ) WRITE (IMPRIM,200)\n");
    F77("C\n");
    F77("C 100 FORMAT(1X,78('&')/' MODULE COMILI : ',20A4/1X,78('&')/)           #GB\n");
    F77("C 110 FORMAT(' OUTPUT D.S. MILI   ( NFMILI AND NIMILI ) : ',2I6/        #GB\n");
    F77("C    +       ' NUMBER OF ASSOCIATED TABLES   ( NTMILI) : ',I6/)         #GB\n");
    F77("C 200 FORMAT(1X,78('&')/' END OF MODULE COMILI  '/1X,78('&')/)          #GB\n");
    F77("C\n");
    F77("  100 FORMAT(1X,78('&')/' MODULE COMILI : ',20A4/1X,78('&')/)           #F\n");
    F77("  110 FORMAT(' S.D.S. MILI      ( NFMILI ET NIMILI ) : ',2I6/           #F\n");
    F77("     +       ' NOMBRE DE TABLEAUX ASSOCIES ( NTMILI) : ',I6/)           #F\n");
    F77("  200 FORMAT(1X,78('&')/' FIN DU MODULE COMILI  '/1X,78('&')/)          #F\n");
    F77("C\n");
    F77("      END\n");

    mfFileClose( fp );
    return;
    
}
