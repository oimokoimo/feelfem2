/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_feel_data_file_bamg
 *      Date:   1995/09/1
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../solve_comp/solve_comp.h"
#include "../mesh_exec/mesh_exec.h"
#include "../var_comp/var_comp.h"

static MidPoint2D *copy_of_total_ptr;
static ElemDat    *copy_of_mesh_edat_ptr;

void save_midpoint2d_total( ptr )  /* called from mesh_bamg_exec.c */
     MidPoint2D   *ptr;
{
  copy_of_total_ptr = ptr;
  return;
}
void save_meshedatptr( ptr )       /* called from mesh_bamg_exec.c */
     ElemDat *ptr;
{
  copy_of_mesh_edat_ptr = ptr;
  return;
}

void make_feel_data_file_bamg()
{
  int i,j,k;
  FILE *fp;
  void wrt_bamg_feel_dat_header();


  /* Make BAMG_BTOF_FILE */
  fp = fopen( BAMG_BTOF_FILE ,"w");
  if(fp == NULL) {
    fprintf(stderr,"cannot Open file %s to write\n",BAMG_BTOF_FILE);
    exit(1);
  }

  /*=============*/
  /* Make header */
  /*=============*/
  if(status_no_delete) {
      fprintf(stderr,"goto wrt_bamg_feel_dat_header...");
  }
  wrt_bamg_feel_dat_header(fp);
  if(status_no_delete) {
      fprintf(stderr,"return.\n");
  }
  /*============================*/
  /* Geometric Edge Information */
  /*============================*/
  if(status_no_delete) {
      fprintf(stderr,"goto bamg_geometric_edge_wrt...");
  }
  bamg_geometric_edge_wrt(fp);
  if(status_no_delete) {
      fprintf(stderr,"return.\n");
  }
 
  /*=======================*/
  /* Mid point information */
  /*=======================*/
  fprintf(fp,"%5d\n",copy_of_total_ptr->edge_points);
  if(copy_of_total_ptr->edge_points > 0) {
    for(i=0;i<copy_of_total_ptr->edge_points;i++) {
      fprintf(fp,"%lf ",copy_of_total_ptr->edge[i]); 
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"%5d\n",copy_of_total_ptr->inner_points); 
  if(copy_of_total_ptr->inner_points > 0 ) {
    for(i=0;i<copy_of_total_ptr->inner_points;i++) {
      fprintf(fp,"%lf %lf\n",
	      copy_of_total_ptr->mid_x[i],copy_of_total_ptr->mid_y[i]); 
    }
  }

  /*=======================*/
  /* MESH REF Information  */
  /*=======================*/
  if(status_no_delete) {
      fprintf(stderr,"goto make_MESH_REF_bamg.\n");
  }
  make_MESH_REF_bamg(fp,copy_of_mesh_edat_ptr,copy_of_total_ptr);
  if(status_no_delete) {
      fprintf(stderr,"return.\n");
  }

  /*=======================*/
  /* Make Boundary data    */
  /*  for feel.bamg.exe    */
  /*=======================*/
  if(status_no_delete) {
      fprintf(stderr,"make_boundary_data_bamg.\n");
  }
  make_boundary_data_bamg(fp); 
  if(status_no_delete) {
      fprintf(stderr,"return.\n");
  }


  /*=======================*/
  /* Make Plot data for    */
  /*  for feel.bamg.exe    */
  /*=======================*/
  make_boundary_plot_data_main_bamg(fp);

  fclose(fp);


  /* Make feel_dat file from bamg.mesh and bamg.feel by BAMG_FDAT_COMMAND */
  system( BAMG_FDAT_COMMAND );
  return;
}


/* Header section */
void  wrt_bamg_feel_dat_header(fp)
     FILE *fp;
{
  int i;

  int ndim,npmax,nedat,nodeset,numset,nip;
  int nvars_fem,nvars_ewise;
  int mode_fem,mode_ex,mode_output;
  int nsolve_edats;

  EWISE_type *ewise_type_ptr;

  ndim    =  2;
  npmax   = -1;
  nodeset = current_nodesetno();
  numset  = 0;
  nedat   = current_edatno();
  nip     = how_many_points();
  nsolve_edats= how_many_nsolve_edats();

  

  mode_ex     = 0;
  mode_output = 0;
  nvars_fem   = how_many_fem_vars();
  nvars_ewise = how_many_ewise_types();

  fprintf(fp,"%8d%8d%8d%8d%8d%8d%8d\n",
	  ndim,npmax,nedat,nodeset,numset,nip,nsolve_edats);
  fprintf(fp,"%8d%8d\n",mode_ex,mode_output);
  fprintf(fp,"%8d%8d\n",nvars_fem,nvars_ewise);
  for(i=0;i<nvars_ewise;i++) {
    ewise_type_ptr = get_nth_ewise_type_ptr(i);
    fprintf(fp,"%8d%8d\n",
	    get_domain_edatno_by_name(ewise_type_ptr->domain_name),
	    ewise_type_ptr->points);
  }

  return;
}



