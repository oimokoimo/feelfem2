/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_bamg_info.c
 *      Date:   1997/05/27
 *   
 *  Modified:   1999/04/12  rect functionality for bamg
 *   
 *   Purpose:   make interface informations to BAMG
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"

typedef struct {         /* Interface structure to geometry of BAMG */
  int Dimension;                        /* DIMENSION = 2                */
  int MaximalAngleOfCorner;             /* It should be greater than 90 */
  int Vertices;                         /* Points in initial geometry   */
  int Corners;                          /* Corners in initial geometry  */
  int Isolatepoints;                    /* Isolatepoints (not on edge node */

  int element_type;                     /* element type TRI or RECT     */
  double *Vert_x,*Vert_y;
  int    *Vert_n;       /* Information of initial points*/
  int Edges;                            /* Initial Lines                */
  int *Edge_1,*Edge_2,*Edge_n;          /* Initial boundary lines       */
  int SubDomains;                       /* Number of subdomains         */
  int *Sub_type,*Sub_ref,*Sub_dir,*Sub_no;   /* Subdomain information */


  /* Additional information */

  double area;         /* Area size to mesh         */
  double initial_h;    /* Initial uniform mesh size */


} BAMG;

static BAMG bamg;      /* Information for BAMG mesh generator */

typedef struct {
  int app_edges;           /* maximum number of edge (for memory allocation) */
  int edges;               /* number of edges  */
  int *from,*to,*etype;    /* edge information in store  *(from+i) < *(to+i) */
} BAMG_EDGE;

static BAMG_EDGE bamg_edge;



void bamg_info_init()
{
  bamg.Dimension = 2;
  bamg.MaximalAngleOfCorner = 91;
  bamg.Vertices             = 0;
  bamg.Corners              = 0;
  bamg.Isolatepoints        = 0;
  bamg.Edges                = 0;
  bamg.SubDomains           = 0;

  bamg.Vert_x               = NULL;
  bamg.Vert_y               = NULL;
  bamg.Vert_n               = NULL;
  bamg.Edge_1               = NULL;
  bamg.Edge_2               = NULL;
  bamg.Edge_n               = NULL;


  bamg.Sub_type             = NULL;
  bamg.Sub_ref              = NULL;
  bamg.Sub_dir              = NULL;
  bamg.Sub_no               = NULL;

  bamg.initial_h            = 0.0;

  return;
}



void wrt_bamg_geom( fp )
     FILE *fp;
{
  int i,j,k;

  int refines;
  Refine *refine_ptr,*get_nth_refine_ptr();


  /* Version */
  fprintf(fp,"MeshVersionFormatted 0\n");

  /* Geometry file data */
  fprintf(fp,"# BAMG Geometry (for feel) by %s at %s\"\n",
	  feel_user,feel_date);
  
  /* Dimension */
  fprintf(fp,"Dimension\n2\n\n");

  /* Corner definition  CAUTION: Now polygonal domain only */
  fprintf(fp,"MaximalAngleOfCorner\n");
  fprintf(fp,"91\n\n");

  /* Vertices */
  fprintf(fp,"Vertices\n");
  fprintf(fp,"%d\n",bamg.Vertices);
  for(i=0;i<bamg.Vertices;i++) {
    fprintf(fp,"%f %f %d\n",*(bamg.Vert_x+i),*(bamg.Vert_y+i),*(bamg.Vert_n));
  }
  fprintf(fp,"\n");

  /* Corner definition  CAUTION: Now polygonal domain only */
  fprintf(fp,"Corners\n%d\n",bamg.Corners);
  for(i=0;i<bamg.Corners;i++) {
    fprintf(fp," %d",i+1);   /* Because isolated points follow last */
  }
  fprintf(fp,"\n");


  /* Edges */
  fprintf(fp,"Edges\n");
  fprintf(fp,"%d\n",bamg.Edges);
  for(i=0;i<bamg.Edges;i++) {
    fprintf(fp,"%d %d %d\n",
	    *(bamg.Edge_1+i),*(bamg.Edge_2+i),*(bamg.Edge_n+i));
  }


  /* hVertices */
  refines = how_many_refine_points();


  fprintf(fp,"hVertices\n");
  for(i=0;i<bamg.Vertices;i++) {
    int wrt_flag;
    
    wrt_flag = 0;

    for(j=0;j<refines;j++) {
      refine_ptr = get_nth_refine_ptr(j);
      if(refine_ptr->no == i) {
	wrt_flag = 1;
	fprintf(fp," %lf",bamg.initial_h*refine_ptr->factor);
	break;
      }
    }
    if(wrt_flag == 0) {
      fprintf(fp," %lf",bamg.initial_h);
    }

  }
  fprintf(fp,"\n\n");


  /* SubDomain */
  fprintf(fp,"SubDomain\n");
  fprintf(fp,"%d\n",bamg.SubDomains);
  for(i=0;i<bamg.SubDomains;i++) {
    fprintf(fp,"%d %d %d %d\n",
	    *(bamg.Sub_type+i),*(bamg.Sub_ref+i),
	    *(bamg.Sub_dir+i), *(bamg.Sub_no+i));
  }
  fprintf(fp,"\n");

  
	    
  fprintf(fp,"End\n");

  return;

}


  

