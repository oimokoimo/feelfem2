/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_mk_milieu.c
 *      Date:   1998/12/16
 *   
 *   Purpose:   make milieu routine
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../solve_comp/solve_comp.h"
#include "../../var_comp/var_comp.h"
#include "../../mesh_comp/mesh_comp.h"   /* for get domain name */

#include "../modulef_def/modulef_def.h"


void mf_mk_milieu( solve_ptr , solve77_ptr)
     Solve       *solve_ptr;
     SolveFORT77 *solve77_ptr;
{
  int i,j;
  int flag;
    
  int solve_no;
    
  int elemg;            /* Element groups */
  int solve_elements;   /* Number of solve elements */
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

  Var  *var_ptr;
  char *var_name;
  char *domain_name;
  int   freedom,B_niveau;
    
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

  if(known_variables == 0) return;  /* DO NOTHING IN CASE OF NO KNOWN VARIABLES */

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

  sprintf(fname,MF_FNAME_MILIEU,solve_no);
  fp = mfFileWriteOpen( fname , MF_FCODE_MILIEU);
    
    
  /* 01:SUBROUTINE STATEMENT */
  PUT(fp,"      subroutine ");
  PUT(fp,MF_NOM77_MILIEU,solve_no);    
  if(solve_no<10) F77(" ");
  PUT(fp,"(");

  F77("M,LOPT,X,NDIM,NPO,TAR,LTAR,LV,IADR,I1,NARE,IA)\n");
  mf_header(fp);
  F77("*\n");
  F77("*  MILIEU is a subroutine to calculate parameters for the calculation\n");
  F77("*  of element-mass matrix and element-stiffness matrix.\n");
  F77("*  Before going to the calculation routine of each element, this MILIEU\n");
  F77("*  will be called several times if necessary.  To call MILIEU or not\n");
  F77("*  for each individual element is judged by its reference number or\n");
  F77("*  sub-domain number. It may be called several times for each element\n");
  F77("*  in SURF,ARET,POI(3D) and ARET,POI(2D) according to its reference\n"); 
  F77("*  number.  This information is stored in MILI data structure.  And\n");
  F77("*  in the case of VOLUME in 3D and SURFACE in 2D, MILIEU is called\n");
  F77("*  only once at most, depending on the sub-domain number.\n");
  F77("*\n");
  F77("** Input parameters\n");
  F77("** ----------------\n");
  F77("* M     : Super array\n");
  F77("*\n");
  F77("* LOPT  : Identification parameter passed to MILIEU subroutine.\n");
  F77("*         Correspondence between LOPT and reference number (or \n");
  F77("*         sub-domain No.) defined in MILI data structure, 'INFO1'\n");
  F77("*         (6th of MIL3,MIL4,...,MILA)\n");
  F77("*\n");
  F77("* X     : Coordinate table X(LVECT,NPO,NDIM) local element coordinate\n");
  F77("*\n");
  F77("* NDIM  : Space dimension\n");
  F77("* NPO   : Number of points in the element\n");
  F77("*\n");
  F77("* TAR   : Array for value to pass element calculation routine, see LTAR also\n");
  F77("*\n");    
  F77("* LTAR  : Array size of TAR in words.  ALLOCATION SIZE IS **SPECIFIED**\n");
  F77("*         in element caluculation routine. (at the option NOCAL=1)\n");
  F77("*         In ther/thraid.f, for example, their name for allocation\n");
  F77("*         size is LVOLUM,LSURFA,LARETE,LPOINT for MASS and STIFFNESS\n");
  F77("*         matrix.\n");
  F77("*         The size specified there is the size of only ONE component.\n");
  F77("*         Especially for edges, points, and for surfaces in 3D case,\n");
  F77("*         Modulef library allocates the memory for all edges, points, \n");
  F77("*         surfaces. That is to say, to specify LARETE words means \n");
  F77("*         to allocate ARETE(LARETE,NumberOfEdges).\n");
  F77("*\n");
  F77("*         LVOLUF,LSURFF,LARETF,LPOINF is the size for calculating second\n");
  F77("*         member in SECM routines, used in FORCE subroutine families.\n");
  F77("*\n");
  F77("* LV    : Length of vector when vector processing (usually its name is LVECT)\n");
  F77("*\n");
  F77("* IADR  : Defined in MILI data structure, 'INFO2' (7th of MIL3,MIL4,...,MILA\n");
  F77("*         This is used for .....?\n");
  F77("*\n");
  F77("* I1    : Pointer in TAR (Generally 0 and not used)\n");
  F77("*\n");
  F77("* NARE  : Local SURFACE number(3D only), EDGE number, POINT number\n");
  F77("*         When the calculation of MILIEU is just one of a geometrical\n");
  F77("*         component of an element. (For example, one edge in triangle,\n");
  F77("*         one surface in tetrahydron,) MILIEU may be called for\n");
  F77("*         several times with regards to its surface, edge, or point\n");
  F77("*         reference number.  This NARE has its local numbering of the\n");
  F77("*         component in the element to indicate which part of element to\n");
  F77("*         calculate.\n");
  F77("*\n");
  F77("* IA    : Pointer in super array M(*), locates the actual element entry\n");
  F77("*         address in MAIL(MAI1,MAI2,...,MAIL<-) of the MAIL data structure.\n");
  F77("*         So, M(IA+1) = the element number NEL, M(IA+2) = the element type NTYE,\n");
  F77("*         M(IA+3) = NMAE,  see the description document MAIL data structure.\n");
  mfCOMCOM(fp);

  /* declarations */
  F77("      dimension M(*)\n");
  F77("      real*8    TAR(*)\n");

  F77("      data IVDEJA/ 0 /\n");
  
  F77("*\n");

  /* Save Pointer variables */
  for(i=0;i<solve_element_ptr->fem_knowns;i++) {
    var_name   = *(solve_element_ptr-> fem_known_name + i);
    PUT(fp,"      save NP_%s\n",var_name);
  }
  for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
    var_name   = *(solve_element_ptr-> ewise_known_name + i);
    PUT(fp,"      save NP_%s\n",var_name);
  }

  mfCOMCOM(fp);

  F77("      if(IVDEJA .EQ. 0) then\n");
  F77("*\n");
  F77("* Retrive Pointers in super array for each known variables\n");
  F77("*\n");
  F77("        IVDEJA = 1\n");


  /* retrive known fem variables */
  if(solve_element_ptr->fem_knowns >0) {
    F77("* FEM   variable B structure\n");
  }
  for(i=0;i<solve_element_ptr->fem_knowns;i++) {
    var_name   = *(solve_element_ptr-> fem_known_name + i);
    domain_name=   get_domain_name_by_no( 0 );
    freedom    =   get_fem_var_freedom_by_ND(var_name, domain_name);
    var_ptr    =   get_var_ptr_by_name( var_name ); /* modulef extension func*/

    B_niveau   =   var_ptr->DS_B_niv;
    
    /* restore known fem variable (stored in B data structure) */
    PUT(fp,"        NIVB_%s=%d\n",var_name,B_niveau);
    PUT(fp,"        NP_%s  =0\n",var_name);
  }


  /* retrive known ewise variable */

  if(solve_element_ptr->ewise_knowns >0) {
    F77("* EWISE variable B structure\n");
  }
  for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
    var_name = *(solve_element_ptr-> ewise_known_name + i);    
    var_ptr  =   get_var_ptr_by_name( var_name ); /* modulef extension func*/
    
    B_niveau   =   var_ptr->DS_B_niv;
    
    /* restore known fem variable (stored in B data structure) */
    PUT(fp,"        NIVB_%s=%d\n",var_name,B_niveau);
    PUT(fp,"        NP_%s  =0\n",var_name);
  }
  F77("*\n");
  F77("      endif\n");

  /*  */

  F77("      RETURN\n");
  F77("*\n");
  F77("      END\n");
  
  mfFileClose( fp );
  return;
}


