/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_new_edat.c
 *      Date:   1997/06/06
 *   
 *   Purpose:   make a inter node for higher order elements
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"

#include "edat.h"



static FEM_edat new_edat;


FEM_edat *get_new_edat()
{
  return(&new_edat);
}

/*  
 * In make_new_node, it adds new nodes, and make ordering
 */

void make_new_edat(edge_nodes,mid_nodes,edge_pos,mid_xpos,mid_ypos)
     int edge_nodes,mid_nodes;
     double *edge_pos,*mid_xpos,*mid_ypos;
     
{
  FEM_edat *bamg_edat,*get_rd_bamg_edat();
  FEM_edat *edat_ptr;

  EDGE_2d  *edge_2d_ptr,*make_edge_info();

  int      *ordering_work,*element_ordering;
  void      make_new_node(),make_final_edat();

  extern int debug_mode;





  /**********************/
  /* get bamg mesh data */
  /**********************/
  bamg_edat   = get_rd_bamg_edat();
  edge_2d_ptr = make_edge_info(bamg_edat);

  /***********************************/
  /* allocate element ordering array */
  /***********************************/
  ordering_work    = (int *)malloc(sizeof(int)*bamg_edat->ne);
  element_ordering = (int *)malloc(sizeof(int)*bamg_edat->ne);
  if(element_ordering == NULL || ordering_work == NULL) {
    fprintf(stderr,"cannot allocate element ordering\n");
    exit(1);
  }

  /*******************************/
  /* make element ordering array */
  /*******************************/
  make_element_ordering(bamg_edat,edge_2d_ptr,ordering_work,element_ordering);



  /**************************************/
  /* make nodes for high order elements */
  /**************************************/
  if( edge_nodes == 0 && mid_nodes == 0) { /* no additional nodes */
    edat_ptr = bamg_edat;
  }
  else {
    edat_ptr = (FEM_edat *)malloc(sizeof(FEM_edat));
    if(edat_ptr == NULL) {
      fprintf(stderr,"Canot allocate edat\n");
      exit(1);
    }

    make_new_node(bamg_edat,edat_ptr,edge_2d_ptr,
		  edge_nodes,mid_nodes,edge_pos,mid_xpos,mid_ypos);

  }


  /*****************************/
  /* Make Boundary2D structure */
  /*                           */
  /* CAUTION: THIS IS MADE IN  */
  /*          ORIGINAL NODE NO.*/
  /*****************************/
  make_bamg_boundary2D(edat_ptr,edge_2d_ptr,edge_nodes);


  /************************************************/
  /* making a final edat  corresponds to MESH.FIN */
  /************************************************/
  make_final_edat(edat_ptr,bamg_edat->npmax,element_ordering,&new_edat);

#ifndef MSDOS
#ifdef DBG
  if(debug_mode) {
    dbg_xplot_init(&new_edat);
    dbg_xplot_draw_allmesh(&new_edat);
    dbg_xplot_draw_nodes(&new_edat);
    xwait();
  }
#endif
#endif

  return;
}


