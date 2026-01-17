/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   bamg_feel_dat_ip.c
 *      Date:   1997/07/29
 *   
 *   Purpose:   ip data
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "edat.h"

void bamg_feel_dat_ip(fp,edat_ptr)
     FILE *fp;
     FEM_edat *edat_ptr;
{
  int i;
  int points;
  int *corresp;
  int columns;

  points = how_many_ip_points();
  corresp = edat_ptr->corresp;

  fprintf(fp,"%s\n",KEY_IP_REAL);  

  columns = 0;

  for(i=0;i<points;i++) {
    fprintf(fp,"%8d",*(corresp+i));
        columns++;
        if(columns == 8) {
	  fprintf(fp,"\n");
	  columns=0;
        }
  }

  if(columns != 0) fprintf(fp,"\n");

  return;
}