void set_bamg_info_etype( etype )
     int etype;
{
  if(etype != TRI && etype != RECT) {
    SystemAbort("Now only triangle is allowd with -bamg option");
  }

  bamg.element_type = etype +1 ;  /* CAUTION!!!!!!!!!!!!!!*/


  return;
}


/* Calculation of the initial mesh size */
void set_bamg_info_nodes( total_area, nodes )
     double total_area;
     int    nodes;
{
  double dnodes,n,elements;
  double da;
  double h;
  double sqrt();

  dnodes = (double)nodes;
  n      = sqrt(dnodes);

  da     = total_area/(n-1.0)/(n-1.0)/2.0;

  h      = sqrt(da * 4.0 / 1.7320508);

  bamg.initial_h            = h;

  return;
}


void set_bamg_info_vertices_init( total_points , edge_points)
     int total_points;
     int edge_points;
{
  if(total_points <0 || total_points >9000000) {
    fprintf(stderr,"Illegal total_points %d\n",total_points);
    exit(1);
  }

  bamg.Vertices = total_points;
  bamg.Corners  = edge_points;    /* THIS MEANS ONLY POLYGONAL DOMAIN ALLOWD */
  /* CAUTION: */
  bamg.Corners  = total_points;   /* For refine isolated points 97/12/12 */
  
  bamg.Vert_x = (double *)malloc(sizeof(double)*total_points);
  bamg.Vert_y = (double *)malloc(sizeof(double)*total_points);
  bamg.Vert_n = (int    *)malloc(sizeof(int   )*total_points);

  if(bamg.Vert_x == NULL || bamg.Vert_y == NULL || bamg.Vert_n == NULL) {
    fprintf(stderr,"Cannot allocate memory in set_bamg_info_vertices_init\n");
    exit(1);
  }
  
  return;
}



void set_bamg_info_vertices(no,x,y,type)
     int no;       /* number      */
     double x,y;   /* coordinates */
     int type;     /* point type  */
{
  if(no > bamg.Vertices || no <1) {
    SystemAbort("Illegal vertex number in set_bamg_info_vertices");
  }
  
  *(bamg.Vert_x + (no-1)) = x;
  *(bamg.Vert_y + (no-1)) = y;
  *(bamg.Vert_n + (no-1)) = type;

  return;
}


void bamg_make_edge_info_init(app_edges)
     int app_edges;
{
  bamg_edge.app_edges = app_edges;
  bamg_edge.edges = 0;

  bamg_edge.from  = (int *)malloc(sizeof(int)*app_edges);
  bamg_edge.to    = (int *)malloc(sizeof(int)*app_edges);
  bamg_edge.etype = (int *)malloc(sizeof(int)*app_edges);

  if(bamg_edge.from  == NULL || bamg_edge.to == NULL ||
     bamg_edge.etype == NULL                            ) {
    SystemAbort("bamg_make_edge_info_init");
  }
  return;
}


