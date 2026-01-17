/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   bamg_feel_dat_region_edat.c
 *      Date:   1997/06/13
 *      Modified: 1998/07/17   webextention
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */
#include <stdio.h>
#include "../../feel_def/feel_def.h"

#include "edat.h"

extern int etype_WEBEXTENSION;     /* web extension */

void   bamg_feel_dat_region_edat(fp,edat_ptr,
				 edats,
				 use_edge_ps,use_edge_no,
				 use_inner_ps,use_inner_no)
     FILE     *fp;
     FEM_edat *edat_ptr;
     int       edats;

     int use_edge_ps[MAX_EDATSET];
     int use_edge_no [MAX_EDATSET][MAX_MID_POINTS];
     int use_inner_ps[MAX_EDATSET];
     int use_inner_no[MAX_EDATSET][MAX_MID_POINTS];
     
{
  int  i,j,k,l;
  int  shape;
  int *ielem;
  int  ne,nx,np;
  int  edge_nodes;
  int  mid_nodes;
  int  edat_no;
  
  int  ne_wrt,np_wrt;
  int  matno ;


  shape      = edat_ptr->shape;

  ielem      = edat_ptr->ielem;
  ne         = edat_ptr->ne;
  np         = edat_ptr->np;
  nx         = edat_ptr->nx;

  edge_nodes = edat_ptr->edge_nodes;
  mid_nodes  = edat_ptr->mid_nodes;


  if(shape != 3 && shape != 4) {
    fprintf(stderr,"Bidimensional region only\n");
    exit(1);
  }


  if(nx-np != 1) {
    fprintf(stderr,"Illegal number of matnos\n");   /* only one key as matno */
    exit(1);
  }


  for(i=0;i<edats;i++) {
    edat_no = i+1;

    np_wrt = shape + shape*use_edge_ps[i]+use_inner_ps[i];

    ne_wrt = ne;

    fprintf(fp,"%s\n",KEY_EDAT_REAL);
    fprintf(fp,"%8d%8d%8d%8d\n",edat_no,ne_wrt,np_wrt,etype_WEBEXTENSION);

    for(j=0;j<ne;j++) {

      matno = *(ielem+nx*j+nx-1);

      /* Write vertices (Same as shape indicator now) */
      for(k=0;k<shape;k++) {
	fprintf(fp,"%8d",*(ielem+nx*j+k));
      }

      /* Write Edge Nodes */
      if(use_edge_ps[i]>0) {
	for(k=0;k<shape;k++) {  /* for each edge in basic shape */

	  for(l=0;l<use_edge_ps[i];l++) {
	    fprintf(fp,"%8d",*(ielem+nx*j+shape+(edge_nodes*k)+
			       (use_edge_no[i][l]-1)));
	  }
	}
      }

      /* Write Inner nodes */
      if(use_inner_ps[i]>0) {
	for(k=0;k<use_inner_ps[i];k++) {
	  fprintf(fp,"%8d",*(ielem+nx*j+shape+(edge_nodes*shape)+
			     (use_inner_no[i][k]-1)));
	}
      }

      /* Write matno */
      fprintf(fp,"%8d\n",matno);
    }
  }

  return;
}


    

    

    

    

