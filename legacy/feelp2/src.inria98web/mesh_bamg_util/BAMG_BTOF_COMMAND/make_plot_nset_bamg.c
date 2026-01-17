/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_plot_nset_bamg.c
 *      Date:   1997/07/28
 *   
 *   Purpose:   MAKE PLOT NSET DATA
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "edat.h"

void make_plot_nset_bamg(edat_ptr,fp,plotlineno,segments,from_ptrptr,to_ptrptr)
     FEM_edat *edat_ptr;
     FILE  *fp;
     int    plotlineno;
     int    segments;
     char **from_ptrptr;
     char **to_ptrptr;
{
  int i,j;
  int total_points;
  int *node_ptr,points;
  int *corresp;

  Boundary2Dbamg *b2d_ptr,*get_b2d_ptr_by_both_ends_bamg();


  corresp = edat_ptr->corresp;
  

  fprintf(fp,"%s\n",KEY_NSET_REAL);

  /* count points */
  total_points = 0;
  for(i=0;i<segments;i++) {
    b2d_ptr = get_b2d_ptr_by_both_ends_bamg(*(from_ptrptr+i),
					    *(to_ptrptr+i));
    total_points = total_points+b2d_ptr->points - 1;
  }
  total_points = total_points+1;


  fprintf(fp,"%8d%8d%8d\n",plotlineno,total_points,1);


  for(i=0;i<segments;i++) {
    b2d_ptr = get_b2d_ptr_by_both_ends_bamg(*(from_ptrptr+i),
					    *(to_ptrptr+i));
	
    if(streq(b2d_ptr->from_name,*(from_ptrptr+i))) {
      /* ’Àµ’¤Î’¸þ’¤­ */
      if(i == 0) {
	node_ptr = b2d_ptr -> node_no;
	points   = b2d_ptr -> points;
      }
      else {
	node_ptr = b2d_ptr -> node_no;
	node_ptr++;                     /* ’ºÇ’½é’¤Ï’¥¹’¥­’¥Ã’¥× */
	points   = b2d_ptr -> points -1; /* ’ºÇ’½é’¤Ï’¥¹’¥­’¥Ã’¥× */
      }
 
      /* ’Àá’ÅÀ’¤ò’½ñ’¤¯ */
      for(j=0;j<points;j++) {
	fprintf(fp,"%8d\n",*(corresp+*node_ptr-1));
	node_ptr++;
      }
    }
    else {
      /* ’µÕ’¸þ’¤­   */

      if(i == 0) {
	node_ptr = b2d_ptr -> node_no;
	points   = b2d_ptr -> points;

	node_ptr += points -1;
      }
      else {
	node_ptr = b2d_ptr -> node_no;
	points   = b2d_ptr -> points -1;  /* ’ºÇ’½é’¤Ï’¥¹’¥­’¥Ã’¥× */

	node_ptr += points -1;
      }
      /* ’Àá’ÅÀ’¤ò’½ñ’¤¯ */
      for(j=0;j<points;j++) {
	fprintf(fp,"%8d\n",*(corresp+*node_ptr-1));
	node_ptr--;
      }		

    }

  }

  return;
}
  
  


