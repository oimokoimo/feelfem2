/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   bamg_btof.c
 *      Date:   1997/06/04
 *  Modified:   2000/04/25
 *   
 *   Purpose:   Generate feel_dat file from BAMG mesh file
 *   Functions: 
 *              
 *   Additinoal information to feel_dat
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../parallel/parallel.h"
#include "../../system/system.h"

static int edge_nodes;   /* new generated node for edges */
static int  mid_nodes;   /* new generated node for inner */
static double edge_node_pos[MAX_NODES_PER_ELEMENT];
static double mid_node_xpos[MAX_NODES_PER_ELEMENT];
static double mid_node_ypos[MAX_NODES_PER_ELEMENT];

#ifdef DBG
int debug_mode = 1;
#else
int debug_mode = 0;
#endif

static int edats;        /* Number of edats to make */
static int use_edge_ps[MAX_EDATSET];
static int use_edge_no [MAX_EDATSET][MAX_MID_POINTS];
static int use_inner_ps[MAX_EDATSET];
static int use_inner_no[MAX_EDATSET][MAX_MID_POINTS];


static FILE *fpr;        /* read file pointer for BAMG_BTOF_FILE */

/* read higher order node */
void read_node_info()
{
  int i,j;

  /* read inner node information */
  fscanf(fpr,"%d",&edge_nodes);
  for(i=0;i<edge_nodes;i++) {
    fscanf(fpr,"%lf",edge_node_pos+i);
  }
   
  fscanf(fpr,"%d",&mid_nodes);
  for(i=0;i<mid_nodes;i++) {
    fscanf(fpr,"%lf %lf",mid_node_xpos+i,mid_node_ypos+i);
  }  

  /* read edat sets */
  fscanf(fpr,"%d",&edats);
  for(i=0;i<edats;i++) {
    fscanf(fpr,"%d",&(use_edge_ps[i]));
    for(j=0;j<use_edge_ps[i];j++) {
      fscanf(fpr,"%d",&(use_edge_no[i][j]));
    }
    fscanf(fpr,"%d",&(use_inner_ps[i]));
    for(j=0;j<use_inner_ps[i];j++) {
      fscanf(fpr,"%d",&(use_inner_no[i][j]));
    }
  }

  return;
}





/* debug write */
void dbg_wrt()
{
  int i;

  fprintf(stderr,"------------------------------------\n");
  fprintf(stderr,"edge_nodes = %d\n",edge_nodes);
  for(i=0;i<edge_nodes;i++) {
    fprintf(stderr,"[%d]  %lf\n",i+1,edge_node_pos[i]);
  }
  fprintf(stderr,"------------------------------------\n");
   
  fprintf(stderr,"mid nodes  = %d\n",mid_nodes);
  for(i=0;i<mid_nodes;i++) {
    fprintf(stderr,"[%d] (%lf,%lf)\n",i+1,mid_node_xpos[i],mid_node_ypos[i]);
  }  
  fprintf(stderr,"------------------------------------\n");
  return;
}

/* Main routine */
void main(argc, argv)
int argc;
char *argv[];
{

  FILE *fp;

  if(argc >1) {
    fprintf(stderr,"if any option specified, it means debug mode now\n");
    debug_mode = 1;
  }

  fp  = fopen(INPUT_FILE,"w");
  if(fp == NULL) {
    fprintf(stderr,"Cannot open %s to write.\n",INPUT_FILE);
    exit(1);
  }


  fpr = fopen(BAMG_BTOF_FILE,"r");
  if(fpr == NULL) {
    fprintf(stderr,"Cannot open %s\n",BAMG_BTOF_FILE);
    exit(1);
  }

  read_bamg_mesh();


  /*-------------------------------*/
  /* Section 1  Header information */
  /*-------------------------------*/
  bamg_feel_dat_header_read(fpr);

  /*---------------------------------------*/
  /* Section 2  Geometric Edge Information */
  /*---------------------------------------*/
  bamg_geometric_edge_read(fpr);

  /*---------------------------------*/
  /* Section 3  Mid node information */
  /*---------------------------------*/
  read_node_info();                    /* This program is in this file */


  /*---------------------------------*/
  /* Section 4  Read Boundary data   */
  /*---------------------------------*/
#ifdef DBG
  fprintf(stderr,"Now, section 4\n");
#endif 

  read_bc_info(fpr);

  /* make new node and ordering */
  make_new_edat(edge_nodes,mid_nodes,
		edge_node_pos,mid_node_xpos,mid_node_ypos);

  /* make feel_dat file */
  make_feel_dat_bamg(edats,use_edge_ps,use_edge_no,use_inner_ps,use_inner_no);


  if(debug_mode)dbg_wrt();

  fclose(fpr);


  make_feel2bamg_file();

}


