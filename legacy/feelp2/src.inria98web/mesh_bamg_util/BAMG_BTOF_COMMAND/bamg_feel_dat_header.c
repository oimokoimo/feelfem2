/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1995/09/1
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */
#include <stdio.h>

#include "edat.h"


static int  ndim,npmax,nedat,nodeset,numset,nip;
static int  nvars_fem,nvars_ewise;
static int  mode_ex,mode_output;
static int  nsolve_edats;
static int *ewise_info;

void bamg_feel_dat_header_read(fpr)
     FILE *fpr;
{
  int i;

  fscanf(fpr,"%d",&ndim);
  fscanf(fpr,"%d",&npmax);
  fscanf(fpr,"%d",&nedat);
  fscanf(fpr,"%d",&nodeset);
  fscanf(fpr,"%d",&numset);
  fscanf(fpr,"%d",&nip);
  fscanf(fpr,"%d",&nsolve_edats);

  fscanf(fpr,"%d",&mode_ex);
  fscanf(fpr,"%d",&mode_output);

  fscanf(fpr,"%d",&nvars_fem);
  fscanf(fpr,"%d",&nvars_ewise);

  if(nvars_ewise != 0) {
    ewise_info = (int *)malloc(sizeof(int)*2*nvars_ewise);
    if(ewise_info == NULL) {
      fprintf(stderr,"Cannot allocate ewise_info\n");
      exit(1);
    }
  }

  for(i=0;i<nvars_ewise;i++) {
    fscanf(fpr,"%d",ewise_info+i*2+0);
    fscanf(fpr,"%d",ewise_info+i*2+1);
  }

  return;
}


void bamg_feel_dat_header_write(fp,edat_ptr)
     FILE     *fp;
     FEM_edat *edat_ptr;
{

  int i;

  npmax = edat_ptr->npmax;
  
  fprintf(fp,"FEEL\n");
  fprintf(fp,"%8d%8d%8d%8d%8d%8d%8d\n"
	  ,ndim,npmax,nedat,nodeset,numset,nip,nsolve_edats);
  fprintf(fp,"%8d%8d\n",mode_ex,mode_output);
  fprintf(fp,"%8d%8d\n",nvars_fem,nvars_ewise);
  for(i=0;i<nvars_ewise;i++) {
    fprintf(fp,"%8d%8d\n", *(ewise_info+i*2+0),*(ewise_info+i*2+1));
  }

  return;
}


  
  
  
