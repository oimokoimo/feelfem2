/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_feel2bamg_file.c
 *      Date:   1997/06/18
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"

#include "edat.h"

void 
make_feel2bamg_file()
{
  FILE *fp;
  int i;
  int org_npmax;

  FEM_edat *edat_ptr,*get_new_edat();


  fp = fopen(BAMG_FTOB_FILE,"w");
  if(fp==NULL) {
    fprintf(stderr,"Cannot open %s to write.\n",INPUT_FILE);
    exit(1);
  }

  edat_ptr = get_new_edat();
  
  org_npmax = edat_ptr->org_npmax;

  fprintf(fp,"%d\n",org_npmax);
  for(i=0;i<org_npmax;i++) {
   fprintf(fp,"%d\n",*(edat_ptr->corresp+i));
  }
 
  fclose(fp);
  return;
}
