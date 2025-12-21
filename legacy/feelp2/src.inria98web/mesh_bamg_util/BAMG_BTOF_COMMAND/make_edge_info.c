#include <stdio.h>
#include "edat.h"


EDGE_2d *make_edge_info( edat_ptr )
     FEM_edat *edat_ptr;
{
  int *ielem;
  int np;
  int nx;
  int ne;
  int npmax;

  int i,j,k;
  int eno,nno,nno2,egno;
  int pos;            /* for temporary use */

  EDGE_2d *edge_info_ptr;

  static int  max_ne_pn; /* maximum no of elements connecting one node */
  static int *ne_pn;     /* number of elements connecting each node */
  static int *eno_en;    /* element number array for each node      */

  static int  max_neg_pn; /* maximum number of edges connecting one node */
  static int *neg_pn;     /* number of edges connecting each node        */
  static int *nno_en;     /* connecting node number array for each node  */

  static int  max_edges;  /* number of edges */
  static int *egno_tbl_en;/* edge number table by each node entry */

  static int *eg_nnos;    /* edge to number of both nodes correspondance */

  static int *ee_egno;    /* element to egno correspondance */


  /* Allocate memory for return value */
  edge_info_ptr = (EDGE_2d *)malloc(sizeof(EDGE_2d));
  if(edge_info_ptr == NULL) {
    fprintf(stderr,"Cannot allocate EDGE_2d structure\n");
    exit(1);
  }


  /* set input parameters */  
  ielem = edat_ptr -> ielem;
  np    = edat_ptr -> np;
  nx    = edat_ptr -> nx;
  ne    = edat_ptr -> ne;
  npmax = edat_ptr -> npmax;


  if(np != 3 && np != 4) {
    fprintf(stderr,"Now, 2D only, must be triangle or rectangle\n");
    exit(1);
  }

  /*---------------------------------*/
  /* Making node-element information */
  /*---------------------------------*/

  max_ne_pn = 0;
  ne_pn     = (int *)malloc(sizeof(int) * npmax);
  if(ne_pn == NULL) {
    fprintf(stderr,"Cannot allocate ne_pn(%d)\n",npmax);
    exit(1);
  }

  for(i=0;i<npmax;i++) {
    *(ne_pn + i) = 0;
  }

  for(i=0;i<ne;i++) {
    for(j=0;j<np;j++) {
      *(ne_pn+ (*(ielem+i*nx+j) - 1)) = *(ne_pn+ (*(ielem+i*nx+j) - 1)) + 1;
    }
  }

  for(i=0;i<npmax;i++) {
    if(max_ne_pn < *(ne_pn + i)) {
      max_ne_pn =  *(ne_pn + i);
    }
  }
  
  eno_en = (int *)malloc( sizeof(int)*max_ne_pn*npmax);
  if(eno_en == NULL) {
    fprintf(stderr,"Cannot allocate eno_en(%d)\n",max_ne_pn*npmax);
    exit(1);
  }
  
  /* re-construct ne_pn for pointer */
  for(i=0;i<npmax;i++) {
    *(ne_pn + i) = 0;
  }

  
  /* Making eno_en(element no for each node array) */
  for(i=0;i<ne;i++) {

    eno = i+1;   /* element number */

    for(j=0;j<np;j++) {

      nno = *(ielem+i*nx+j);  /* node number */

      *(eno_en+ max_ne_pn*(nno-1) + *(ne_pn +(nno-1))) = eno;
      *(ne_pn +(nno-1)) = *(ne_pn +(nno-1))+1;

    }
  }
  
  /*-------------------------*/
  /* Making edge information */
  /*-------------------------*/
  
  /*  max_neg_pn  maximum number of edges connecting one node */
  /* *neg_pn      number of edges connecting each node        */
  /* *nno_en;     connecting node number array for each node  */  

  /* max_ne_pn + 1  is ideal, if the mesh is good */
  max_neg_pn = max_ne_pn + 1;   /* plus one room  */


  neg_pn = (int *)malloc(sizeof(int)*npmax);
  nno_en = (int *)malloc(sizeof(int)*npmax*max_neg_pn);

  if(neg_pn == NULL || nno_en == NULL) {
    fprintf(stderr,"Cannot allocate neg_pn,nno_en\n");
    exit(1);
  }

  for(i=0;i<npmax;i++) {
    *(neg_pn+i) = 0;
  }

  for(i=0;i<ne;i++) {
    
    for(j=0;j<np;j++) {

      nno = *(ielem+i*nx+j);
      
      /* X---O---. */
      if(j==0) {
	nno2 = *(ielem+i*nx+np-1);
      }	
      else {
	nno2 = *(ielem+i*nx+j-1 );
      }
      pos = -1;
      for(k=0;k<*(neg_pn+(nno-1));k++) {
	if(*(nno_en+(nno-1)*max_neg_pn+k) == nno2) {
	  pos = k;
	}
      }
      if(pos == -1) {
	*(nno_en + (nno-1)*max_neg_pn + *(neg_pn+(nno-1)))
	  = nno2;
	*(neg_pn+(nno-1)) = *(neg_pn+(nno-1)) + 1;
      }


      /* .---O---X */
      if(j==np-1) {
	nno2 = *(ielem+i*nx+0);
      }
      else {
	nno2 = *(ielem+i*nx+j+1);
      }
      pos = -1;
      for(k=0;k<*(neg_pn+(nno-1));k++) {
	if(*(nno_en+(nno-1)*max_neg_pn+k) == nno2) {
	  pos = k;
	}
      }
      if(pos == -1) {
	*(nno_en + (nno-1)*max_neg_pn + *(neg_pn+(nno-1)))
	  = nno2;
	*(neg_pn+(nno-1)) = *(neg_pn+(nno-1)) + 1;
      }
    }
  }

  for(i=0;i<npmax;i++) {
    if(*(neg_pn+i) > max_neg_pn) {
      fprintf(stderr,"Too optimistic estimation for max_neg_pn\n");
      fprintf(stderr,"i=%d,*(neg_pn+i)=%d,max_neg_pn=%d\n",
	i,*(neg_pn+i),max_neg_pn);
      exit(1);
    }
  }

  /********************/
  /* Make edge number */
  /********************/

  /*  max_edges;     number of edges                      */
  /* *egno_tbl_en;   edge number table by each node entry */
  
  max_edges = 0;
  egno_tbl_en = (int *)malloc(sizeof(int)*npmax*max_neg_pn);

  if(egno_tbl_en == NULL) {
    fprintf(stderr,"Cannot allocate egno_tbl_en\n");
    exit(1);
  }
  
  /* initialize to 0 (0 means that the edge number is not decided yet */
  for(i=0;i<npmax*max_neg_pn;i++) {
    *(egno_tbl_en+i) = 0;
  }

  /* count the edge, simultaneously, make the table */
  for(i=0;i<npmax;i++) {
    
    for(j=0;j<*(neg_pn+i);j++) {
      
      if(*(egno_tbl_en + (i*max_neg_pn) + j) != 0) { /* already counted */
	continue;
      }

      max_edges = max_edges + 1;
      *(egno_tbl_en + (i*max_neg_pn) + j) = max_edges;
      nno =  *(nno_en +(i*max_neg_pn) + j);
      nno2=  i+1;
      pos =  -1;

      for(k=0;k<*(neg_pn + (nno-1));k++) {
	if(nno2 == *(nno_en + (nno-1)*max_neg_pn + k)) {
	  if(pos != -1) {
	    fprintf(stderr,"Inconsistent data\n");
	    exit(1);
	  }
	  pos = k;
	}
      }
      if(pos == -1) {
	fprintf(stderr,"Cannot find the correspondance %d-%d\n",nno,nno2);
	exit(1);
      }
      *(egno_tbl_en + (nno-1)*max_neg_pn + pos) = max_edges;
    }
  }


  /* Make edge-node number correnspondance */
  eg_nnos = (int *)malloc(sizeof(int)*2*max_edges);
  if(eg_nnos == NULL) {
    fprintf(stderr,"Cannot allocate eg_nnos\n");
    fprintf(stderr,"try to allocate %d ints\n",sizeof(int)*2*max_edges);
    exit(1);
  }
  
  /* initialize */
  for(i=0;i<2*max_edges;i++) {
    *(eg_nnos + i) = 0;
  }
  

  for(i=0;i<npmax;i++) {
    nno = i+1;
    
    for(j=0;j<*(neg_pn+i);j++) {
      egno = *(egno_tbl_en + i * max_neg_pn + j);
      if( *(eg_nnos + (egno-1)*2) != 0) {
	continue;
      }

      nno2 = *(nno_en + i * max_neg_pn + j);  
      *(eg_nnos + (egno-1)*2   ) = nno ;
      *(eg_nnos + (egno-1)*2 +1) = nno2;
    }
  }


  /* Make element -> egno correspondance */
  
  ee_egno = (int *)malloc(sizeof(int)* np * ne );
  if(ee_egno == NULL) {
    fprintf(stderr,"Cannot allocate ee_egno\n");
    exit(1);
  }

  for(i=0;i<ne;i++) {
    
    for(j=0;j<np;j++) {
      nno = *(ielem+i*nx+j);
      if(j == np-1) {
	nno2 = *(ielem+i*nx+0);
      }
      else {
	nno2 = *(ielem+i*nx+j+1);
      }

      egno = -1;
      for(k=0;k<*(neg_pn+(nno-1));k++) {
	if(*(nno_en+(nno-1)*max_neg_pn+k) == nno2) {
	  egno = *(egno_tbl_en+(nno-1)*max_neg_pn+k);
	}
      }
      if(egno == -1) {
	fprintf(stderr,"Inconsistent date in making ee_egno\n");
	exit(1);
      }
      *(ee_egno + i*np + j) = egno;
    }
  }


  edge_info_ptr->max_ne_pn   = max_ne_pn;
  edge_info_ptr->ne_pn       = ne_pn;    
  edge_info_ptr->eno_en      = eno_en;   

  edge_info_ptr->max_neg_pn  = max_neg_pn;
  edge_info_ptr->neg_pn      = neg_pn;    
  edge_info_ptr->nno_en      = nno_en;    
  edge_info_ptr->max_edges   = max_edges; 
  edge_info_ptr->egno_tbl_en = egno_tbl_en;
  edge_info_ptr->eg_nnos     = eg_nnos;    
  edge_info_ptr->ee_egno     = ee_egno;    

  /* CAUTION:
   * edge_info_ptr->edge_nodes
   * edge_info_ptr->edge_node_no   is set in make_new_edat.c
   *   (Modified on 1997/07/23 for boundary2D)
   */


  return(edge_info_ptr);
}

  
