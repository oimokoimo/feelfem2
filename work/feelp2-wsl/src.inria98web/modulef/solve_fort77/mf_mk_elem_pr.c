/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_elem_pr.c
 *      Date:   1998/12/02
 *   
 *   Purpose:   make prs00X.f   element stiffness matrix calculation routine
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../solve_comp/solve_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_mk_elem_pr( solve_ptr , solve77_ptr)
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
    char *numtitle;
    
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
    numtitle = zerozeronum( solve_no );
    

    sprintf(fname,MF_FNAME_ELEM_PR,numtitle);
    fp = mfFileWriteOpen( fname , MF_FCODE_SOLVE_TAE);
    
    
    /* 01:SUBROUTINE STATEMENT */
    PUT(fp,"      subroutine ");
    PUT(fp,MF_NOM77_ELEM_PR,numtitle);    
    F77("(NOCAL,NOTELM,NOREF,\n");
    F77("     $                  MMAST,NTYTA,NINDI,NSTOC,\n");
    F77("     $                  X,Y,\n");
    F77("     $                  VOLUME,LVOLUM,\n");
    F77("     $                  SURFAC,LSURFA,\n");
    F77("     $                  ARETE ,LARETE,\n");
    F77("     $                  POINT ,LPOINT,\n");
    F77("     $                  AE                       )\n");

    /* 02:Discription statement */
    mf_header(fp);

    F77("*---------------------------------------------------------------------\n");
    F77("* PURPOSE\n");
    F77("*\n");
    F77("* When NOCAL = 1   Set element information\n");
    F77("*\n");
    F77("* 1)Specify real value precision by NTYTA\n");
    F77("* 2)Specify the size of element stiffness matrix by NMMAST\n");
    F77("*   CAUTION in words!!!\n");
    F77("* 3)Specify ??? by NINDI\n");
    F77("* 4)Specify Symmetric or Non-symmetric by NSTOC\n");
    F77("*\n");
    F77("* Optional:\n");
    F77("* 5)Specify allocation size for cofficient information MILIEU\n");
    F77("*           LVOLUM\n");
    F77("*           LSURFA\n");
    F77("*           LARETE\n");
    F77("*           LPOINT\n");
    F77("*\n");
    F77("* When NOCAL = 2   Calculate element stiffness matrix\n");
    F77("*                 (Includes Robbin type boundary integration contributes)\n");
    F77("*---------------------------------------------------------------------\n");
    F77("* INPUT PARAMETERS\n");
    F77("* ----------------\n");
    F77("*     NOCAL   SET TO 1 ON THE FIRST CALL,  2 ON THE SECOND\n");
    F77("*     NOTELM  OPTIONS FOR COEFFICIENT EVALUATION\n");
    F77("*     X(*)    ARRAY CONTAINING THE X-COORDINATES OF THE NODES OF TRI\n");
    F77("*     Y(*)    ARRAY CONTAINING THE Y-COORDINATES OF THE NODES OF TRI\n");
    F77("*\n");
    F77("*     SUR(*)  ARRAY CONTAINING COEFFICIENT INFORMATION for SURFACE\n");
    F77("*     LSUR    SIZE OF SUR\n");
    F77("*  \n");
    F77("*\n");
    F77("*     NDSDE   NUMBER OF THE SUBDOMAIN CONTAING THE ELEMENT\n");
    F77("*    \n");
    F77("* OUTPUT PARAMETERS\n");
    F77("* -----------------\n");
    F77("*     NMMAST  LENGTH IN WORDS OF THE OUTPUT ARRAY AE\n");
    F77("*     NSTOC   TYPE OF STORAGE USED IN THE OUTPUT ARRAY AE\n");
    F77("*            (-1: nonsym  0:diag  1:sym)\n");
    F77("*\n");
    F77("*| OUTPUT PARAMETERS FOR NOCAL=1\n");
    F77("*| -----------------------------\n");
    F77("*| NTYTA  TYPE OF THE OUTPUT ARRAY AE\n");
    F77("*| NINDI  NUMBER OF INDICES IN THE OUTPUT ARRAY AE\n");
    F77("*| LSUR   LENGTH IN WORDS OF THE INPUT ARRAY SUR\n");
    F77("*|\n");
    F77("*| OUTPUT PARAMETERS FOR NOCAL=2\n");
    F77("*| -----------------------------\n");
    F77("*| AE     THE ELEMENTARY STIFFNESS MATRIX\n");
    F77("*|\n");
    F77("*------------------------------------------------------------------\n");

    F77("      REAL*4 X(*),Y(*)\n");
    F77("      REAL*8 VOLUME(*),SURFAC(*),ARETE(*),POINT(*)\n");
    F77("      READ*8 AE(*)\n");
    mfCOM(fp);

    



    F77("      RETURN\n");
    F77("      END\n");


    mfFileClose( fp );
    return;
    
}