/* Making a new node without ordering */
void    make_new_node(bamg_edat,edat_ptr,edge_2d_ptr,
		  edge_nodes,mid_nodes,edge_pos,mid_xpos,mid_ypos)
     FEM_edat *bamg_edat,*edat_ptr;
     EDGE_2d  *edge_2d_ptr;
     int edge_nodes,mid_nodes;
     double *edge_pos,*mid_xpos,*mid_ypos;
{
  int i,j,k;

  int shape;

  int nno_ptr;    /* node number pointer */

  int npmax_old,ne_old,nx_old,np_old;
  int npmax,ne,nx,np;


  double *x_old,*y_old;
  int    *type_old,*ielem_old,*corresp_old;

  double *x,*y;
  int    *type,*ielem,*corresp;

  int edges;

  int *eg_nnos;
  int *ee_egno;

  int    *edge_node_no;   /* work array for making nodes in edge */
  double  xs,xe,ys,ye;
  int    ips,ipe;
  int    egno,egno_can;

  double  x1,y1,x2,y2,x3,y3,x4,y4;


  /* set old parameters from BAMG mesh */
  npmax_old = bamg_edat->npmax;
  shape     = bamg_edat->shape;

  ne_old    = bamg_edat->ne;
  nx_old    = bamg_edat->nx;
  np_old    = bamg_edat->np;
  ielem_old = bamg_edat->ielem;
  x_old     = bamg_edat->x;
  y_old     = bamg_edat->y;
  type_old  = bamg_edat->type;

  edges     = edge_2d_ptr->max_edges;
  eg_nnos   = edge_2d_ptr->eg_nnos;
  ee_egno   = edge_2d_ptr->ee_egno;


  /* triangle check */
#ifdef DBG
  if(shape != 3) {
    fprintf(stderr,"Now triangle mesh only\n");
    fprintf(stderr,"99/04/30  constructing in make_new_node...\n");
  }
#endif

  /* SET NEW mesh data */
  npmax     = npmax_old + edges*edge_nodes+ ne_old * mid_nodes;
  x         = (double *)malloc(sizeof(double) * npmax);
  y         = (double *)malloc(sizeof(double) * npmax);
  type      = (int    *)malloc(sizeof(double) * npmax);
  corresp   = (int    *)malloc(sizeof(int)    * npmax);
  
  ne        = ne_old;   /* element number never changes */
  nx        = nx_old + np_old * edge_nodes + mid_nodes;
  np        = np_old + np_old * edge_nodes + mid_nodes;

  ielem     = (int    *)malloc(sizeof(int)    * ne * nx);


  if(x     == NULL || y == NULL || type == NULL || corresp == NULL ||
     ielem == NULL) {
    fprintf(stderr,"Cannot allocate memory\n");
    exit(1);
  }
  
  /* set into edat_ptr */
  edat_ptr -> npmax = npmax;
  edat_ptr -> shape = shape;
  edat_ptr -> x     = x;
  edat_ptr -> y     = y;
  edat_ptr -> type  = type;
  edat_ptr -> ne    = ne;
  edat_ptr -> nx    = nx;
  edat_ptr -> np    = np;
  edat_ptr -> ielem = ielem;
  edat_ptr -> corresp = corresp;
  edat_ptr -> edge_nodes = edge_nodes;
  edat_ptr -> mid_nodes  = mid_nodes;


  /* Making New nodes (without re-numbering here) */
  nno_ptr = npmax_old;
  for(i=0;i<npmax_old;i++) {
    *(x+i)    = *(x_old+i);
    *(y+i)    = *(y_old+i);
    *(type+i) = *(type_old+i);
  }
  for(i=0;i<ne_old;i++) {
    for(j=0;j<np_old;j++) {
      *(ielem+i*nx+j) = *(ielem_old+i*nx_old+j);
    }
  }

  
  /* first, let's make a new nodes on the edges */
  if(edge_nodes>0) {

    /* allocate work array (store the node number for new nodes on edges) */
    edge_node_no = (int *)malloc(sizeof(int)*edge_nodes*edges);
    if(edge_node_no == NULL) {
      fprintf(stderr,"Cannot allocate edge_node_no\n");
      exit(1);
    }

    for(i=0;i<edges;i++) {
      xs = *(x_old + (*(eg_nnos+2*i+0)-1));
      ys = *(y_old + (*(eg_nnos+2*i+0)-1));
      xe = *(x_old + (*(eg_nnos+2*i+1)-1));
      ye = *(y_old + (*(eg_nnos+2*i+1)-1));

      for(j=0;j<edge_nodes;j++) {
	*(x+nno_ptr) = xs + (xe-xs)* (*(edge_pos+j));
	*(y+nno_ptr) = ys + (ye-ys)* (*(edge_pos+j));
	nno_ptr++;

	*(edge_node_no+i*edge_nodes+j) = nno_ptr;
      }
    }
  }

  /*-----------------------------------------*/
  /* Additional setting for Edge2d structure */
  /*-----------------------------------------*/
  if(edge_nodes >0) {
    edge_2d_ptr->edge_nodes   = edge_nodes;
    edge_2d_ptr->edge_node_no = edge_node_no;
  }
  else {
    edge_2d_ptr->edge_nodes   = edge_nodes;
    edge_2d_ptr->edge_node_no = NULL;
  }
   
  /* second, let's make new nodes in inner element */
  if(mid_nodes>0) {

    if( shape == 3) {
      
      for(i=0;i<ne;i++) {
	x1 = *(x_old + (*(ielem_old + i*nx_old + 0)-1));
	y1 = *(y_old + (*(ielem_old + i*nx_old + 0)-1));
	x2 = *(x_old + (*(ielem_old + i*nx_old + 1)-1));
	y2 = *(y_old + (*(ielem_old + i*nx_old + 1)-1));
	x3 = *(x_old + (*(ielem_old + i*nx_old + 2)-1));
	y3 = *(y_old + (*(ielem_old + i*nx_old + 2)-1));
	
	for(j=0;j<mid_nodes;j++) {
	  
	  *(x+nno_ptr) = (x2-x1)*( *(mid_xpos+j))+(x3-x1)*(*(mid_ypos+j)) + x1;
	  *(y+nno_ptr) = (y2-y1)*( *(mid_xpos+j))+(y3-y1)*(*(mid_ypos+j)) + y1;
	  
	  nno_ptr++;
	  
	  /* first, set ielem for inner nodes */
	  *(ielem + nx*i + np_old + np_old*edge_nodes + j) = nno_ptr;
	}
      }
    }

    if(shape == 4) {
   
      /* add 99/04/30 rect */

      for(i=0;i<ne;i++) {
	x1 = *(x_old + (*(ielem_old + i*nx_old + 0)-1));
	y1 = *(y_old + (*(ielem_old + i*nx_old + 0)-1));
	x2 = *(x_old + (*(ielem_old + i*nx_old + 1)-1));
	y2 = *(y_old + (*(ielem_old + i*nx_old + 1)-1));
	x3 = *(x_old + (*(ielem_old + i*nx_old + 2)-1));
	y3 = *(y_old + (*(ielem_old + i*nx_old + 2)-1));
	x4 = *(x_old + (*(ielem_old + i*nx_old + 3)-1));
	y4 = *(y_old + (*(ielem_old + i*nx_old + 3)-1));
	
	for(j=0;j<mid_nodes;j++) {
	  double xi,eta;
	  xi  = *(mid_xpos+j);
	  eta = *(mid_ypos+j);
	  *(x+nno_ptr) = 0.25 * (x1 *(1.0 - xi)*(1.0 - eta) +
				 x2 *(1.0 + xi)*(1.0 - eta) +
				 x3 *(1.0 + xi)*(1.0 + eta) +
				 x4 *(1.0 - xi)*(1.0 + eta) );

	  *(y+nno_ptr) = 0.25 * (y1 *(1.0 - xi)*(1.0 - eta) +
				 y2 *(1.0 + xi)*(1.0 - eta) +
				 y3 *(1.0 + xi)*(1.0 + eta) +
				 y4 *(1.0 - xi)*(1.0 + eta) );
	  
	  nno_ptr++;
	  
	  /* first, set ielem for inner nodes */
	  *(ielem + nx*i + np_old + np_old*edge_nodes + j) = nno_ptr;
	}
      }

    }
    if(shape != 3 && shape != 4) {
      fprintf(stderr,"Shape error in make_new_edat.c\n");
    }

  }


  if(nno_ptr != npmax) {
    fprintf(stderr,"Node number mismatch\n");
    exit(1);
  }

  /* set matno in ielem (this works in case of 3,4  and matno is more than 1*/
  for(i=0;i<ne;i++) {
    for(j=np_old;j<nx_old;j++) {
      *(ielem + i*nx + np_old*edge_nodes + mid_nodes + j) = 
	*(ielem_old + i*nx_old+j);
    }
  }

  /* set ielem for edge nodes */
  if(edge_nodes>0) {
    for(i=0;i<ne;i++) {

      /* set for LOCAL EDGE j */
      for(j=0;j<np_old;j++) {
	ips = *(ielem_old+nx_old*i+j);
	if(j == (np_old-1)) {
	  ipe = *(ielem_old+nx_old*i+0);
	}
	else {
	  ipe = *(ielem_old+nx_old*i+j+1);
	}

	/* search edge ips->ipe */
	
	egno = 0;
	for(k=0;k<np_old;k++) {   /* may work 3 and 4 */
	  egno_can = *(ee_egno+i*np_old+k);

	  if(*(eg_nnos+2*(egno_can-1)+0) == ips &&
	     *(eg_nnos+2*(egno_can-1)+1) == ipe    ) {
	    egno = egno_can;
	  }
	  else if(*(eg_nnos+2*(egno_can-1)+0) == ipe &&
	          *(eg_nnos+2*(egno_can-1)+1) == ips    ) {
	    egno = -egno_can;
	  }
	}
	if(egno == 0) {
	  fprintf(stderr,"There should be data mismatch in making midedge\n");
	  exit(1);
	}

	if(egno>0) {
	  for(k=0;k<edge_nodes;k++) {
	    *(ielem + nx*i + np_old + edge_nodes*j + k) =
	      *(edge_node_no+edge_nodes*(egno-1)+k);
	  }
	}
	else {
	  egno = -egno;
	  for(k=0;k<edge_nodes;k++) {
	    *(ielem + nx*i + np_old + edge_nodes*j + k) =
	      *(edge_node_no+edge_nodes*(egno-1)+ (edge_nodes-k-1));
	  }
	}
      }
    }
  }

  return;

}

