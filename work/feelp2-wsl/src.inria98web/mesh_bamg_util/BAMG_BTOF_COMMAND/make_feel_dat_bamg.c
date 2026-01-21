/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_feel_dat_bamg.c
 *      Date:   1997/06/07
 *   
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
make_feel_dat_bamg(edats,use_edge_ps,use_edge_no,use_inner_ps,use_inner_no)
     int edats;        /* Number of edats to make */
     int use_edge_ps[MAX_EDATSET];
     int use_edge_no [MAX_EDATSET][MAX_MID_POINTS];
     int use_inner_ps[MAX_EDATSET];
     int use_inner_no[MAX_EDATSET][MAX_MID_POINTS];
{
  FILE *fp;

  FEM_edat *edat_ptr,*get_new_edat();


  fp = fopen(INPUT_FILE,"w");
  if(fp==NULL) {
    fprintf(stderr,"Cannot open %s to write.\n",INPUT_FILE);
    exit(1);
  }


  edat_ptr = get_new_edat();
  

  bamg_feel_dat_header_write(fp,edat_ptr);
  
  bamg_feel_dat_region_edat(fp,edat_ptr,edats,
			    use_edge_ps,use_edge_no,
			    use_inner_ps,use_inner_no);

  bamg_feel_dat_node(fp,edat_ptr);


  bamg_feel_dat_bc(fp,edat_ptr); 

  bamg_feel_dat_ip(fp,edat_ptr);

  
  fprintf(fp,"%s\n",KEY_END_REAL);


  fclose(fp);

}
