/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_make_scheme_femalloc.c
 *      Date:   1998/12/14
 *   
 *   Purpose:   Generation of allocation statements for fem variables
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../var_comp/var_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_make_scheme_ewisealloc(fp)
     FILE *fp;
{
  int i;
  int ewise_vars;

  Var *var_ptr;
  int  niveau;

  ewise_vars = how_many_ewise_vars();


  F77("*--------------------------------------------------\n");
  F77("* Allocate EWISE variables in Data Structure 'B'\n");
  F77("*--------------------------------------------------\n");


  for(i=0;i<ewise_vars;i++) {

    /* LIMITATION MODULEF */
    
    var_ptr = get_nth_ewise_ptr(i);

    niveau            = get_new_B_niv();
    var_ptr->DS_B_niv = niveau;                 /* Modulef B level set here */
    
    PUT(fp,"      NIVB_%s = %d\n",var_ptr->name,niveau);
  }
  
  mfCOM(fp);

  if(ewise_vars == 0) {
    F77("*  No ewise variables\n");
    mfCOM(fp);
    return;
  }

    
  for(i=0;i<ewise_vars;i++) {

    /* LIMITATION MODULEF */
    
    var_ptr = get_nth_fem_ptr(i);
    
    PUT(fp,"      CALL ALLOCEWISEV(M, NTYP, NIVB_%s,\n",var_ptr->name);
    PUT(fp,"     $                 NFNOPO%d, NINOPO%d, M(NP_WKE%d), M(NP_WKE%d))\n",
	1,1,1,1);   /* LIMITATION   1 must be variable for nopo number */
  }
  
  mfCOMCOM(fp);

  return;
}