void bamg_make_edge_info_store(from,to)
     int from,to;
{
  int i;
  int swap;

  if(from > to ) {
    swap = from;
    from = to;
    to   = swap;
  }

  for(i=0;i<bamg_edge.edges;i++) {
    if(*(bamg_edge.from + i) == from && *(bamg_edge.to + i) == to) return;
  }
  
  /* This means new edge detected */

  if(bamg_edge.edges + 1 >= bamg_edge.app_edges) {
    SystemAbort("Illegal in void bamg_make_edge_info_store(from,to)");
  }

  *(bamg_edge.from  + bamg_edge.edges) = from;
  *(bamg_edge.to    + bamg_edge.edges) = to  ;
  *(bamg_edge.etype + bamg_edge.edges) = bamg_edge.edges+1;  /* edge number */
 
  bamg_edge.edges = bamg_edge.edges + 1;

  return;
}

void make_bamg_geom_edges()
{
  int i;

  bamg.Edges = bamg_edge.edges;

  bamg.Edge_1 = (int *)malloc(sizeof(int)*bamg.Edges);
  bamg.Edge_2 = (int *)malloc(sizeof(int)*bamg.Edges);
  bamg.Edge_n = (int *)malloc(sizeof(int)*bamg.Edges);

  if(bamg.Edge_1 == NULL || bamg.Edge_2 == NULL || bamg.Edge_n == NULL) {
    SystemAbort("Cannot allocate memory in make_bamg_geom_edges");
  }


  for(i=0;i<bamg_edge.edges;i++) {
    *(bamg.Edge_1+i) = *(bamg_edge.from  + i);
    *(bamg.Edge_2+i) = *(bamg_edge.to    + i);
    *(bamg.Edge_n+i) = *(bamg_edge.etype + i);
  }

  return;
}

void make_bamg_subdomain_info_init(subdomains)
     int subdomains;
{
  bamg.SubDomains = subdomains;

  bamg.Sub_type   = (int *)malloc(sizeof(int)*subdomains);
  bamg.Sub_ref    = (int *)malloc(sizeof(int)*subdomains);
  bamg.Sub_dir    = (int *)malloc(sizeof(int)*subdomains);
  bamg.Sub_no     = (int *)malloc(sizeof(int)*subdomains);

  if(bamg.Sub_type == NULL || bamg.Sub_ref == NULL ||
     bamg.Sub_dir  == NULL || bamg.Sub_no  == NULL    ) {
    SystemAbort("Cannot allocate memory in make_bamg_subdomain_info_init");
  }

  return;
}


void set_bamg_info_subdomains(subno,matno,from,to)
     int subno,matno,from,to;   /* generally subno == matno */
{
  int i,type,ref,dir,no;
  int swap;

  if(subno != matno) SystemAbort("Illegal subno/matno");

  ref = -1;
  
  /* dir  */
  if(from > to) {
    dir  = -1;
    swap = from;
    from = to;
    to   = swap;
  }
  else {
    dir =   1;
  }

  /* type */
  type = 2;   /* LINE only */

  /* ref  */
  for(i=0;i<bamg_edge.edges;i++) {
    if(*(bamg_edge.from + i) == from && *(bamg_edge.to + i) == to) {
      ref = i+1;   /* This means edge number */
    }
  }

  if(ref == -1) {
    SystemAbort("Illegal number in set_bamg_info_subdomains");
  }

  /* no   */
  no = matno;


  *(bamg.Sub_type + (subno-1)) = type;
  *(bamg.Sub_ref  + (subno-1)) = ref;
  *(bamg.Sub_dir  + (subno-1)) = dir;
  *(bamg.Sub_no   + (subno-1)) = no;

  return;
}

void bamg_geometric_edge_wrt(fp)
  FILE *fp;
{
  int i;
  fprintf(fp,"%d\n",bamg.Edges);
  for(i=0;i<bamg.Edges;i++) {
    fprintf(fp,"%d %d\n",
      *(bamg.Edge_1+i), *(bamg.Edge_2+i));
  }
}
