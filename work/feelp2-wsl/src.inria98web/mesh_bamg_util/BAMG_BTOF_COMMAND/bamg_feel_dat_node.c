/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   bamg_feel_dat_node.c
 *      Date:   1997/06/13
 *   
 *   Purpose:   make feel_dat in NODE
 *   Functions: 
 *              
 *              
 */
#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "edat.h"

void  bamg_feel_dat_node(fp,edat_ptr)
     FILE *fp;
     FEM_edat *edat_ptr;
{
  int i;

  int npmax;

  npmax = edat_ptr->npmax;


  fprintf(fp,"%s\n",KEY_NODE_REAL);

  
  for(i=0;i<npmax;i++) {
    fprintf(fp,"%8d",i+1);
#ifdef MSDOS
    fprintf(fp,"%12.4e%12.4e",*(edat_ptr->x+i),*(edat_ptr->y+i));
#else
    fprintf(fp,"%12.5e%12.5e",*(edat_ptr->x+i),*(edat_ptr->y+i));
#endif
    fprintf(fp,"%8d\n",*(edat_ptr->type+i));
  }


  fprintf(fp,"%8d\n",0);

  return;
}


	    
