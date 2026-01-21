/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_element_ordering.c
 *      Date:   1997/06/06
 *   
 *   Purpose:   make element ordering array
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>

#include "edat.h"


void make_element_ordering(bamg_edat,edge_2d_ptr,ordering,result_ordering)
     FEM_edat *bamg_edat;
     EDGE_2d  *edge_2d_ptr;
     int      *ordering;            /* work array         */
     int      *result_ordering;     /* result of ordering */
{
  int i,j,k;
  int npmax,ne,nx,np;
  int *ielem;
  int ssno          ;  /* starting node       */

  int eno,nno;         /* general use of element no, node no */
  int current_eno;  


  double *x,*y;
  double  xmin,ymin;

  int max_ne_pn;
  int *ne_pn;
  int *eno_en;


  int *e_stack,estacks;
  int *n_stack,nstacks;



  /* Set fundamental data */
  npmax = bamg_edat->npmax;
  ne    = bamg_edat->ne;
  np    = bamg_edat->np;
  nx    = bamg_edat->nx;
  ielem = bamg_edat->ielem;

  x     = bamg_edat->x;
  y     = bamg_edat->y;

  max_ne_pn = edge_2d_ptr->max_ne_pn;
  ne_pn     = edge_2d_ptr->ne_pn;
  eno_en    = edge_2d_ptr->eno_en;

#ifndef MSDOS
#ifdef DBG
  if(DBG) dbg_xplot_init(bamg_edat);
#endif
#endif
  

  /* search left bottom point for starting point */
  ssno = 1;
  xmin = *(x+(ssno-1)); ymin = *(y + (ssno-1));
  
  for(i=1;i<npmax;i++) {
    if(xmin >= *(x+i) && ymin >= *(y+i)) {
      ssno = i+1;
      xmin = *(x+i);
      ymin = *(y+i);
    }
  }

  /* initialize ordering array */
  for(i=0;i<ne;i++) {
    *(ordering+i) = 0;
  }

  eno = *(eno_en + (ssno-1));
  current_eno =0;

  /* prepare work array */
  e_stack = (int *)malloc(sizeof(int)*ne);
  if(e_stack == NULL) {
    fprintf(stderr,"cannot allocate already\n");
    exit(1);
  }

  n_stack = (int *)malloc(sizeof(int)*npmax);
  if(n_stack == NULL) {
    fprintf(stderr,"cannot allocate work\n");
    exit(1);
  }
  


  /* LOOP INITIALIZATION */
  *n_stack    = ssno;
  nstacks     = 1;
  current_eno = 0;
  

  /* make ordering */
  while(current_eno != ne) {

    /* make e_stack from n_stack  */
    estacks = 0;
    for(i=0;i<nstacks;i++) {

      nno = *(n_stack + i);
      
      for(j=0;j<*(ne_pn + (nno -1));j++) {
	eno = *(eno_en  + (nno-1)*max_ne_pn+j);
	if(*(ordering+(eno-1)) == 0) {
	  
	  /* if not numbered, put on the e_stack, but no duplication */
	  for(k=0;k<estacks;k++) {
	    if(eno == *(e_stack+k)) {
	      eno = -1;
	      break;
	    }
	  }
	  if(eno != -1) {
	    *(e_stack+estacks) = eno;
	    estacks++;
	  }
	}
      }
    }

    /* enumerate e_stacked element */
    for(i=0;i<estacks;i++) {
      eno = *(e_stack+i);
      current_eno++;

#ifndef MSDOS
#ifdef DBG
      if(DBG) dbg_xplot_draw_elem_no(bamg_edat,eno,current_eno);
#endif
#endif

      *(ordering+(eno-1)) = current_eno;
    }

    /* make_nstack from pushed estack */
    nstacks = 0;
    for(i=0;i<estacks;i++) {
      
      eno = *(e_stack+i);

      for(j=0;j<np;j++) {
	nno = *(ielem + (eno-1)*nx+j);

	for(k=0;k<nstacks;k++) {
	  if(*(n_stack+k) == nno) {
	    nno = -1;
	    break;
	  }
	}

	if(nno != -1) {
	  *(n_stack+nstacks) = nno;
	  nstacks++;
	}
      }
    }
  }

#ifndef MSDOS
#ifdef DBG
  if(DBG) xwait();
#endif
#endif


  /* make result_ordering array */
  for(i=0;i<ne;i++) {
    *(result_ordering + *(ordering+i)-1) = i+1;
  }

  { /* THIS IS NEW FOR METIS Metis metis! */
    FILE *mfp;
    mfp = fopen("metis.feel","w");
    if(mfp==NULL) {
       fprintf(stderr,"feel.bamg.exe:Cannot open metis.feel to write.\n");
       exit(1);
    }
    for(i=0;i<ne;i++) {
      fprintf(mfp,"%d\n",*(ordering+i));
    }
    fclose(mfp);
  }


  return;
}