/* 
 *
 * in make_final_edat, do node and element renumbering
 *
 */

void make_final_edat(edat_ptr,npmax_old,ordering,new_edat_ptr)
     FEM_edat *edat_ptr,*new_edat_ptr;
     int       npmax_old;
     int      *ordering;
{
  int i,j,k;

  int npmax,ne,nx,np;
  int shape;


  int eno,nno,nnoptr;

  double *x_old,*y_old;
  int    *ielem_old,*type_old;

  double *x,*y;
  int     org_npmax;
  int    *corresp,*rcorresp;
  int    *type,*ielem;
  int     edge_nodes,mid_nodes;   /* to send new_edat_ptr */

  
  /* These value is same */
  npmax = edat_ptr->npmax;
  shape = edat_ptr->shape;
  ne    = edat_ptr->ne;
  nx    = edat_ptr->nx;
  np    = edat_ptr->np;

  /* Original nodes in bamg */
  org_npmax = npmax_old;

  x_old     = edat_ptr->x;
  y_old     = edat_ptr->y;
  type_old  = edat_ptr->type;
  ielem_old = edat_ptr->ielem;

  edge_nodes= edat_ptr->edge_nodes;
  mid_nodes = edat_ptr->mid_nodes;



  x         = (double *)malloc(sizeof(double) * npmax);
  y         = (double *)malloc(sizeof(double) * npmax);
  type      = (int    *)malloc(sizeof(int)    * npmax);
  corresp   = (int    *)malloc(sizeof(int)    * npmax);
  rcorresp  = (int    *)malloc(sizeof(int)    * npmax);
  ielem     = (int    *)malloc(sizeof(int)    * ne * nx);


  if(x        == NULL || y     == NULL || type == NULL || corresp == NULL ||
     rcorresp == NULL || ielem == NULL) {
    fprintf(stderr,"Cannot allocate memory in make final edat\n");
    exit(1);
  }

  /* Initinalize corresp array (this is for new_edat_ptr) */
  for(i=0;i<npmax;i++) {
    *(corresp+i) = 0;
  }


  /* Make node renumbering information */
  nnoptr = 0;
  for(i=0;i<ne;i++) {
    
    eno = *(ordering+i);   /* element No. */

    for(j=0;j<np;j++) {
      nno = *(ielem_old+(eno-1)*nx+j);
      if(*(corresp+(nno-1))==0) {
	nnoptr++;
	*(corresp+(nno-1)) = nnoptr;

      }
    }
  }
  if(nnoptr != npmax) {
    fprintf(stderr,"Something wrong in node renumbering\n");
    exit(1);
  }

  /* Make renumbered node data */
  for(i=0;i<npmax;i++) {
    nno = *(corresp+i);    /* Old No. i+1  =>  New No. [nno] */
    *(x+(nno-1))    = *(x_old+i);
    *(y+(nno-1))    = *(y_old+i);
    *(type+(nno-1)) = *(type_old+i);
  }

  for(i=0;i<ne;i++) {
    eno = *(ordering+i);     /* old eno */
    
    for(j=0;j<np;j++) {
      nno = *(ielem_old+(eno-1)*nx+j);
      *(ielem+i*nx+j) = *(corresp+(nno-1));
    }
    for(j=np;j<nx;j++) {
      *(ielem+i*nx+j) = *(ielem_old+(eno-1)*nx+j);
    }
  }

  /* Make rcorresp array */
  for(i=0;i<npmax;i++) {
    *(rcorresp+i) = 0;
  }
  for(i=0;i<npmax;i++) {
    nno = *(corresp+i);

    if(*(rcorresp+(nno-1)) != 0) {
      fprintf(stderr,"ERR: nno=%d  i+1 = %d  *(rcorresp+(nno-1))=%d\n",
	      nno,i+1,*(rcorresp+(nno-1)));
    }

    if(i<npmax_old) {
      *(rcorresp + (nno-1)) = i+1;
    }
    else {
      *(rcorresp + (nno-1)) =   0;
    }
  }


  new_edat_ptr->npmax   = npmax;
  new_edat_ptr->shape   = shape;
  new_edat_ptr->ne      = ne;
  new_edat_ptr->nx      = nx;
  new_edat_ptr->np      = np;
  new_edat_ptr->ielem   = ielem;
  new_edat_ptr->org_npmax = org_npmax;
  new_edat_ptr->corresp = corresp;
  new_edat_ptr->rcorresp= rcorresp;
  new_edat_ptr->x       = x;
  new_edat_ptr->y       = y;
  new_edat_ptr->type    = type;

  new_edat_ptr->edge_nodes = edge_nodes;
  new_edat_ptr->mid_nodes  = mid_nodes;



  return;
} 
