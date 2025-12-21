/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_make_solve_ctrl77.c
 *      Date:   1998/12/01
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../solve_comp/solve_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_make_solve_ctrl77( solve_ptr , solve77_ptr)
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
   
    if(solve_no <1 || solve_no>99) {
      SystemAbort("solve no. Error (mf_make_solve_ctrl77)");
    }


    sprintf(fname,MF_FNAME_SOLVE,solve_no);
    fp = mfFileWriteOpen( fname , MF_FCODE_SOLVE);
    
    
    /* 01:SUBROUTINE STATEMENT */
    PUT(fp,"      subroutine ");
    PUT(fp,MF_NOM77_SOLVE,solve_no);    
    if(solve_no<10) F77(" ");
    PUT(fp,"(");

    F77("M");
    

    F77(",NFNOPO,NINOPO,NTNOPO,\n");
    F77("     $                     NFMAIL,NIMAIL,NTMAIL,\n");
    F77("     $                     NFCOOR,NICOOR,NTCOOR )\n");

    /* 02:Discription statement */
    mf_header(fp);


    /* 03:SUPPER ARRAY */
    F77("      dimension M(*)\n");
    mfCOMCOM(fp);

    F77("*--------------------------------------------\n");
    F77("* Set Unit/Level for MAIL/COOR data structure\n");
    F77("*--------------------------------------------\n");

    F77("      NFMAIL = 11\n");
    PUT(fp,"      NIMAIL = %d\n",solve_no);

    F77("      NFCOOR = 12\n");
    PUT(fp,"      NICOOR = %d\n",solve_no);

    F77("*------------\n");
    F77("C Set in core\n");
    F77("*------------\n");
    F77("      NFMAIL = 0\n");
    F77("      NFCOOR = 0\n");
    mfCOM(fp);
    F77("     IF(NFMAIL .NE. 0) THEN\n");
    F77("         call TRUNIT(NFMAIL)\n");
    F77("         call OUVRIR(NFMAIL,'feel1.MAIL','UNFORMATTED,UNKNOWN',0,IOSTAT)\n");
    F77("         if(IOSTAT .NE. 0) stop 'CANNOT CREATE MAIL FILE'\n");
    F77("      ENDIF\n");
    F77("*\n");
    F77("      IF(NFCOOR.NE.0) then\n");
    F77("         call TRUNIT(NFCOOR)\n");
    F77("         call OUVRIR(NFCOOR,'feel1.COOR','UNFORMATTED,UNKNOWN',0,IOSTAT)\n");
    F77("         if(IOSTAT .NE. 0) stop 'CANNOT CREATE COOR FILE'\n");
    F77("      ENDIF\n");

    /* NFMILI, NFFORC */
    F77("*---------------------------------------------------------\n");
    F77("* Set Usage flag/Unit/Level for MILI\n");
    F77("*---------------------------------------------------------\n");
    if(known_variables == 0) {
      F77("      IEMILI = 0\n");
    }
    else {
      F77("      IEMILI = 1\n");
    }
    F77("      NFMILI = 0\n");
    PUT(fp,"      NIMILI = %d\n",solve_no);
    F77("      NTMILI = 0\n");
    F77("\n");
    F77("      IF(IEMILI .NE. 0 .AND. NFMILI .NE. 0) then\n");
    F77("         call trunit(NFMILI)\n");
    F77("         call OUVRIR(NFMILI,'feel1.MILI','UNFORMATTED,UNKNOWN',0,IOSTAT)\n");
    F77("      endif\n");


    F77("*---------------------------------------------------------\n");
    F77("* Set Usage flag/Unit/Leve for FORC\n");
    F77("*---------------------------------------------------------\n");
    F77("      IEFORC = 0\n");
    F77("      NFFORC = 0\n");
    PUT(fp,"      NIFORC = %d\n",solve_no);
    F77("      NTFORC = 0\n");
    F77("\n");
    F77("      IF(IEFORC.NE.0  .AND. NFFORC .NE. 0) then\n");
    F77("         call trunit(NFFORC)\n");
    F77("         call OUVRIR(NFFORC,'feel1.FORC','UNFORMATTED,UNKNOWN',0,IOSTAT)\n");
    F77("      endif\n");


    F77("*---------------------------------------------------------\n");
    F77("* Set Unit/Leve for TAE\n");
    F77("*---------------------------------------------------------\n");
    F77("      call TRUNIT(NFTAE)\n");
    F77("      call OUVRIR(NFTAE,'");
    PUT(fp,MF_FNAME_FEELTAE,solve_no);
    F77("','UNFORMATTED,UNKNOWN',0,IOSTAT)\n");
    F77("      if(IOSTAT .NE. 0) STOP 'CANNOT CREATE TAE FILE'\n");
    F77("\n");
    PUT(fp,"      NITAE   = %d\n",solve_no);
    F77("      NTTAE   = 0\n");
    F77("\n");


    /* CALL COMACO */
    F77("*-----------------------------------------\n");
    F77("*-----------------------------------------\n");
    F77("* CALL COMACO ROUTINE\n");
    F77("*-----------------------------------------\n");
    PUT(fp,"      CALL SOLVE%dMACO",solve_no);
    if(solve_no<10) F77(" ");    F77("(M,NFNOPO,NINOPO,NTNOPO,\n");
    F77(   "     $\n");
    F77(   "     $                   NFMAIL,NIMAIL,NTMAIL,\n");
    F77(   "     $                   NFCOOR,NICOOR,NTCOOR)\n");
    F77("\n");


    
    /* CALL COMILI */
    F77("*-----------------------------------------\n");
    F77("* CALL COMILI ROUTINE\n");
    F77("*-----------------------------------------\n");
    PUT(fp,"      CALL SOLVE%dMILI",solve_no);
    if(solve_no<10) F77(" ");    F77("(M,IEMILI,NFMILI,NIMILI,NTMILI)\n");
    F77("\n");



    /* CALL COFORC */
    F77("*-----------------------------------------\n");
    F77("* CALL COFORC ROUTINE (Now not used)\n");
    F77("*-----------------------------------------\n");
    PUT(fp,"      CALL SOLVE%dFORC",solve_no);
    if(solve_no<10) F77(" ");    F77("(M,IEFORC,NFFORC,NIFORC,NTFORC)\n");
    F77("\n");



    /* 06:CALL TAE  */
    F77("*-----------------------------------------\n");
    F77("* CALL COTAE ROUTINE \n");
    F77("*-----------------------------------------\n");
    PUT(fp,"      CALL SOLVE%dTAE ",solve_no);
    if(solve_no<10) F77(" ");F77("(M,NFMAIL,NIMAIL,NTMAIL,\n");
    F77(   "     $                   NFCOOR,NICOOR,NTCOOR,\n");
    F77(   "     $            IEMILI,NFMILI,NIMILI,NTMILI,\n");
    F77(   "     $            IEFORC,NFFORC,NIFORC,NTFORC,\n");
    F77(   "     $\n");
    F77(   "     $                   NFTAE ,NITAE ,NTTAE  )\n");
    F77("\n");


    /* 07:CALL BDCL */
    F77("*-----------------------------------------\n");
    F77("* CALL COBDCL ROUTINE \n");
    F77("*-----------------------------------------\n");
    PUT(fp,"      CALL SOLVE%dBDCL",solve_no);
    if(solve_no<10) F77(" ");F77("(M,NFMAIL,NIMAIL,NTMAIL,\n");
    F77(   "     $                   NFCOOR,NICOOR,NTCOOR,\n");
    F77(   "     $\n");
    F77(   "     $                   NFBDCL,NIBDCL,NTBDCL )\n");
    mfCOMCOM(fp);


    /*   :CALL MUA  */
    

    F77(" madadayonn mua ikou\n");


    
    /* RETURN;END; */
    F77("      RETURN\n");
    F77("      END\n");

    mfFileClose( fp );
    return;
    
}

