#include <stdio.h>
static FILE *fp=NULL;

FILE *GetFEELFEMFP()
{
  
  if(fp == NULL) {
    fp = fopen("ctrl77.dat","w");
    if(fp==NULL) {
      fprintf(stderr,"Cannot Open ctrl77.dat to write\n");
      exit(1);
    }
  }
  return(fp);
}
