/*
 *   feel p3  Finite Element Equation Language Prototype Version 3
 *            ~      ~       ~        ~
 *   MODULEF EXTENTION
 *
 *      File:   mf_make_scheme_femalloc.c
 *      Date:   1998/12/14
 *   
 *   Purpose:   Generation of allocation statements for fem variables
 *   Functions: set DS_B_niv in Var structure here
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#include "../../var_comp/var_comp.h"

#include "../modulef_def/modulef_def.h"


void mf_make_scheme_femalloc(fp)
     FILE *fp;
{
  int i;
  int fem_vars;

  Var *var_ptr;

  int  niveau;

  fem_vars = how_many_fem_vars();


  F77("*--------------------------------------------------\n");
  F77("* Allocate FEM variables in Data Structure 'B'\n");
  F77("*--------------------------------------------------\n");


  for(i=0;i<fem_vars;i++) {

    /* LIMITATION MODULEF */
    
    var_ptr = get_nth_fem_ptr(i);
    
    niveau            = get_new_B_niv();
    var_ptr->DS_B_niv = niveau;                 /* Modulef B level set here */

    PUT(fp,"      NIVB_%s = %d\n",var_ptr->name,niveau);
  }
  
  mfCOM(fp);
    
  for(i=0;i<fem_vars;i++) {

    /* LIMITATION MODULEF */
    
    var_ptr = get_nth_fem_ptr(i);
    
    PUT(fp,"      CALL ALLOCFEMV(M, NTYP, NIVB_%s,\n",var_ptr->name);
    PUT(fp,"     $               NFNOPO%d, NINOPO%d, M(NP_WKP%d), M(NP_WKP%d))\n",
	1,1,1,1);   /* LIMITATION   1 must be variable for nopo number */
  }
  
  mfCOMCOM(fp);

  return;
}
