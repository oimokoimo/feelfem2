/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_solve_maco.c
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
#include "../../mesh_comp/mesh_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_mk_solve_maco( solve_ptr , solve77_ptr)
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
      SystemAbort("solve no. Error (mf_make_solve_ctrl77)");
    }

    sprintf(fname,MF_FNAME_SOLVE_MACO,solve_no);
    fp = mfFileWriteOpen( fname , MF_FCODE_SOLVE_MACO);
    
    
    /* 01:SUBROUTINE STATEMENT */
    PUT(fp,"      subroutine ");
    PUT(fp,MF_NOM77_SOLVE_MACO,solve_no);    
    if(solve_no<10) F77(" ");
    PUT(fp,"(");

    F77("M");
    

    F77(",NFNOPO,NINOPO,NTNOPO,\n");
    F77("     $                         NFMAIL,NIMAIL,NTMAIL,\n");
    F77("     $                         NFCOOR,NICOOR,NTCOOR )\n");

    /* 02:Discription statement */
    mf_header(fp);

    /* DECLARE MAXSBD */
    F77("      PARAMETER    (MAXSBD = 10)\n");
    mfCOM(fp);

    /* :SUPPER ARRAY */
    F77("      dimension M(*)\n");
    mfCOMCOM(fp);

    F77("      DIMENSION     ICODEL(4*MAXSBD)\n");
    F77("      DIMENSION     NOSDC(1),NONSC(1),NONFC(1)\n");
    mfCOM(fp);

    F77("      LOGICAL       FONINT\n");
    F77("      EXTERNAL      FFRONT\n");
    mfCOMCOM(fp);
    F77("* Purpose: This subroutine generates MAIL and COOR data structure\n");
    F77("*          from NOPO data and element library specified in this\n");
    F77("*          subroutine (ICODEL) by calling COMACO routine.\n");
    F77("*\n");


    F77("* PARAMETERS FOR COMACO ROUTINE\n");
    F77("*\n");

    F77("* NDIM   : SPACE DIMENSION\n");
    F77("* NDSD   : Total number of sub domains\n");
    F77("*\n");

    F77("* NBSDC  : Number of curbed subdomains (array size of NOSDC)\n");
    F77("* NOSDC  : Curbed subdomain list array\n");
    F77("*\n");

    F77("* NNR    : The total number of references(When NOT use NOPO)\n");
    F77("*\n");

    F77("* NBNSC  : Number of curbed surface (Array size of NONSC)\n");
    F77("* NONSC  : Curbed surface list array\n");
    F77("*\n");

    F77("* NBNFC  : Number of curbed edges (Array size of NONFC)\n");
    F77("* NONFC  : Curbed edge list array\n");
    F77("*\n");


    F77("* IELECA : if == 0 to call element library\n");
    F77("*             >= 1 by data card\n");
    F77("*\n");

    
    F77("* NOMBIB : INTEGER*4 format of library cathegory, here =ICHAR4('PERS')\n");
    F77("*\n");


    F77("* ICODEL : Array describing the element to use for each subdomain\n");
    F77("*          ** This array contains the number of different types of\n");
    F77("*          ** straight elements and for each its name, followed\n");
    F77("*          ** by the number of different types of curved elements\n");
    F77("*          ** and for each name (if curved element used)\n");
    F77("*\n");
    F77("*          for each subdomain,\n");
    F77("*            number of straight elements\n");
    F77("*             Its names(2 words) loop of above number\n");
    F77("*            number of curved element\n");
    F77("*             Its names(2 words) loop of above number\n");
    F77("*\n");
    F77("*          Each subdomains, the number of each geometric type\n");
    F77("*          must be only one.  2 strainght element, say, TRIA and\n");
    F77("*          RECT, is possible, but not two different TRIAs\n");
    F77("*\n");

    
    F77("* NOPOEX : 0 data by card  >0 by NOPO D.S. (NOPO Existence flag)\n");
    F77("*\n");


    F77("* NFNOPO : NOPO Data structure Unit No. if 0 in core\n");
    F77("* NINOPO : NOPO Data structure level number.\n");
    F77("* NFMAIL : MAIL Data structure Unit No. if 0 in core\n");
    F77("* NIMAIL : MAIL Data structure level number (here same as solve statement No.)\n");
    F77("* NTMAIL : Number of arrays associated with MAIL data structure\n");
    F77("*\n");

    F77("* NOPTFI :(Old parameter to save memory, not use now)\n");
    F77("*\n");

    F77("* NFCOOR : COOR Data structure Unit No. if 0 in core\n");
    F77("* NICOOR : COOR Data structure level number (here same as solve statement No.)\n");
    F77("* NTCOOR : Number of arrays associated with COOR data structure\n");
    F77("*\n");


    F77("* NPACD  : OLD PARAMETER(V.85) NOT USED In this version\n");
    F77("*\n");


    F77("* NDCSMC : If use paging in COO4, the length of page, otherwise big num\n");
    F77("*\n");


    F77("* FONINT : .TRUE. if use function interapter, otherwise .FALSE.\n");
    F77("* FFRONT : External function name for COMACO\n");
    F77("* \n");
    mfCOMCOM(fp);

    
    F77("      NDIM     = 2\n");
    F77("*\n");

    PUT(fp,"      NDSD   = %d\n",regions_in_domain);
    F77("      IF(NDSD .GT. MAXSBD) STOP 'CHANGE PARAMETER STATEMENT FOR MAXSBD'\n");
    F77("*\n");

    F77("      NBSDC    = 0\n");
    F77("      NOSDC(1) = 0\n");
    F77("*\n");

    F77("*NNR NOT USE NOW\n");
    F77("      NNR      = 0\n");
    F77("*\n");

    F77("      NBNSC    = 0\n");
    F77("      NONSC(1) = 0\n");
    F77("*\n");

    F77("      NBNFC    = 0\n");
    F77("      NONFC(1) = 0\n");
    F77("*\n");

    F77("      IELECA   = 0\n");              /* always 0, because always call 
    F77("*\n");
					         element library            */

    F77("      NOMBIB   = ICHAR4('PERS')\n"); /* always PERS, as feel personal
						 element library */

    F77("*\n");
    F77("* LIMITED USE OF COMACO here\n");
    F77("* (only one straight element of only one geometric element type)\n");
    F77("* (and each subdomain has the same element)\n");
    F77("*\n");
    F77("      NELEMS_STRAIGHT = 1\n");
    F77("      NELEMS_CURVE    = 0\n");
    F77("      NWORDS_SUBDOM   = 1 + 1 + NELEMS_STRAIGHT*2 + NELEMS_CURVE*2\n");
    F77("      IF(NWORDS_SUBDOM*NDSD .GT. MAXSBD*4) STOP 'ICODEL TOO SHORT'\n");
    

    F77("      DO 20 I=1,NDSD\n");
    F77("       ICODEL(NWORDS_SUBDOM*(I-1)+1) = NELEMS_STRAIGHT\n");

    if(solve_element_ptr -> etype == TRI) {
      F77("       ICODEL(NWORDS_SUBDOM*(I-1)+2) = ICHAR4('TRIA')\n");
    }
    else {
      F77("       ICODEL(NWORDS_SUBDOM*(I-1)+2) = ICHAR4('QUAD')\n");
    }

    F77("       ICODEL(NWORDS_SUBDOM*(I-1)+3) = ICHAR4('S0");
    
    if(solve_no < 10) {
      PUT(fp,"0%d",solve_no);
    }
    else {
      PUT(fp,"%d",solve_no);
    }
    F77("')\n");

    F77("       ICODEL(NWORDS_SUBDOM*(I-1)+1+2*NELEMS_STRAIGHT+1)=NELEMS_CURVE\n");
    F77(" 20   CONTINUE\n");
    F77("*\n");



    F77("      NOPOEX = 1\n");            /* always 1, because always call element library */
    
    F77("* NOPTFI,NPACD not used in this version\n");
    F77("      NOPTFI = 0\n");            /* set 0 in COMAC2 */
    F77("      NPACD  = 0\n");            /* set 0 in COMAC2 */
    F77("      NDCSMC = 1000000\n");      /* Big number! if use paging in COO4, page length */

    F77("*\n");
    F77("      FONINT = .FALSE.\n");
    F77("*     FFRONT =\n");
    mfCOM(fp);

    mfCOMCOM(fp);
    F77("* CALL COMACO to make MAIL and COOR data structure\n");
    mfCOMCOM(fp);
    F77("      CALL COMACO(M,NDIM,  NDSD,  NBSDC, NOSDC, NNR,   NBNSC, NONSC,\n"); 
    F77("     $              NBNFC, NONFC, IELECA,NOMBIB,ICODEL,NOPOEX,\n"); 
    F77("     $              NFNOPO,NINOPO,NFMAIL,NIMAIL,NTMAIL,NOPTFI,\n");
    F77("     $              NFCOOR,NICOOR,NTCOOR,NPACD, NDCSMC,FONINT,FFRONT)\n");
    mfCOMCOM(fp);


    F77("      RETURN\n");
    F77("      END\n");


    mfFileClose( fp );
    return;
    
}
