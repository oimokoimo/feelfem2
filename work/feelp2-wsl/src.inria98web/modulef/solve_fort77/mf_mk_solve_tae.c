/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_solve_tae.c
 *      Date:   1998/12/02
 *   
 *   Purpose:   make solveXXmaco.f
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../solve_comp/solve_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_mk_solve_tae( solve_ptr , solve77_ptr)
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

    int known_variables;
    
    FILE *fp;
    
    ElementFORT77 **elem77_ptrptr,*elem77_ptr;   
    ElemDat        *elem_dat_ptr;
    DirichletData **d_ptrptr,*d_ptr; 
    NeumannData   **n_ptrptr,*n_ptr;
    
    char fname[30];
    
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
    
    known_variables = solve_ptr -> fem_knowns   +
                      solve_ptr -> ewise_knowns +
                      solve_ptr -> scalar_knowns; 


    /* First Solve Element Information (This is for MODULEF short time expansion) */
    if(elemg != 1) {
      SystemAbort("MODULEF EXPANSION, elemg is assumed to be only one.");
    }

    solve_element_ptr = *(solve_ptr->solve_elem_dat + 0);




    /* The end of short time coding */


    /* MAKE FILE NAME */
    if(solve_no <1 || solve_no>99) {
      SystemAbort("solve no. Error (mf_make_solve_ctrl77)");
    }

    sprintf(fname,MF_FNAME_SOLVE_TAE,solve_no);
    fp = mfFileWriteOpen( fname , MF_FCODE_SOLVE_TAE);
    
    
    /* 01:SUBROUTINE STATEMENT */
    PUT(fp,"      subroutine ");
    PUT(fp,MF_NOM77_SOLVE_TAE,solve_no);    
    if(solve_no<10) F77(" ");
    PUT(fp,"(");

    F77("M");
    

    F77(",NFMAIL,NIMAIL,NTMAIL,\n");
    F77("     $                        NFCOOR,NICOOR,NTCOOR,\n");
    F77("     $                 IEMILI,NFMILI,NIMILI,NTMILI,\n");
    F77("     $                 IEFORC,NFFORC,NIFORC,NTFORC,\n");
    F77("     $\n");
    F77("     $                        NFTAE ,NITAE ,NTTAE  )\n");

    /* 02:Discription statement */
    mf_header(fp);

    /* DECLARE FOR NL arrays */
    F77("      PARAMETER    (MAXNL = 1)\n");
    mfCOM(fp);

    /* :SUPPER ARRAY */
    F77("      DIMENSION M(*)\n");
    mfCOM(fp);

    F77("      DIMENSION     IOPT(4)\n");
    F77("      DIMENSION     L1(MAXNL),L2(MAXNL)\n");
    mfCOM(fp);

    F77("      EXTERNAL      PNMASS,PNRAID,PNSECM,PNCNTR,FORCE,");
    if(known_variables != 0) {
      PUT(fp,MF_NOM77_MILIEU,solve_no);
    }
    else {
      F77("MILIEU");
    }
    F77("\n");

    mfCOMCOM(fp);
    F77("* MAKE TAE from MAIL/COOR/MILI/(FORC)\n");


    mfCOMCOM(fp);
    F77("C     PARAMETERS FOR THENEW\n");
    F77("C\n");
    F77("C     M:     SUPER ARRAY\n");
    F77("C\n");
    F77("C     NFMAIL UNIT  NUMBER OF THE MAIL DATABASE ( 0 IF STORED IN CORE)\n");
    F77("C     NIMAIL LEVEL NUMBER OF THE MAIL DATABASE\n");
    F77("C     NFCOOR UNIT  NUMBER OF THE COOR DATABASE ( 0 IF STORED IN CORE)\n");
    F77("C     NICOOR LEVEL NUMBER OF THE COOR DATABASE\n");
    F77("C\n");
    F77("C     IEMILI USE MILI OR NOT  (1 USE,  0 NOT USE)\n");
    F77("C     NFMILI UNIT  NUMBER OF THE MILI DATABASE ( 0 IF STORED IN CORE)\n");
    F77("C     NIMILI LEVEL NUMBER OF THE MILI DATABASE\n");
    F77("C\n");
    F77("C     IEFORC USE FORC OR NOT  (1 USE,  0 NOT USE)\n");
    F77("C     NFFORC UNIT  NUMBER OF THE FORC DATABASE ( 0 IF STORED IN CORE)\n");
    F77("C     NIFORC LEVEL NUMBER OF THE FORC DATABASE\n");
    F77("C \n");
    F77("C \n");
    F77("C \n");
    F77("C     IOPT   ARRAY CONTAINING OPTIONS FOR CALCULATING THE MASS\n");
    F77("C            MATRIX, STIFFNESS MATRIX, LOAD VECTOR, AND FLUXES\n");
    F77("C\n");
    F77("C            IOPT(1) =0 MASS MATRIX NOT EXIST     | =1    MASS MATRIX EXIST\n");
    F77("C            IOPT(2) =0 STIFFNESS MATRIX NOT EXIST| =1    EXIST\n");
    F77("C            IOPT(3) =0 NO SECOND MEMBER(LOAD VEC)| =NDSM NUMBER OF LOAD CASES\n");
    F77("C            IOPT(4) =0 NOT CALCULATE FLUX        | =1    CALCULATE FLUX\n");
    F77("C\n");
    F77("C     NL     NUMBER OF LINEAR COMBINATIONS OF THE MASS AND/OR STIFFNESS\n");
    F77("C            MATRICES\n");
    F77("C\n");
    F77("C     D1,D2  ARRAYS CONTAINING THE COEFFICIENTS OF THE I'TH\n");
    F77("C            LINEAR COMBINATION; USED ONLY WHEN NL IS NONZERO\n");
    F77("C\n");
    F77("C     NNTAE  NAME OF ARRAY TO BE ASSOCIATED WITH THE TAE.\n");
    F77("C            USED ONLY WHEN NL IS NONZERO\n");
    F77("C\n");

    F77("C     NPROV  INDICATES TYPE OF PROBLEM:  1 FOR THERMAL, 2 FOR ELASTICITY,...\n");
    F77("C\n");
    F77("C     NFPOBA DIRECT ACCESS FILE CONTAINING PRECOMPUTED INFORMATION \n");
    F77("C            FOR CERTAIN QUADRATURE RULES (NOT USED HERE)\n");
    F77("C\n");

    F77("C     NTHELA OPTION FOR THERMO-ELASTIC PROBLEMS\n");
    F77("C\n");
    F77("C     NFBO,NIBO     DATABASE CONTAINING INFORMATION ON INITIAL DEFORMATIONS\n");
    F77("C\n");
    F77("C     NFNDL1,NINDL1 DATABASE USED IF ALL THE NODES DO NOT HAVE \n");
    F77("C                   THE SAME DEGREES OF FREEDOM\n");
    F77("C\n");
    F77("C     NOMCOU        COLOR TABLE NAME FOR VECTOR PROCESSING\n");
    F77("C\n");
    F77("C     OUTPUT:\n");
    F77("C     -------\n");
    F77("C     TAE DATABASE (INTO TAE FILE)\n");
    F77("C------------------------------------------------------------------\n");



    F77("\n");
    F77("C NO MASS MATRIX HERE(=0)\n");
    F77("      IOPT(1) = 0\n");
    F77("C    STIFFNEXX MATRIX EXIST (CALL ONRAID)\n");
    F77("      IOPT(2) = 1\n");
    F77("C    LOAD CASE IS 1 (CALL ONSECM)\n");
    F77("      IOPT(3) = 1\n");
    F77("C    NOT CALCULATE FLUX = 0\n");
    F77("      IOPT(4) = 0\n");
    F77("\n");
    F77("* NUMBER OF LINEAR COMBINATION CONSTRAINT IN MASS/STIFFNESS MATRIX\n");
    F77("      NL      = 0\n");
    F77("*     L1,L2   NOT SET HERE,\n");
    F77("\n");
    F77("* NNTAE  (USED FOR LINEAR COMBINATIN CONSTRAINT)\n");
    F77("      NNTAE   = 0\n");
    F77("\n");
    F77("* NPROV   0: RESERVED (PERSONAL LIBRARY)\n");
    F77("*         1: THERMIQUE/SIMPLE PRECISION\n");
    F77("*         2: ELASTICITE/DOUBLE PRECISION\n");
    F77("*  == 1 REAL*4  otherwise  REAL*8\n");
    F77("*\n");
    F77("      NPROV   = 0\n");
    F77("\n");
    F77("* NFPOBA (Usable in ONMASS/ONRAID/ONSECM/ONCNTR)\n");
    F77("      NFPOBA  = 0\n");
    F77("\n");
    F77("* NTHELA(OPTION FOR THERMO-ELASTIC ELEMENT LIBRARIES)\n");
    F77("      NTHELA  = 0\n");
    F77("* BO DATA STRUCTURE(INITIAL DEFORMATION)  \n");
    F77("      NFBO    = 0\n");
    F77("      NIBO    = 0\n");
    F77("\n");
    F77("* NDL1 DATA STRUCTURE\n");
    F77("      NFNDL1  = 0\n");
    F77("      NINDL1  = 0\n");
    F77("\n");
    F77("* LVECT  LENGTH OF VECTORS (For vector processor machines cf. SX-5)\n");
    F77("* NOMCOU ARRAY NAME OF ELEMENT COLOR DATA ARRAY\n");
    F77("      LVECT   = 1\n");
    F77("      NOMCOU  = 0\n");
    F77("* ------------------------------------\n");
    F77("* CALL THENEW FOR MAKING TAE\n");
    F77("* ------------------------------------\n");
    F77("      CALL THENEW(M,M,M,\n");
    F77("     $                   NFMAIL,NIMAIL,\n");
    F77("     $                   NFCOOR,NICOOR,\n");
    F77("     $            IEMILI,NFMILI,NIMILI,\n");
    F77("     $            IEFORC,NFFORC,NIFORC,\n");
    F77("     $                   NFTAE ,NITAE ,NTTAE,\n");
    F77("     $            IOPT,\n");
    F77("     $            NL,L1,L2,\n");
    F77("     $            NNTAE, NPROV ,NFPOBA,\n");
    F77("     $            NTHELA,NFBO  ,NIBO,\n");
    F77("     $            NFNDL1,NINDL1,\n");
    F77("     $            LVECT ,NOMCOU,\n");
    F77("     $            PNMASS,PNRAID,PNSECM,PNCNTR,FORCE,");
    if(known_variables != 0) {
      PUT(fp,MF_NOM77_MILIEU,solve_no);
    }
    else {
      F77("MILIEU");
    }
    F77(")\n");

    F77("*\n");
    F77("      RETURN\n");
    F77("*\n");
    F77("      END\n");



    mfFileClose( fp );
    return;
    
}
